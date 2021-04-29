#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdShade/utils.h"
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
#ifndef FORGE_USD_USD_SHADE_UTILS_H
#define FORGE_USD_USD_SHADE_UTILS_H

#include "forge/forge.h"
#include "forge/usd/usdShade/api.h"
#include "forge/usd/usdShade/types.h"
#include "forge/usd/usd/attribute.h"

#include "forge/base/tf/smallVector.h"
#include "forge/base/tf/token.h"

#include <string>
#include <utility>

FORGE_NAMESPACE_BEGIN

class UsdShadeInput;
class UsdShadeOutput;

/// \class UsdShadeUtils
///
/// This class contains a set of utility functions used when authoring and
/// querying shading networks.
///
class UsdShadeUtils {
public:
    /// Returns the namespace prefix of the USD attribute associated with the
    /// given shading attribute type.
    USDSHADE_API
    static std::string GetPrefixForAttributeType(
        UsdShadeAttributeType sourceType);

    /// Given the full name of a shading attribute, returns it's base name and
    /// shading attribute type.
    USDSHADE_API
    static std::pair<TfToken, UsdShadeAttributeType>
        GetBaseNameAndType(const TfToken &fullName);

    /// Given the full name of a shading attribute, returns its shading
    /// attribute type.
    USDSHADE_API
    static UsdShadeAttributeType GetType(const TfToken &fullName);

    /// Returns the full shading attribute name given the basename and the
    /// shading attribute type. \p baseName is the name of the input or output
    /// on the shading node. \p type is the \ref UsdShadeAttributeType of the
    /// shading attribute.
    USDSHADE_API
    static TfToken GetFullName(const TfToken &baseName,
                               const UsdShadeAttributeType type);

    /// \brief Find what is connected to an Input or Output recursively
    ///
    /// GetValueProducingAttributes implements the UsdShade connectivity rules
    /// described in \ref UsdShadeAttributeResolution .
    ///
    /// When tracing connections within networks that contain containers like
    /// UsdShadeNodeGraph nodes, the actual output(s) or value(s) at the end of
    /// an input or output might be multiple connections removed. The methods
    /// below resolves this across multiple physical connections.
    ///
    /// An UsdShadeInput is getting its value from one of these sources:
    /// - If the input is not connected the UsdAttribute for this input is
    /// returned, but only if it has an authored value. The input attribute
    /// itself carries the value for this input.
    /// - If the input is connected we follow the connection(s) until we reach
    /// a valid output of a UsdShadeShader node or if we reach a valid
    /// UsdShadeInput attribute of a UsdShadeNodeGraph or UsdShadeMaterial that
    /// has an authored value.
    ///
    /// An UsdShadeOutput on a container can get its value from the same
    /// type of sources as a UsdShadeInput on either a UsdShadeShader or
    /// UsdShadeNodeGraph. Outputs on non-containers (UsdShadeShaders) cannot be
    /// connected.
    ///
    /// This function returns a vector of UsdAttributes. The vector is empty if
    /// no valid attribute was found. The type of each attribute can be
    /// determined with the \p UsdShadeUtils::GetType function.
    ///
    /// If \p shaderOutputsOnly is true, it will only report attributes that are
    /// outputs of non-containers (UsdShadeShaders). This is a bit faster and
    /// what is need when determining the connections for Material terminals.
    ///
    /// \note This will return the last attribute along the connection chain
    /// that has an authored value, which might not be the last attribute in the
    /// chain itself.
    /// \note When the network contains multi-connections, this function can
    /// return multiple attributes for a single input or output. The list of
    /// attributes is build by a depth-first search, following the underlying
    /// connection paths in order. The list can contain both UsdShadeOutput and
    /// UsdShadeInput attributes. It is up to the caller to decide how to
    /// process such a mixture.
    USDSHADE_API
    static UsdShadeAttributeVector GetValueProducingAttributes(
        UsdShadeInput const &input,
        bool shaderOutputsOnly = false);
    /// \overload
    USDSHADE_API
    static UsdShadeAttributeVector GetValueProducingAttributes(
        UsdShadeOutput const &output,
        bool shaderOutputsOnly = false);
};

FORGE_NAMESPACE_END

#endif
