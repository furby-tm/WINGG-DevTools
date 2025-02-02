#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/renderIndex.h"
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
#ifndef FORGE_IMAGING_HD_RENDER_INDEX_H
#define FORGE_IMAGING_HD_RENDER_INDEX_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/changeTracker.h"
#include "forge/imaging/hd/perfLog.h"
#include "forge/imaging/hd/primTypeIndex.h"
#include "forge/imaging/hd/resourceRegistry.h"
#include "forge/imaging/hd/sortedIds.h"
#include "forge/imaging/hd/tokens.h"

#include "forge/imaging/hf/perfLog.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/gf/vec4i.h"
#include "forge/base/tf/hashmap.h"

#if !defined(Q_MOC_RUN)
# include <tbb/enumerable_thread_specific.h>
#endif /* Q_MOC_RUN */

#include <vector>
#include <unordered_map>
#include <memory>

FORGE_NAMESPACE_BEGIN

class HdRprim;
class HdSprim;
class HdBprim;
class HdDrawItem;
class HdRprimCollection;
class HdSceneDelegate;
class HdRenderDelegate;
class HdExtComputation;
class VtValue;
class HdInstancer;
class HdDriver;

using HdDirtyListSharedPtr = std::shared_ptr<class HdDirtyList>;

using HdTaskSharedPtr = std::shared_ptr<class HdTask>;

using HdResourceRegistrySharedPtr = std::shared_ptr<class HdResourceRegistry>;
using HdTaskSharedPtrVector = std::vector<HdTaskSharedPtr>;
using HdTaskContext = std::unordered_map<TfToken,
                           VtValue,
                           TfToken::HashFunctor>;
using HdDriverVector = std::vector<HdDriver*>;

/// \class HdRenderIndex
///
/// The Hydra render index is a flattened representation of the client scene
/// graph, which may be composed of several self-contained scene graphs, each of
/// which provides a HdSceneDelegate adapter for data access.
///
/// Thus, multiple HdSceneDelegate's may be tied to the same HdRenderIndex.
///
/// The render index, however, is tied to a single HdRenderDelegate, which
/// handles the actual creation and deletion of Hydra scene primitives. These
/// include geometry and non-drawable objects (such as the camera and texture
/// buffers). The render index simply holds a handle to these primitives, and
/// tracks any changes to them via the HdChangeTracker.
/// It also tracks computations and tasks that may update resources and render a
/// subset of the renderable primitives.
///
/// The render index orchestrates the "syncing" of scene primitives, by
/// providing the relevant scene delegate for data access, and leaves resource
/// management to the rendering backend (via HdResourceRegistry).
///
/// It also provides "execution" functionality for application facing Hydra
/// concepts (such as HdTask/HdRenderPass) in computing the set of HdDrawItems
/// for a given HdRprimCollection, for rendering.
///
/// \sa
/// HdChangeTracker
/// HdDrawItem
/// HdRenderDelegate
/// HdRprimCollection
/// HdSceneDelegate
///
/// \note
/// The current design ties a HdRenderIndex to a HdRenderDelegate.
/// However, the HdRenderIndex isn't tied to a viewer (viewport).
/// It is common to have multiple viewers image the composed scene (for example,
/// with different cameras), in which case the HdRenderIndex and
/// HdRenderDelegate are shared by the viewers.
///
/// If two viewers use different HdRenderDelegate's, then it may unfortunately
/// require populating two HdRenderIndex's.
///
class HdRenderIndex final
{
public:
    typedef std::vector<HdDrawItem const*> HdDrawItemPtrVector;

    /// Create a render index with the given render delegate.
    /// Returns null if renderDelegate is null.
    /// The render delegate and render tasks may require access to a renderer's
    /// device provided by the application. The objects can be
    /// passed in as 'drivers'. Hgi is an example of a HdDriver.
    //    hgi = Hgi::CreatePlatformDefaultHgi()
    //    hgiDriver = new HdDriver<Hgi*>(HgiTokens→renderDriver, hgi)
    //    HdRenderIndex::New(_renderDelegate, {_hgiDriver})
    HD_API
    static HdRenderIndex* New(
        HdRenderDelegate *renderDelegate,
        HdDriverVector const& drivers);

    HD_API
    ~HdRenderIndex();

    /// Clear all r (render), s (state) and b (buffer) prims.
    HD_API
    void Clear();

    /// Clear all entries in the render index under
    /// the given root and belong to a specified delegate.
    ///
    /// Used for example to unload a delegate.
    HD_API
    void RemoveSubtree(const SdfPath &root, HdSceneDelegate* sceneDelegate);

