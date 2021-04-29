#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/dynamicFileFormatDependencyData.h"
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
#ifndef FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_DEPENDENCY_DATA_H
#define FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_DEPENDENCY_DATA_H

#include "forge/forge.h"
#include "forge/usd/pcp/api.h"
#include "forge/base/tf/declarePtrs.h"
#include "forge/base/tf/token.h"

#include <memory>
#include <vector>

FORGE_NAMESPACE_BEGIN

class PcpDynamicFileFormatInterface;
class VtValue;

TF_DECLARE_WEAK_PTRS(SdfFileFormat);

/// \class PcpDynamicFileFormatDependencyData
///
/// Contains the necessary information for storing a prim index's dependency
/// on dynamic file format arguments and determining if a field change affects
/// the prim index. This data structure does not store the prim index or its
/// path itself and is expected to be the data in some other data structure
/// that maps prim indexes to its dependencies.
///
class PcpDynamicFileFormatDependencyData
{
public:
    /// Default constructor. This data will be empty.
    PCP_API
    PcpDynamicFileFormatDependencyData() = default;

    /// Move constructor.
    PCP_API
    PcpDynamicFileFormatDependencyData(
        PcpDynamicFileFormatDependencyData &&) = default;

    /// Copy constructor.
    PCP_API
    PcpDynamicFileFormatDependencyData(
        const PcpDynamicFileFormatDependencyData &rhs);

    /// Move assignment operator
    PcpDynamicFileFormatDependencyData &operator=(
        PcpDynamicFileFormatDependencyData &&rhs) {
        Swap(rhs);
        return *this;
    }

    /// Copy assignment operator
    PcpDynamicFileFormatDependencyData &operator=(
        const PcpDynamicFileFormatDependencyData &rhs) {
        PcpDynamicFileFormatDependencyData(rhs).Swap(*this);
        return *this;
    }

    /// Swap the contents of this dependency data with \p rhs.
    inline void Swap(PcpDynamicFileFormatDependencyData& rhs) {
        _data.swap(rhs._data);
    }

    /// Same as Swap(), but standard name.
    inline void swap(PcpDynamicFileFormatDependencyData &rhs) { Swap(rhs); }

    /// Returns whether this dependency data is empty.
    inline bool IsEmpty() const {
        return !_data;
    }

    /// Adds dependency info from a single context that generated dynamic file
    /// format arguments (usually a payload arc in the graph).
    /// \p dynamicFileFormat is the file format that generated the arguments.
    /// \p dependencyContextData is custom dependency information generated when
    /// the file format generated its arguments. \p composedFieldNames is a
    /// list of the fields that were composed on the prim to generate arguments.
    PCP_API
    void AddDependencyContext(
        const PcpDynamicFileFormatInterface *dynamicFileFormat,
        VtValue &&dependencyContextData,
        TfToken::Set &&composedFieldNames);

    /// Takes all the dependency data from \p dependencyData and adds it to this
    /// dependency.
    PCP_API
    void AppendDependencyData(
        PcpDynamicFileFormatDependencyData &&dependencyData);

    /// Returns a list of field names that were composed for any of the
    /// dependency contexts that were added to this dependency.
    PCP_API
    const TfToken::Set &GetRelevantFieldNames() const;

    /// Given a \p field name and the changed field values in \p oldAndNewValues
    /// this return whether this change can affect any of the file format
    /// arguments generated by any of the contexts stored in this dependency.
    PCP_API
    bool CanFieldChangeAffectFileFormatArguments(const TfToken &fieldName,
                                                 const VtValue& oldValue,
                                                 const VtValue& newValue) const;

private:
    // Struct containing the entire contents of the dependency.
    struct _Data
    {
        using _ContextData =
            std::pair<const PcpDynamicFileFormatInterface *, VtValue>;
        using _ContextDataVector = std::vector<_ContextData>;

        _ContextDataVector dependencyContexts;
        TfToken::Set relevantFieldNames;

        // Helper for adding relevant fields. We avoid copying by taking the
        // input set if our set is empty.
        void _AddRelevantFieldNames(TfToken::Set &&fieldNames);
    };

    // Pointer to data. Will be null if this an empty data object.
    std::unique_ptr<_Data> _data;
};

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_DYNAMIC_FILE_FORMAT_DEPENDENCY_DATA_H
