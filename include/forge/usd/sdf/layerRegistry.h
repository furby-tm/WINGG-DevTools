#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/sdf/layerRegistry.h"
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
#ifndef FORGE_USD_SDF_LAYER_REGISTRY_H
#define FORGE_USD_SDF_LAYER_REGISTRY_H

/// \file sdf/layerRegistry.h

#include "forge/forge.h"
#include "forge/usd/sdf/declareHandles.h"
#include "forge/base/tf/hash.h"

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/noncopyable.hpp>

#include <string>
#include <iosfwd>

FORGE_NAMESPACE_BEGIN

SDF_DECLARE_HANDLES(SdfLayer);

/// \class Sdf_LayerRegistry
///
/// A class that provides functionality to look up layers by asset path that
/// are tracked by the registry. Currently, when a new SdfLayer is created, it
/// is inserted into the layer registry. This allows SdfLayer::Find/FindOrOpen
/// to locate loaded layers.
///
class Sdf_LayerRegistry : boost::noncopyable
{
public:
    /// Constructor.
    Sdf_LayerRegistry();

    /// Inserts layer into the registry, or updates an existing registry entry
    /// if an entry is found for the same layer.
    void InsertOrUpdate(const SdfLayerHandle& layer);

    /// Erases the layer from the registry, if found.
    void Erase(const SdfLayerHandle& layer);

    /// Returns a layer from the registry, searching first by identifier using
    /// FindByIdentifier, then by real path using FindByRealPath. If the layer
    /// cannot be found, a null layer handle is returned. If the \p layerPath
    /// is relative, it is made absolute by anchoring to the current working
    /// directory.
    SdfLayerHandle Find(const std::string &layerPath,
                        const std::string &resolvedPath=std::string()) const;

    /// Returns a layer from the registry, consulting the by_identifier index
    /// with the \p layerPath as provided.
    SdfLayerHandle FindByIdentifier(const std::string& layerPath) const;

    /// Returns a layer from the registry, consulting the by_repository_path index
    /// with the \p layerPath as provided.
    SdfLayerHandle FindByRepositoryPath(const std::string& layerPath) const;

    /// Returns a layer from the registry, consulting the by_real_path index.
    /// If \p layerPath is an absolute file system path, the index is searched
    /// using the input path. Otherwise, \p layerPath is resolved and the
    /// resulting path is used to search the index.
    SdfLayerHandle FindByRealPath(
        const std::string& layerPath,
        const std::string& resolvedPath=std::string()) const;

    /// Returns all valid layers held in the registry as a set.
    SdfLayerHandleSet GetLayers() const;

private:
    // Index tags.
    struct by_identity {};
    struct by_identifier {};
    struct by_repository_path {};
    struct by_real_path {};

    // Key Extractors.
    struct layer_identifier {
        typedef std::string result_type;
        const result_type& operator()(const SdfLayerHandle& layer) const;
    };

    struct layer_repository_path {
        typedef std::string result_type;
        result_type operator()(const SdfLayerHandle& layer) const;
    };

    struct layer_real_path {
        typedef std::string result_type;
        result_type operator()(const SdfLayerHandle& layer) const;
    };

    // Unordered associative layer container.
    typedef boost::multi_index::multi_index_container<
        SdfLayerHandle,
        boost::multi_index::indexed_by<
            // Layer<->Layer, one-to-one. Duplicate layer handles cannot be
            // inserted into the container.
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<by_identity>,
                boost::multi_index::identity<SdfLayerHandle>,
                TfHash
                >,

            // Layer<->RealPath, one-to-one. The real path is the file from
            // which an existing layer asset was read, or the path to which a
            // newly created layer asset will be written.
            boost::multi_index::hashed_unique<
                boost::multi_index::tag<by_real_path>,
                layer_real_path
                >,

            // Layer<->Identifier, one-to-many. The identifier is the path
            // passed in to CreateNew/FindOrOpen, and may be any path form
            // resolvable to a single real path.
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<by_identifier>,
                layer_identifier
                >,

            // Layer<->RepositoryPath
            boost::multi_index::hashed_non_unique<
                boost::multi_index::tag<by_repository_path>,
                layer_repository_path
                >
            >
        > _Layers;

    // Identity index.
    typedef _Layers::index<by_identity>::type _LayersByIdentity;
    // Identifier index.
    typedef _Layers::index<by_identifier>::type _LayersByIdentifier;
    // Real path index.
    typedef _Layers::index<by_real_path>::type _LayersByRealPath;
    // Repository path index.
    typedef _Layers::index<by_repository_path>::type _LayersByRepositoryPath;

    _Layers _layers;
};

std::ostream&
operator<<(std::ostream& ostr, const Sdf_LayerRegistry& registry);

FORGE_NAMESPACE_END

#endif // FORGE_USD_SDF_LAYER_REGISTRY_H