    // ---------------------------------------------------------------------- //
    /// Given a prim id, returns the path of the corresponding rprim
    /// or an empty path if none is found.
    HD_API
    SdfPath GetRprimPathFromPrimId(int primId) const;

    // ---------------------------------------------------------------------- //
    /// \name Synchronization
    // ---------------------------------------------------------------------- //

    /// Adds the dirty list to the sync queue. The actual processing of the
    /// dirty list happens later in SyncAll().
    ///
    /// This is typically called from HdRenderPass::Sync. However, the current
    /// call chain ties it to SyncAll, i.e.
    /// HdRenderIndex::SyncAll > .... > HdRenderPass::Sync > HdRenderIndex::Sync
    HD_API
    void EnqueuePrimsToSync(
        HdDirtyListSharedPtr const &dirtyList,
        HdRprimCollection const &collection);

    /// Syncs input tasks, B & S prims, (external) computations and processes
    /// all pending dirty lists (which syncs the R prims). At the end of this
    /// step, all the resources that need to be updated have handles to their
    /// data sources.
    /// This is the first phase in Hydra's execution. See HdEngine::Execute
    HD_API
    void SyncAll(HdTaskSharedPtrVector *tasks, HdTaskContext *taskContext);

    // ---------------------------------------------------------------------- //
    /// \name Execution
    // ---------------------------------------------------------------------- //

    /// Returns a list of relevant draw items that match the criteria specified
    //  by renderTags and collection.
    /// The is typically called during render pass execution, which is the
    /// final phase in the Hydra's execution. See HdRenderPass::Execute
    HD_API
    HdDrawItemPtrVector GetDrawItems(HdRprimCollection const& collection,
                                     TfTokenVector const& renderTags);

    // ---------------------------------------------------------------------- //
    /// \name Change Tracker
    // ---------------------------------------------------------------------- //

    HdChangeTracker& GetChangeTracker() { return _tracker; }
    HdChangeTracker const& GetChangeTracker() const { return _tracker; }

    // ---------------------------------------------------------------------- //
    /// \name Renderable prims (e.g. meshes, basis curves)
    // ---------------------------------------------------------------------- //

    /// Returns whether the rprim type is supported by this render index.
    HD_API
    bool IsRprimTypeSupported(TfToken const& typeId) const;

    /// Insert a rprim into index
    HD_API
    void InsertRprim(TfToken const& typeId,
                     HdSceneDelegate* sceneDelegate,
                     SdfPath const& rprimId);

    /// Remove a rprim from index
    HD_API
    void RemoveRprim(SdfPath const& id);

    /// Returns true if rprim \p id exists in index.
    bool HasRprim(SdfPath const& id) {
        return _rprimMap.find(id) != _rprimMap.end();
    }

    /// Returns the rprim of id
    HD_API
    HdRprim const *GetRprim(SdfPath const &id) const;

    /// Returns the scene delegate for the given rprim
    HD_API
    HdSceneDelegate *GetSceneDelegateForRprim(SdfPath const &id) const;

    /// Query function to return the id's of the scene delegate and instancer
    /// associated with the Rprim at the given path.
    HD_API
    bool GetSceneDelegateAndInstancerIds(SdfPath const &id,
                                         SdfPath* sceneDelegateId,
                                         SdfPath* instancerId) const;

    /// Returns the render tag for the given rprim
    HD_API
    TfToken GetRenderTag(SdfPath const& id) const;

    /// Return the material tag for the given rprim
    HD_API
    TfToken GetMaterialTag(SdfPath const& id) const;

    /// Returns a sorted list of all Rprims in the render index.
    /// The list is sorted by std::less<SdfPath>
    HD_API
    const SdfPathVector &GetRprimIds() { return _rprimIds.GetIds(); }


    /// Returns the subtree rooted under the given path.
    HD_API
    SdfPathVector GetRprimSubtree(SdfPath const& root);


    // ---------------------------------------------------------------------- //
    /// \name Instancer Support
    // ---------------------------------------------------------------------- //

    /// Insert an instancer into index
    HD_API
    void InsertInstancer(HdSceneDelegate* delegate,
                         SdfPath const &id);

    /// Remove an instancer from index
    HD_API
    void RemoveInstancer(SdfPath const& id);

    /// Returns true if instancer \p id exists in index.
    bool HasInstancer(SdfPath const& id) {
        return _instancerMap.find(id) != _instancerMap.end();
    }

    /// Returns the instancer of id
    HD_API
    HdInstancer *GetInstancer(SdfPath const &id) const;

