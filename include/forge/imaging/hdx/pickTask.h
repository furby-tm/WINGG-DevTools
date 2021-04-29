#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdx/pickTask.h"
/*
 * Copyright 2021 Forge. All Rights Reserved.
 *
 * The use of this software is subject to the terms of the
 * Forge license agreement provided at the time of installation
 * or download, or which otherwise accompanies this software in
 * either electronic or hard copy form.
 *
 * Portions of this file are derived from original work by Pixar
 * distributed with Universal Scene Description, a project of the
 * Academy Software Foundation (ASWF). https://www.aswf.io/
 *
 * Original Copyright (C) 2016-2021 Pixar.
 * Modifications copyright (C) 2020-2021 ForgeXYZ LLC.
 *
 * Forge. The Animation Software & Motion Picture Co.
 */
#ifndef FORGE_IMAGING_HDX_PICK_TASK_H
#define FORGE_IMAGING_HDX_PICK_TASK_H

#include "forge/forge.h"
#include "forge/imaging/hdx/api.h"

#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/renderPass.h"
#include "forge/imaging/hd/renderPassState.h"
#include "forge/imaging/hd/rprimCollection.h"
#include "forge/imaging/hd/task.h"

#include "forge/base/tf/declarePtrs.h"
#include "forge/base/gf/matrix4d.h"
#include "forge/base/gf/vec2i.h"
#include "forge/base/gf/vec2f.h"
#include "forge/base/gf/vec4i.h"
#include "forge/base/gf/vec4d.h"
#include "forge/usd/sdf/path.h"

#include <vector>
#include <memory>

FORGE_NAMESPACE_BEGIN

#define HDX_PICK_TOKENS              \
    /* Task context */               \
    (pickParams)                     \
                                     \
    /* Pick target */                \
    (pickPrimsAndInstances)          \
    (pickFaces)                      \
    (pickEdges)                      \
    (pickPoints)                     \
                                     \
    /* Resolve mode */               \
    (resolveNearestToCamera)         \
    (resolveNearestToCenter)         \
    (resolveUnique)                  \
    (resolveAll)

#ifndef DOXYGEN_SHOULD_SKIP_THIS
TF_DECLARE_PUBLIC_TOKENS(HdxPickTokens, HDX_API, HDX_PICK_TOKENS);
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

TF_DECLARE_WEAK_AND_REF_PTRS(GlfDrawTarget);

class HdPhRenderPassState;
using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;

/// Pick task params. This contains render-style state (for example), but is
/// augmented by HdxPickTaskContextParams, which is passed in on the task
/// context.
struct HdxPickTaskParams
{
    HdxPickTaskParams()
        : cullStyle(HdCullStyleNothing)
        , enableSceneMaterials(true)
    {}

    HdCullStyle cullStyle;
    bool enableSceneMaterials;
};

/// Picking hit structure. This is output by the pick task as a record of
/// what objects the picking query found.
struct HdxPickHit {
    SdfPath delegateId;
    SdfPath objectId;
    SdfPath instancerId;
    int instanceIndex;
    int elementIndex;
    int edgeIndex;
    int pointIndex;
    GfVec3f worldSpaceHitPoint;
    GfVec3f worldSpaceHitNormal;
    // normalizedDepth is in the range [0,1].
    float normalizedDepth;

    inline bool IsValid() const {
        return !objectId.IsEmpty();
    }

    HDX_API
    size_t GetHash() const;
};

using HdxPickHitVector = std::vector<HdxPickHit>;

/// Pick task context params.  This contains task params that can't come from
/// the scene delegate (like resolution mode and pick location, that might
/// be resolved late), as well as the picking collection and the output
/// hit vector.
/// 'pickTarget': The target of the pick operation, which may influence the
///     data filled in the HdxPickHit(s).
///     The available options are:
///         HdxPickTokens->pickPrimsAndInstances
///         HdxPickTokens->pickFaces
///         HdxPickTokens->pickEdges
///         HdxPickTokens->pickPoints
///
/// 'resolveMode': Dictates the resolution of which hit(s) are returned in
///     'outHits'.
///     The available options are:
///     1. HdxPickTokens->resolveNearestToCamera : Returns the hit whose
///         position is nearest to the camera
///     2. HdxPickTokens->resolveNearestToCenter : Returns the hit whose
///         position is nearest to center of the pick location/region.
///     3. HdxPickTokens->resolveUnique : Returns the unique hits, by hashing
///         the relevant member fields of HdxPickHit. The 'pickTarget'
///         influences this operation. For e.g., the subprim indices are ignored
///         when the pickTarget is pickPrimsAndInstances.
///     4. HdxPickTokens->resolveAll: Returns all the hits for the pick location
///         or region. The number of hits returned depends on the resolution
///         used and may have duplicates.
///
struct HdxPickTaskContextParams
{
    using DepthMaskCallback = std::function<void(void)>;

