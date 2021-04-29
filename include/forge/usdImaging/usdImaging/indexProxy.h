#line 1 "C:/Users/tyler/dev/WINGG/forge/usdImaging/usdImaging/indexProxy.h"
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
#ifndef FORGE_USD_IMAGING_USD_IMAGING_INDEX_PROXY_H
#define FORGE_USD_IMAGING_USD_IMAGING_INDEX_PROXY_H

/// \file usdImaging/indexProxy.h

#include "forge/forge.h"
#include "forge/usdImaging/usdImaging/api.h"
#include "forge/usdImaging/usdImaging/delegate.h"

#include "forge/usd/sdf/path.h"
#include "forge/usd/usd/prim.h"

#include "forge/base/tf/token.h"


FORGE_NAMESPACE_BEGIN


/// \class UsdImagingIndexProxy
///
/// This proxy class exposes a subset of the private Delegate API to
/// PrimAdapters.
///
class UsdImagingIndexProxy {
public:
    /// A note on paths/prims: the core function of UsdImagingIndexProxy and
    /// UsdImagingDelegate is to maintain a set of mappings between USD prims
    /// and hydra prims (and a set of adapters that know how to translate
    /// USD properties to hydra buffers).  A USD prim can represent multiple
    /// hydra prims (e.g. point instancer prototypes that are referenced twice),
    /// and a hydra prim can represent multiple USD prims (e.g. a single hydra
    /// instancer prim representing multiple native instances).
    ///
    /// There are three different prim "namespaces" that the delegate works
    /// with: "USD paths", which represent paths to USD prims; "index paths",
    /// which represent paths to hydra prims in the render index; and
    /// "cache paths", which represent paths to buffers in the value cache
    /// backing hydra prims.  Cache paths and index paths are the same,
    /// except that index paths have the "delegateID" prefixed onto their path.
    ///
    /// Index paths are only used in the interface to hydra.  In IndexProxy
    /// and the adapters, the pattern is to use "cachePath" as a key to look
    /// up state for a hydra prim; and pass "usdPrim" when we additionally
    /// need to specify the related USD prim.  The naming helps clarify them,
    /// and the fact that we pass a UsdPrim and not an SdfPath further ensures
    /// that we pass valid USD paths instead of passing cache paths by mistake.


    /// Adds a dependency from the given usdPrim to the given cache path.
    /// Insert* will automatically add a dependency, so this is for hydra prims
    /// that may depend on more than one usd prim (e.g. subsets, instancers)
    USDIMAGING_API
    void AddDependency(SdfPath const& cachePath,
                       UsdPrim const& usdPrim);

    /// Insert a hydra prim with the specified cache path.  As mentioned above,
    /// the delegateID will be prepended before adding the prim in hydra, but
    /// cachePath will be the key into all internal usdImaging datastructures.
    /// usdPrim is the USD prim this hydra prim is representing (e.g. the
    /// UsdGeomMesh for which we are inserting a hydra mesh).  If no
    /// adapter is specified, UsdImagingDelegate will choose based on Usd
    /// prim type; some clients (e.g. instancing) want to override the adapter
    /// choice but this should be used sparingly.
    ///
    /// For Rprims and Instancers, "parentPath" is the parent instancer.
    USDIMAGING_API
    void InsertRprim(TfToken const& primType,
                     SdfPath const& cachePath,
                     UsdPrim const& usdPrim,
                     UsdImagingPrimAdapterSharedPtr adapter =
                        UsdImagingPrimAdapterSharedPtr());

    USDIMAGING_API
    void InsertSprim(TfToken const& primType,
                     SdfPath const& cachePath,
                     UsdPrim const& usdPrim,
                     UsdImagingPrimAdapterSharedPtr adapter =
                        UsdImagingPrimAdapterSharedPtr());

    USDIMAGING_API
    void InsertBprim(TfToken const& primType,
                     SdfPath const& cachePath,
                     UsdPrim const& usdPrim,
                     UsdImagingPrimAdapterSharedPtr adapter =
                        UsdImagingPrimAdapterSharedPtr());

    USDIMAGING_API
    void InsertInstancer(SdfPath const& cachePath,
                         UsdPrim const& usdPrim,
                         UsdImagingPrimAdapterSharedPtr adapter =
                            UsdImagingPrimAdapterSharedPtr());

    // Mark a prim as needing follow-up work by the delegate
    // (e.g. TrackVariability); this is automatically called on Insert*, but
    // needs to manually be called in some special cases like native
    // instancer population.
    USDIMAGING_API
    void Refresh(SdfPath const& cachePath);

    //
    // All removals are deferred to avoid surprises during change processing.
    //