    // ---------------------------------------------------------------------- //
    /// \name Task Support
    // ---------------------------------------------------------------------- //

    /// Inserts a new task into the render index with an identifier of \p id.
    template <typename T>
    void InsertTask(HdSceneDelegate* delegate, SdfPath const& id);

    /// Removes the given task from the RenderIndex.
    HD_API
    void RemoveTask(SdfPath const& id);

    /// Returns true if a task exists in the index with the given \p id.
    bool HasTask(SdfPath const& id) {
        return _taskMap.find(id) != _taskMap.end();
    }

    /// Returns the task for the given \p id.
    HD_API
    HdTaskSharedPtr const& GetTask(SdfPath const& id) const;

    // ---------------------------------------------------------------------- //
    /// \name Scene state prims (e.g. camera, light)
    // ---------------------------------------------------------------------- //

    /// Returns whether the sprim type is supported by this render index.
    HD_API
    bool IsSprimTypeSupported(TfToken const& typeId) const;

    /// Insert a sprim into index
    HD_API
    void InsertSprim(TfToken const& typeId,
                     HdSceneDelegate* delegate,
                     SdfPath const& sprimId);

    HD_API
    void RemoveSprim(TfToken const& typeId, SdfPath const &id);

    HD_API
    HdSprim *GetSprim(TfToken const& typeId, SdfPath const &id) const;

    /// Returns the subtree rooted under the given path for the given sprim
    /// type.
    HD_API
    SdfPathVector GetSprimSubtree(TfToken const& typeId,
                                  SdfPath const& root);

    /// Returns the fullback prim for the Sprim of the given type.
    HD_API
    HdSprim *GetFallbackSprim(TfToken const& typeId) const;


    // ---------------------------------------------------------------------- //
    /// \name Buffer prims (e.g. textures, buffers)
    // ---------------------------------------------------------------------- //

    /// Returns whether the bprim type is supported by this render index.
    HD_API
    bool IsBprimTypeSupported(TfToken const& typeId) const;

    /// Insert a bprim into index
    HD_API
    void InsertBprim(TfToken const& typeId,
                     HdSceneDelegate* delegate,
                     SdfPath const& bprimId);

    HD_API
    void RemoveBprim(TfToken const& typeId, SdfPath const &id);

    HD_API
    HdBprim *GetBprim(TfToken const& typeId, SdfPath const &id) const;

    /// Returns the subtree rooted under the given path for the given bprim
    /// type.
    HD_API
    SdfPathVector GetBprimSubtree(TfToken const& typeId,
                                  SdfPath const& root);

    /// Returns the fallback prim for the Bprim of the given type.
    HD_API
    HdBprim *GetFallbackBprim(TfToken const& typeId) const;

    // ---------------------------------------------------------------------- //
    /// \name Render Delegate
    // ---------------------------------------------------------------------- //
    /// Currently, a render index only supports connection to one type of
    /// render delegate, due to the inserted information and change tracking
    /// being specific to that delegate type.
    HD_API
    HdRenderDelegate *GetRenderDelegate() const;

    // The render delegate may require access to a render context / device
    // that is provided by the application.
    HD_API
    HdDriverVector const& GetDrivers() const;

    /// Returns a shared ptr to the resource registry of the current render
    /// delegate.
    HD_API
    HdResourceRegistrySharedPtr GetResourceRegistry() const;

private:
    // The render index constructor is private so we can check
    // renderDelegate before construction: see HdRenderIndex::New(...).
    HdRenderIndex(
        HdRenderDelegate *renderDelegate,
        HdDriverVector const& drivers);

    // ---------------------------------------------------------------------- //
    // Private Helper methods
    // ---------------------------------------------------------------------- //

    // Go through all RPrims and reallocate their instance ids
    // This is called once we have exhausted all all 24bit instance ids.
    void _CompactPrimIds();

    // Allocate the next available instance id to the prim
    void _AllocatePrimId(HdRprim* prim);

    // Inserts the task into the index and updates tracking state.
    // _TrackDelegateTask is called by the inlined InsertTask<T>, so it needs
    // to be marked HD_API.
    HD_API
    void _TrackDelegateTask(HdSceneDelegate* delegate,
                            SdfPath const& taskId,
                            HdTaskSharedPtr const& task);

    template <typename T>
    static inline const TfToken & _GetTypeId();

