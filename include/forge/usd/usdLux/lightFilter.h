#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdLux/lightFilter.h"
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
#ifndef USDLUX_GENERATED_LIGHTFILTER_H
#define USDLUX_GENERATED_LIGHTFILTER_H

/// \file usdLux/lightFilter.h

#include "forge/forge.h"
#include "forge/usd/usdLux/api.h"
#include "forge/usd/usdGeom/xformable.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdLux/tokens.h"

#include "forge/usd/usd/collectionAPI.h"
#include "forge/usd/usdShade/input.h"
#include "forge/usd/usdShade/output.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// LIGHTFILTER                                                                //
// -------------------------------------------------------------------------- //

/// \class UsdLuxLightFilter
///
/// A light filter modifies the effect of a light.
/// Lights refer to filters via relationships so that filters may be
/// shared.
///
/// <b>Linking</b>
///
/// Filters can be linked to geometry.  Linking controls which geometry
/// a light-filter affects, when considering the light filters attached
/// to a light illuminating the geometry.
///
/// Linking is specified as a collection (UsdCollectionAPI) which can
/// be accessed via GetFilterLinkCollection().
///
///
class UsdLuxLightFilter : public UsdGeomXformable
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::ConcreteTyped;

    /// Construct a UsdLuxLightFilter on UsdPrim \p prim .
    /// Equivalent to UsdLuxLightFilter::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdLuxLightFilter(const UsdPrim& prim=UsdPrim())
        : UsdGeomXformable(prim)
    {
    }

    /// Construct a UsdLuxLightFilter on the prim held by \p schemaObj .
    /// Should be preferred over UsdLuxLightFilter(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdLuxLightFilter(const UsdSchemaBase& schemaObj)
        : UsdGeomXformable(schemaObj)
    {
    }

    /// Destructor.
    USDLUX_API
    virtual ~UsdLuxLightFilter();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDLUX_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdLuxLightFilter holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdLuxLightFilter(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDLUX_API
    static UsdLuxLightFilter
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Attempt to ensure a \a UsdPrim adhering to this schema at \p path
    /// is defined (according to UsdPrim::IsDefined()) on this stage.
    ///
    /// If a prim adhering to this schema at \p path is already defined on this
    /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
    /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
    /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
    /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
    /// current EditTarget for any nonexistent, or existing but not \a Defined
    /// ancestors.
    ///
    /// The given \a path must be an absolute prim path that does not contain
    /// any variant selections.
    ///
    /// If it is impossible to author any of the necessary PrimSpecs, (for
    /// example, in case \a path cannot map to the current UsdEditTarget's
    /// namespace) issue an error and return an invalid \a UsdPrim.
    ///
    /// Note that this method may return a defined prim whose typeName does not
    /// specify this schema class, in case a stronger typeName opinion overrides
    /// the opinion at the current EditTarget.
    ///
    USDLUX_API
    static UsdLuxLightFilter
    Define(const UsdStagePtr &stage, const SdfPath &path);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDLUX_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDLUX_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDLUX_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDLUX_API
    const TfType &_GetTfType() const override;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by
    // the code generator.
    //
    // Just remember to:
    //  - Close the class declaration with };
    //  - Close the namespace with FORGE_NAMESPACE_END
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--

    // -------------------------------------------------------------------------
    /// \name Conversion to and from UsdShadeConnectableAPI
    ///
    /// @{

    /// Constructor that takes a ConnectableAPI object.
    /// Allow implicit conversion of UsdShadeConnectableAPI to
    /// UsdLuxLightFilter.
    USDLUX_API
    UsdLuxLightFilter(const UsdShadeConnectableAPI &connectable);

    /// Contructs and returns a UsdShadeConnectableAPI object with this light
    /// filter.
    ///
    /// Note that most tasks can be accomplished without explicitly constructing
    /// a UsdShadeConnectable API, since connection-related API such as
    /// UsdShadeConnectableAPI::ConnectToSource() are static methods, and
    /// UsdLuxLightFilter will auto-convert to a UsdShadeConnectableAPI when
    /// passed to functions that want to act generically on a connectable
    /// UsdShadeConnectableAPI object.
    USDLUX_API
    UsdShadeConnectableAPI ConnectableAPI() const;

    /// @}

    // -------------------------------------------------------------------------
    /// \name Outputs API
    ///
    /// Outputs represent a typed attribute on a light filter whose value is
    /// computed externally.
    ///
    /// @{

    /// Create an output which can either have a value or can be connected.
    /// The attribute representing the output is created in the "outputs:"
    /// namespace. Outputs on a light filter cannot be connected, as their
    /// value is assumed to be computed externally.
    ///
    USDLUX_API
    UsdShadeOutput CreateOutput(const TfToken& name,
                                const SdfValueTypeName& typeName);

    /// Return the requested output if it exists.
    ///
    USDLUX_API
    UsdShadeOutput GetOutput(const TfToken &name) const;

    /// Outputs are represented by attributes in the "outputs:" namespace.
    /// If \p onlyAuthored is true (the default), then only return authored
    /// attributes; otherwise, this also returns un-authored builtins.
    ///
    USDLUX_API
    std::vector<UsdShadeOutput> GetOutputs(bool onlyAuthored=true) const;

    /// @}

    // -------------------------------------------------------------------------

    /// \name Inputs API
    ///
    /// Inputs are connectable attribute with a typed value.
    ///
    /// Light filter parameters are encoded as inputs.
    ///
    /// @{

    /// Create an input which can either have a value or can be connected.
    /// The attribute representing the input is created in the "inputs:"
    /// namespace. Inputs on light filters are connectable.
    ///
    USDLUX_API
    UsdShadeInput CreateInput(const TfToken& name,
                              const SdfValueTypeName& typeName);

    /// Return the requested input if it exists.
    ///
    USDLUX_API
    UsdShadeInput GetInput(const TfToken &name) const;

    /// Inputs are represented by attributes in the "inputs:" namespace.
    /// If \p onlyAuthored is true (the default), then only return authored
    /// attributes; otherwise, this also returns un-authored builtins.
    ///
    USDLUX_API
    std::vector<UsdShadeInput> GetInputs(bool onlyAuthored=true) const;

    /// @}

    /// Return the UsdCollectionAPI interface used for examining and
    /// modifying the filter-linking of this light filter.  Linking
    /// controls which geometry this light filter affects.
    USDLUX_API
    UsdCollectionAPI GetFilterLinkCollectionAPI() const;
};

FORGE_NAMESPACE_END

#endif