    // Removes the Rprim at the specified cache path.
    void RemoveRprim(SdfPath const& cachePath) {
        _rprimsToRemove.push_back(cachePath);
        _hdPrimInfoToRemove.push_back(cachePath);
        _RemoveDependencies(cachePath);
    }

    // Removes the Sprim at the specified cache path.
    void RemoveSprim(TfToken const& primType, SdfPath const& cachePath) {
        _TypeAndPath primToRemove = {primType, cachePath};
        _sprimsToRemove.push_back(primToRemove);
        _hdPrimInfoToRemove.push_back(cachePath);
        _RemoveDependencies(cachePath);
    }

    // Removes the Bprim at the specified cache path.
    void RemoveBprim(TfToken const& primType, SdfPath const& cachePath) {
        _TypeAndPath primToRemove = {primType, cachePath};
        _bprimsToRemove.push_back(primToRemove);
        _hdPrimInfoToRemove.push_back(cachePath);
        _RemoveDependencies(cachePath);
    }

    // Removes the HdInstancer at the specified cache path.
    void RemoveInstancer(SdfPath const& cachePath) {
        _instancersToRemove.push_back(cachePath);
        _hdPrimInfoToRemove.push_back(cachePath);
        _RemoveDependencies(cachePath);
    }

    USDIMAGING_API
    void MarkRprimDirty(SdfPath const& cachePath, HdDirtyBits dirtyBits);

    USDIMAGING_API
    void MarkSprimDirty(SdfPath const& cachePath, HdDirtyBits dirtyBits);

    USDIMAGING_API
    void MarkBprimDirty(SdfPath const& cachePath, HdDirtyBits dirtyBits);

    USDIMAGING_API
    void MarkInstancerDirty(SdfPath const& cachePath, HdDirtyBits dirtyBits);

    USDIMAGING_API
    bool IsRprimTypeSupported(TfToken const& typeId) const;

    USDIMAGING_API
    bool IsSprimTypeSupported(TfToken const& typeId) const;

    USDIMAGING_API
    bool IsBprimTypeSupported(TfToken const& typeId) const;

    // Check if the given path has been populated yet.
    USDIMAGING_API
    bool IsPopulated(SdfPath const& cachePath) const;

    // Recursively repopulate the specified usdPath into the render index.
    USDIMAGING_API
    void Repopulate(SdfPath const& usdPath);

    USDIMAGING_API
    UsdImagingPrimAdapterSharedPtr GetMaterialAdapter(
        UsdPrim const& materialPrim);

    // XXX: This is a workaround for some bugs in USD edit processing, and
    // the weird use of HdPrimInfo by instanced prims. It removes the dependency
    // between a hydra prim and whatever USD prim is in its primInfo, since this
    // dependency is automatically inserted and for instanced prims will
    // erroneously add a dependency between a hydra prototype and
    // a USD instancer.
    //
    // Pending some refactoring, hopefully this API will disappear.
    USDIMAGING_API
    void RemovePrimInfoDependency(SdfPath const& cachePath);

private:
    friend class UsdImagingDelegate;
    UsdImagingIndexProxy(UsdImagingDelegate* delegate,
                            UsdImagingDelegate::_Worker* worker)
        : _delegate(delegate)
        , _worker(worker)
    {}

    // Sort and de-duplicate "repopulate" paths to prevent double-inserts.
    // Called by UsdImagingDelegate::ApplyPendingUpdates.
    void _UniqueifyPathsToRepopulate();

    bool _AddHdPrimInfo(SdfPath const& cachePath,
                        UsdPrim const& usdPrim,
                        UsdImagingPrimAdapterSharedPtr const& adapter);

    USDIMAGING_API
    void _RemoveDependencies(SdfPath const& cachePath);

    SdfPathVector const& _GetUsdPathsToRepopulate() {
        return _usdPathsToRepopulate;
    }
    void _ProcessRemovals();

    void _AddTask(SdfPath const& usdPath);

    struct _TypeAndPath {
        TfToken primType;
        SdfPath cachePath;
    };

    typedef std::vector<_TypeAndPath> _TypeAndPathVector;

    typedef std::vector<UsdImagingDelegate::_DependencyMap::value_type>
        _DependencyVector;

    UsdImagingDelegate* _delegate;
    UsdImagingDelegate::_Worker* _worker;
    SdfPathVector _usdPathsToRepopulate;
    SdfPathVector _rprimsToRemove;
    _TypeAndPathVector _sprimsToRemove;
    _TypeAndPathVector _bprimsToRemove;
    SdfPathVector _instancersToRemove;
    SdfPathVector _hdPrimInfoToRemove;
    _DependencyVector _dependenciesToRemove;
};


FORGE_NAMESPACE_END

#endif //FORGE_USD_IMAGING_USD_IMAGING_INDEX_PROXY_H