    HdxPickTaskContextParams()
        : resolution(128, 128)
        , pickTarget(HdxPickTokens->pickPrimsAndInstances)
        , resolveMode(HdxPickTokens->resolveNearestToCamera)
        , doUnpickablesOcclude(false)
        , viewMatrix(1)
        , projectionMatrix(1)
        , clipPlanes()
        , depthMaskCallback(nullptr)
        , collection()
        , outHits(nullptr)
    {}

    GfVec2i resolution;
    TfToken pickTarget;
    TfToken resolveMode;
    bool doUnpickablesOcclude;
    GfMatrix4d viewMatrix;
    GfMatrix4d projectionMatrix;
    std::vector<GfVec4d> clipPlanes;
    DepthMaskCallback depthMaskCallback;
    HdRprimCollection collection;
    HdxPickHitVector *outHits;
};

/// \class HdxPickTask
///
/// A task for running picking queries against the current scene.
/// This task generates an id buffer for a "pick frustum" (normally the
/// camera frustum with the near plane narrowed to an (x,y) location and a
/// pick radius); then it resolves that id buffer into a series of prim paths.
/// The "Hit" output also contains subprim picking results (e.g. picked face,
/// edge, point, instance) and the intersection point in scene worldspace.
///
/// HdxPickTask takes an HdxPickTaskParams through the scene delegate, and
/// HdxPickTaskContextParams through the task context as "pickParams".
/// It produces a hit vector, in the task context as "pickHits".
class HdxPickTask : public HdTask
{
public:
    HDX_API
    HdxPickTask(HdSceneDelegate* delegate, SdfPath const& id);

    HDX_API
    ~HdxPickTask() override;

    /// Sync the render pass resources
    HDX_API
    void Sync(HdSceneDelegate* delegate,
              HdTaskContext* ctx,
              HdDirtyBits* dirtyBits) override;

    /// Prepare the pick task
    HDX_API
    void Prepare(HdTaskContext* ctx,
                 HdRenderIndex* renderIndex) override;

    /// Execute the pick task
    HDX_API
    void Execute(HdTaskContext* ctx) override;

    HDX_API
    const TfTokenVector &GetRenderTags() const override;

    /// Utility: Given a UNorm8Vec4 pixel, unpack it into an int32 ID.
    static inline int DecodeIDRenderColor(unsigned char const idColor[4]) {
        return (int32_t(idColor[0] & 0xff) << 0)  |
               (int32_t(idColor[1] & 0xff) << 8)  |
               (int32_t(idColor[2] & 0xff) << 16) |
               (int32_t(idColor[3] & 0xff) << 24);
    }

private:
    HdxPickTaskParams _params;
    HdxPickTaskContextParams _contextParams;
    TfTokenVector _renderTags;

    // We need to cache a pointer to the render index so Execute() can
    // map prim ID to paths.
    HdRenderIndex *_index;

    void _InitIfNeeded(GfVec2i const& widthHeight);
    void _ConditionStencilWithGLCallback(
            HdxPickTaskContextParams::DepthMaskCallback maskCallback);

    bool _UseOcclusionPass() const;

    // Create a shared render pass each for pickables and unpickables
    HdRenderPassSharedPtr _pickableRenderPass;
    HdRenderPassSharedPtr _occluderRenderPass;

    // Having separate render pass states allows us to use different
    // shader mixins if we choose to (we don't currently).
    HdRenderPassStateSharedPtr _pickableRenderPassState;
    HdRenderPassStateSharedPtr _occluderRenderPassState;

    // A single draw target is shared for all contexts.  Since the FBO cannot
    // be shared, we clone the attachments on each request.
    GlfDrawTargetRefPtr _drawTarget;

    HdxPickTask() = delete;
    HdxPickTask(const HdxPickTask &) = delete;
    HdxPickTask &operator =(const HdxPickTask &) = delete;
};

/// A utility class for resolving ID buffers into hits.
class HdxPickResult {
public:

