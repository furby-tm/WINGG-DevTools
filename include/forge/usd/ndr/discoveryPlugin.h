#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/ndr/discoveryPlugin.h"
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

#ifndef FORGE_USD_NDR_DISCOVERY_PLUGIN_H
#define FORGE_USD_NDR_DISCOVERY_PLUGIN_H

/// \file ndr/registry.h

#include "forge/forge.h"
#include "forge/usd/ndr/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/type.h"
#include "forge/base/tf/weakBase.h"
#include "forge/usd/ndr/declare.h"
#include "forge/usd/ndr/nodeDiscoveryResult.h"

FORGE_NAMESPACE_BEGIN

/// Register a discovery plugin (`DiscoveryPluginClass`) with the plugin system.
/// If registered, the discovery plugin will execute its discovery process when
/// the registry is instantiated.
#define NDR_REGISTER_DISCOVERY_PLUGIN(DiscoveryPluginClass)                   \
TF_REGISTRY_FUNCTION(TfType)                                                  \
{                                                                             \
    TfType::Define<DiscoveryPluginClass, TfType::Bases<NdrDiscoveryPlugin>>() \
        .SetFactory<NdrDiscoveryPluginFactory<DiscoveryPluginClass>>();       \
}

TF_DECLARE_WEAK_AND_REF_PTRS(NdrDiscoveryPluginContext);

/// A context for discovery.  Discovery plugins can use this to get
/// a limited set of non-local information without direct coupling
/// between plugins.
class NdrDiscoveryPluginContext : public TfRefBase, public TfWeakBase
{
public:
    NDR_API
    virtual ~NdrDiscoveryPluginContext() = default;

    /// Returns the source type associated with the discovery type.
    /// This may return an empty token if there is no such association.
    NDR_API
    virtual TfToken GetSourceType(const TfToken& discoveryType) const = 0;
};

TF_DECLARE_WEAK_AND_REF_PTRS(NdrDiscoveryPlugin);

/// \class NdrDiscoveryPlugin
///
/// Interface for discovery plugins.
///
/// Discovery plugins, like the name implies, find nodes. Where the plugin
/// searches is up to the plugin that implements this interface. Examples
/// of discovery plugins could include plugins that look for nodes on the
/// filesystem, another that finds nodes in a cloud service, and another that
/// searches a local database. Multiple discovery plugins that search the
/// filesystem in specific locations/ways could also be created. All discovery
/// plugins are executed as soon as the registry is instantiated.
///
/// These plugins simply report back to the registry what nodes they found in
/// a generic way. The registry doesn't know much about the innards of the
/// nodes yet, just that the nodes exist. Understanding the nodes is the
/// responsibility of another set of plugins defined by the `NdrParserPlugin`
/// interface.
///
/// Discovery plugins report back to the registry via `NdrNodeDiscoveryResult`s.
/// These are small, lightweight classes that contain the information for a
/// single node that was found during discovery. The discovery result only
/// includes node information that can be gleaned pre-parse, so the data is
/// fairly limited; to see exactly what's included, and what is expected to
/// be populated, see the documentation for `NdrNodeDiscoveryResult`.
///
/// \section create How to Create a Discovery Plugin
/// There are three steps to creating a discovery plugin:
/// <ul>
///     <li>
///         Implement the discovery plugin interface, `NdrDiscoveryPlugin`
///     </li>
///     <li>
///         Register your new plugin with the registry. The registration macro
///         must be called in your plugin's implementation file:
///         \code{.cpp}
///         NDR_REGISTER_DISCOVERY_PLUGIN(YOUR_DISCOVERY_PLUGIN_CLASS_NAME)
///         \endcode
///         This macro is available in discoveryPlugin.h.
///     </li>
///     <li>
///         In the same folder as your plugin, create a `plugInfo.json` file.
///         This file must be formatted like so, substituting
///         `YOUR_LIBRARY_NAME`, `YOUR_CLASS_NAME`, and `YOUR_DISPLAY_NAME`:
///         \code{.json}
///         {
///             "Plugins": [{
///                 "Type": "library",
///                 "Name": "YOUR_LIBRARY_NAME",
///                 "Root": "@PLUG_INFO_ROOT@",
///                 "LibraryPath": "@PLUG_INFO_LIBRARY_PATH@",
///                 "ResourcePath": "@PLUG_INFO_RESOURCE_PATH@",
///                 "Info": {
///                     "Types": {
///                         "YOUR_CLASS_NAME" : {
///                             "bases": ["NdrDiscoveryPlugin"],
///                             "displayName": "YOUR_DISPLAY_NAME"
///                         }
///                     }
///                 }
///             }]
///         }
///         \endcode
///
///         The NDR ships with one discovery plugin, the
///         `_NdrFilesystemDiscoveryPlugin`. Take a look at NDR's plugInfo.json
///         file for example values for `YOUR_LIBRARY_NAME`, `YOUR_CLASS_NAME`,
///         and `YOUR_DISPLAY_NAME`. If multiple discovery plugins exist in the
///         same folder, you can continue adding additional plugins under the
///         `Types` key in the JSON. More detailed information about the
///         plugInfo.json format can be found in the documentation for the
///         `plug` library (in forge/base).
///     </li>
/// </ul>
///
class NdrDiscoveryPlugin : public TfRefBase, public TfWeakBase
{
public:
    using Context = NdrDiscoveryPluginContext;

    NDR_API
    NdrDiscoveryPlugin();
    NDR_API
    virtual ~NdrDiscoveryPlugin();

    /// Finds and returns all nodes that the implementing plugin should be
    /// aware of.
    NDR_API
    virtual NdrNodeDiscoveryResultVec DiscoverNodes(const Context&) = 0;

    /// Gets the URIs that this plugin is searching for nodes in.
    NDR_API
    virtual const NdrStringVec& GetSearchURIs() const = 0;
};


/// \cond
/// Factory classes should be hidden from the documentation.

class NdrDiscoveryPluginFactoryBase : public TfType::FactoryBase
{
public:
    NDR_API
    virtual NdrDiscoveryPluginRefPtr New() const = 0;
};

template <class T>
class NdrDiscoveryPluginFactory : public NdrDiscoveryPluginFactoryBase
{
public:
    NdrDiscoveryPluginRefPtr New() const override
    {
        return TfCreateRefPtr(new T);
    }
};

/// \endcond

FORGE_NAMESPACE_END

#endif // FORGE_USD_NDR_DISCOVERY_PLUGIN_H