    void _RemoveRprimSubtree(const SdfPath &root,
                             HdSceneDelegate* sceneDelegate);
    void _RemoveInstancerSubtree(const SdfPath &root,
                                 HdSceneDelegate* sceneDelegate);
    void _RemoveExtComputationSubtree(const SdfPath &root,
                                      HdSceneDelegate* sceneDelegate);
    void _RemoveTaskSubtree(const SdfPath &root,
                            HdSceneDelegate* sceneDelegate);

    // ---------------------------------------------------------------------- //
    // Index State
    // ---------------------------------------------------------------------- //
    struct _RprimInfo {
        HdSceneDelegate *sceneDelegate;
        HdRprim *rprim;
    };

    struct _TaskInfo {
        HdSceneDelegate *sceneDelegate;
        HdTaskSharedPtr task;
    };

    typedef std::unordered_map<SdfPath, _TaskInfo, SdfPath::Hash> _TaskMap;
    typedef TfHashMap<SdfPath, _RprimInfo, SdfPath::Hash> _RprimMap;
    typedef std::vector<SdfPath> _RprimPrimIDVector;

    typedef Hd_PrimTypeIndex<HdSprim> _SprimIndex;
    typedef Hd_PrimTypeIndex<HdBprim> _BprimIndex;

    _RprimMap _rprimMap;
    Hd_SortedIds _rprimIds;

    _RprimPrimIDVector _rprimPrimIdMap;

    _TaskMap _taskMap;

    _SprimIndex _sprimIndex;
    _BprimIndex _bprimIndex;

    HdChangeTracker _tracker;

    typedef TfHashMap<SdfPath, HdInstancer*, SdfPath::Hash> _InstancerMap;
    _InstancerMap _instancerMap;

    struct _SyncQueueEntry {
        HdDirtyListSharedPtr dirtyList;
        HdRprimCollection collection;

    };
    typedef std::vector<_SyncQueueEntry> _SyncQueue;
    _SyncQueue _syncQueue;

    /// With the removal of task-based collection include/exclude path
    /// filtering, HdDirtyLists were generating their lists of dirty rprim IDs
    /// by looking through every rprim in the render index. When the number of
    /// tasks/render passes/dirty lists grew large, this resulted in
    /// significant overhead and lots of duplication of work.
    /// Instead, the render index itself now takes care of generating the
    /// complete list of dirty rprim IDs when requested by the HdDirtyList.
    /// During SyncAll(), the first HdDirtyList to request the list of dirty
    /// IDs for a given HdDirtyBits mask triggers the render index to produce
    /// that list and cache it in a map. Subsequent requests reuse the cached
    /// list. At the end of SyncAll(), the map is cleared in preparation for
    /// the next sync.
    std::unordered_map<HdDirtyBits, const SdfPathVector> _dirtyRprimIdsMap;

    friend class HdDirtyList;
    const SdfPathVector& _GetDirtyRprimIds(HdDirtyBits mask);

    HdRenderDelegate *_renderDelegate;
    HdDriverVector _drivers;

    // ---------------------------------------------------------------------- //
    // Sync State
    // ---------------------------------------------------------------------- //
    TfTokenVector _activeRenderTags;
    unsigned int  _renderTagVersion;

    /// Register the render delegate's list of supported prim types.
    void _InitPrimTypes();

    /// Creates fallback prims for each supported prim type.
    bool _CreateFallbackPrims();

    /// Release the fallback prims.
    void _DestroyFallbackPrims();

    void _GatherRenderTags(const HdTaskSharedPtrVector *tasks);

    typedef tbb::enumerable_thread_specific<HdDrawItemPtrVector>
        _ConcurrentDrawItems;

    void _AppendDrawItems(const SdfPathVector &rprimIds,
                          size_t begin,
                          size_t end,
                          HdRprimCollection const& collection,
                          _ConcurrentDrawItems* result);

    /// Register core hydra reprs. Only ever called once, the first time
    /// a render index is created.
    /// XXX: This code should move to the application layer.
    static void _ConfigureReprs();

    // Remove default constructor
    HdRenderIndex() = delete;

    // Don't allow copies
    HdRenderIndex(const HdRenderIndex &) = delete;
    HdRenderIndex &operator=(const HdRenderIndex &) = delete;

};

template <typename T>
void
HdRenderIndex::InsertTask(HdSceneDelegate* delegate, SdfPath const& id)
{
    HD_TRACE_FUNCTION();
    HF_MALLOC_TAG_FUNCTION();

    HdTaskSharedPtr task = std::make_shared<T>(delegate, id);
    _TrackDelegateTask(delegate, id, task);
}

FORGE_NAMESPACE_END

#endif //FORGE_IMAGING_HD_RENDER_INDEX_H