    // Pick result takes a tuple of ID buffers:
    // - (primId, instanceId, elementId, edgeId, pointId)
    // along with some geometric buffers:
    // - (depth, Neye)
    // ... and resolves them into a series of hits, using one of the
    // algorithms specified below.
    //
    // index is used to fill in the HdxPickHit structure;
    // pickTarget is used to determine what a valid hit is;
    // viewMatrix, projectionMatrix, depthRange are used for unprojection
    // to calculate the worldSpaceHitPosition and worldSpaceHitNormal.
    // bufferSize is the size of the ID buffers, and subRect is the sub-region
    // of the id buffers to iterate over in the resolution algorithm.
    //
    // All buffers need to be the same size, if passed in.  It's legal for
    // only the depth and primId buffers to be provided; everything else is
    // optional but provides a richer picking result.
    HDX_API
    HdxPickResult(int const* primIds,
                  int const* instanceIds,
                  int const* elementIds,
                  int const* edgeIds,
                  int const* pointIds,
                  int const* neyes,
                  float const* depths,
                  HdRenderIndex const *index,
                  TfToken const& pickTarget,
                  GfMatrix4d const& viewMatrix,
                  GfMatrix4d const& projectionMatrix,
                  GfVec2f const& depthRange,
                  GfVec2i const& bufferSize,
                  GfVec4i const& subRect);

    HDX_API
    ~HdxPickResult();

    HDX_API
    HdxPickResult(HdxPickResult &&);
    HDX_API
    HdxPickResult& operator=(HdxPickResult &&);

    /// Return whether the result was given well-formed parameters.
    HDX_API
    bool IsValid() const;

    /// Return the nearest single hit point. Note that this method may be
    /// considerably more efficient, as it only needs to construct a single
    /// Hit object.
    HDX_API
    void ResolveNearestToCamera(HdxPickHitVector* allHits) const;

    /// Return the nearest single hit point from the center of the viewport.
    /// Note that this method may be considerably more efficient, as it only
    /// needs to construct a single Hit object.
    HDX_API
    void ResolveNearestToCenter(HdxPickHitVector* allHits) const;

    /// Return all hit points. Note that this may contain redundant objects,
    /// however it allows access to all depth values for a given object.
    HDX_API
    void ResolveAll(HdxPickHitVector* allHits) const;

    /// Return the set of unique hit points, keeping only the nearest depth
    /// value.
    HDX_API
    void ResolveUnique(HdxPickHitVector* allHits) const;

private:
    bool _ResolveHit(int index, int x, int y, float z, HdxPickHit* hit) const;
    size_t _GetHash(int index) const;
    bool _IsValidHit(int index) const;

    // Provide accessors for all of the ID buffers.  Since all but _primIds
    // are optional, if the buffer doesn't exist just return -1 (== no hit).
    int _GetPrimId(int index) const {
        return _primIds ? _primIds[index] : -1;
    }
    int _GetInstanceId(int index) const {
        return _instanceIds ? _instanceIds[index] : -1;
    }
    int _GetElementId(int index) const {
        return _elementIds ? _elementIds[index] : -1;
    }
    int _GetEdgeId(int index) const {
        return _edgeIds ? _edgeIds[index] : -1;
    }
    int _GetPointId(int index) const {
        return _pointIds ? _pointIds[index] : -1;
    }

    // Provide an accessor for the normal buffer.  If the normal buffer is
    // provided, this function will unpack the normal.  The fallback is
    // GfVec3f(0.0f).
    GfVec3f _GetNormal(int index) const;

    int const* _primIds;
    int const* _instanceIds;
    int const* _elementIds;
    int const* _edgeIds;
    int const* _pointIds;
    int const* _neyes;
    float const* _depths;
    HdRenderIndex const *_index;
    TfToken  _pickTarget;
    GfMatrix4d _ndcToWorld;
    GfMatrix4d _eyeToWorld;
    GfVec2f _depthRange;
    GfVec2i _bufferSize;
    GfVec4i _subRect;
};

// For sorting, order hits by ndc depth.
HDX_API
bool operator<(HdxPickHit const& lhs, HdxPickHit const& rhs);

// VtValue requirements
HDX_API
std::ostream& operator<<(std::ostream& out, const HdxPickHit& h);
HDX_API
bool operator==(const HdxPickHit& lhs,
                const HdxPickHit& rhs);
HDX_API
bool operator!=(const HdxPickHit& lhs,
                const HdxPickHit& rhs);

HDX_API
std::ostream& operator<<(std::ostream& out, const HdxPickTaskParams& pv);
HDX_API
bool operator==(const HdxPickTaskParams& lhs,
                const HdxPickTaskParams& rhs);
HDX_API
bool operator!=(const HdxPickTaskParams& lhs,
                const HdxPickTaskParams& rhs);

HDX_API
std::ostream& operator<<(std::ostream& out, const HdxPickTaskContextParams& pv);
HDX_API
bool operator==(const HdxPickTaskContextParams& lhs,
                const HdxPickTaskContextParams& rhs);
HDX_API
bool operator!=(const HdxPickTaskContextParams& lhs,
                const HdxPickTaskContextParams& rhs);
FORGE_NAMESPACE_END

#endif // FORGE_IMAGING_HDX_PICK_TASK_H
