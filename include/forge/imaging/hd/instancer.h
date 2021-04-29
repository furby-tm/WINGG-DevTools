#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/instancer.h"
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
#ifndef FORGE_IMAGING_HD_INSTANCER_H
#define FORGE_IMAGING_HD_INSTANCER_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/types.h"

#include "forge/usd/sdf/path.h"

#include <mutex>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
class HdRenderIndex;
class HdRprim;
class HdRenderParam;

/// \class HdInstancer
///
/// This class exists to facilitate point cloud style instancing. Instancers,
/// conceptually, are instructions to draw N objects; for each object, store
/// which Rprim you're drawing and what instance-specific primvars you're
/// binding.
///
///     "/InstancerA": prototypes = ["/sphere", "/cube", "/sphere"];
///                    translate  = [  <0,0,0>, <1,0,0>,   <0,1,0>]
///
/// Hydra stores this in reverse: Rprims store which instancer is drawing them,
/// and the instancer stores which indices in that array of N objects are the
/// given Rprim.
///
///     "/sphere": instancerId = "/InstancerA"
///     "/cube": instancerId = "/InstancerA"
///     Instancer A: indices("/sphere") = [0, 2]
///                  indices("/cube") = [1]
///                  translate = [<0,0,0>, <1,0,0>, <0,1,0>]
///
/// Instancing is implemented by the prototype drawing itself multiple times,
/// and looking up per-instance data each time based on "indices": so
/// "/sphere" would draw itself once with translate=<0,0,0> and once with
/// translate=<0,1,0>.
///
/// To make things more exciting, instancers can be nested.
///
///     "/cube": instancerId = "/InstancerA"
///     "/InstancerA": instancerId = "/InstancerB"
///                    indices("/cube") = [0, 1]
///                    translate = [<0,0,0>, <1,0,0>]
///     "/InstancerB": indices("/InstancerA") = [0, 1]
///                    translate = [<0,0,0>, <0,1,0>]
///
/// In this case, "/cube" draws itself four times, for each of the
/// index tuples <0,0>, <0,1>, <1,0>, <1,1> where the first index is
/// the index in instancerA, and the second index is in instancerB.
///
/// If the same primvar (e.g. "translate") shows up at multiple levels of
/// nesting, it's resolved as follows:
///
/// Transforms
/// ----------
///
/// Instance primvars "translate", "rotate", "scale", and "instanceTransform"
/// are used to compute the final transform of an instance. "translate"
/// and "scale" are interpreted as vec3: position, and axis-aligned scale
/// respectively. "rotate" is interpreted as a vec4 quaternion, and
/// "instanceTransform" is a 4x4 matrix.  In the transform computation,
/// everything is converted to a 4x4 matrix.
///
/// There are additional transforms: "instancerTransform" comes from
/// HdSceneDelegate::GetInstancerTransform(instancer, proto), and represents
/// the constant transform between the instancer and the prototype. It
/// varies with each level of nesting, but not across instances.
///
/// "transform" is the proto Rprim's local transform.
///
/// The final instance transform for instance "index" is computed as:
///
///     nested_transform(level) = instancerTransform(level) *
///                               translate(level, index) *
///                               rotate(level, index) *
///                               scale(level, index) *
///                               instanceTransform(level, index);
///     output_transform = product(i : nested-levels - 1 -> 0) {
///                           nested_transform(i)
///                        } * transform;
///
/// Any transforms not provided by the scene delegate are set to identity.
///
/// Class responsibilities
/// ======================
///
/// HdInstancer's primary role is to track the "indices" arrays for each
/// proto used by an instancer, and any provided primvar arrays. The
/// implementation is in the renderer-specific instancers, like HdPhInstancer.
///
/// All data access (aside from local caches) is routed to the HdSceneDelegate.
///

class HdInstancer {
public:
    /// Constructor.
    HD_API
    HdInstancer(HdSceneDelegate* delegate, SdfPath const& id);

    HD_API
    virtual ~HdInstancer();

    /// Returns the identifier.
    SdfPath const& GetId() const { return _id; }

    /// Returns the parent instancer identifier.
    SdfPath const& GetParentId() const { return _parentId; }

    HdSceneDelegate* GetDelegate() const { return _delegate; }

    HD_API
    static int GetInstancerNumLevels(HdRenderIndex& index,
                                     HdRprim const& rprim);

    HD_API
    static TfTokenVector const & GetBuiltinPrimvarNames();

    HD_API
    virtual void Sync(HdSceneDelegate *sceneDelegate,
                      HdRenderParam   *renderParam,
                      HdDirtyBits     *dirtyBits);

    HD_API
    virtual void Finalize(HdRenderParam *renderParam);

    HD_API
    virtual HdDirtyBits GetInitialDirtyBitsMask() const;

    HD_API
    static void _SyncInstancerAndParents(
        HdRenderIndex &renderIndex,
        SdfPath const& instancerId);

protected:
    HD_API
    void _UpdateInstancer(HdSceneDelegate *delegate,
                          HdDirtyBits *dirtyBits);

private:
    HdSceneDelegate* _delegate;
    SdfPath _id;
    SdfPath _parentId;

    // XXX: This mutex exists for _SyncInstancerAndParents, which will go
    // away when the render index calls sync on instancers.
    std::mutex _instanceLock;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_INSTANCER_H
