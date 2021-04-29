#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRi/materialAPI.h"
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
#ifndef USDRI_GENERATED_MATERIALAPI_H
#define USDRI_GENERATED_MATERIALAPI_H

/// \file usdRi/materialAPI.h

#include "forge/forge.h"
#include "forge/usd/usdRi/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRi/tokens.h"

#include "forge/usd/usdShade/input.h"
#include "forge/usd/usdShade/output.h"
#include "forge/usd/usdShade/material.h"


#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// RIMATERIALAPI                                                              //
// -------------------------------------------------------------------------- //

/// \class UsdRiMaterialAPI
///
///
/// \deprecated Materials should use UsdShadeMaterial instead.
/// This schema will be removed in a future release.
///
/// This API provides outputs that connect a material prim to prman
/// shaders and RIS objects.
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdRiTokens.
/// So to set an attribute to the value "rightHanded", use UsdRiTokens->rightHanded
/// as the value.
///
class UsdRiMaterialAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::SingleApplyAPI;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::SingleApplyAPI;

    /// Construct a UsdRiMaterialAPI on UsdPrim \p prim .
    /// Equivalent to UsdRiMaterialAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRiMaterialAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdRiMaterialAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdRiMaterialAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRiMaterialAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDRI_API
    virtual ~UsdRiMaterialAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRI_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRiMaterialAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRiMaterialAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRI_API
    static UsdRiMaterialAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


    /// Applies this <b>single-apply</b> API schema to the given \p prim.
    /// This information is stored by adding "RiMaterialAPI" to the
    /// token-valued, listOp metadata \em apiSchemas on the prim.
    ///
    /// \return A valid UsdRiMaterialAPI object is returned upon success.
    /// An invalid (or empty) UsdRiMaterialAPI object is returned upon
    /// failure. See \ref UsdPrim::ApplyAPI() for conditions
    /// resulting in failure.
    ///
    /// \sa UsdPrim::GetAppliedSchemas()
    /// \sa UsdPrim::HasAPI()
    /// \sa UsdPrim::ApplyAPI()
    /// \sa UsdPrim::RemoveAPI()
    ///
    USDRI_API
    static UsdRiMaterialAPI
    Apply(const UsdPrim &prim);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDRI_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDRI_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDRI_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDRI_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // SURFACE
    // --------------------------------------------------------------------- //
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token outputs:ri:surface` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    USDRI_API
    UsdAttribute GetSurfaceAttr() const;

    /// See GetSurfaceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateSurfaceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // DISPLACEMENT
    // --------------------------------------------------------------------- //
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token outputs:ri:displacement` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    USDRI_API
    UsdAttribute GetDisplacementAttr() const;

    /// See GetDisplacementAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateDisplacementAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VOLUME
    // --------------------------------------------------------------------- //
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token outputs:ri:volume` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    USDRI_API
    UsdAttribute GetVolumeAttr() const;

    /// See GetVolumeAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateVolumeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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

    /// A constructor for creating a MaterialAPI object from a material prim.
    explicit UsdRiMaterialAPI(const UsdShadeMaterial& material)
        : UsdRiMaterialAPI(material.GetPrim())
    {
    }

    // --------------------------------------------------------------------- //
    /// \name Outputs API
    // --------------------------------------------------------------------- //
    /// @{

    /// Returns the "surface" output associated with the material.
    USDRI_API
    UsdShadeOutput GetSurfaceOutput() const;

    /// Returns the "displacement" output associated with the material.
    USDRI_API
    UsdShadeOutput GetDisplacementOutput() const;

    /// Returns the "volume" output associated with the material.
    USDRI_API
    UsdShadeOutput GetVolumeOutput() const;

    /// @}

    // --------------------------------------------------------------------- //
    /// \name API for setting sources of outputs
    // --------------------------------------------------------------------- //
    /// @{

    USDRI_API
    bool SetSurfaceSource(const SdfPath &surfacePath) const;

    USDRI_API
    bool SetDisplacementSource(const SdfPath &displacementPath) const;

    USDRI_API
    bool SetVolumeSource(const SdfPath &volumePath) const;

    /// @}

    // --------------------------------------------------------------------- //
    /// \name Shaders API
    // --------------------------------------------------------------------- //
    /// @{

    /// Returns a valid shader object if the "surface" output on the
    /// material is connected to one.
    ///
    /// If \p ignoreBaseMaterial is true and if the "surface" shader source
    /// is specified in the base-material of this material, then this
    /// returns an invalid shader object.
    USDRI_API
    UsdShadeShader GetSurface(bool ignoreBaseMaterial=false) const;

    /// Returns a valid shader object if the "displacement" output on the
    /// material is connected to one.
    ///
    /// If \p ignoreBaseMaterial is true and if the "displacement" shader source
    /// is specified in the base-material of this material, then this
    /// returns an invalid shader object.
    USDRI_API
    UsdShadeShader GetDisplacement(bool ignoreBaseMaterial=false) const;

    /// Returns a valid shader object if the "volume" output on the
    /// material is connected to one.
    ///
    /// If \p ignoreBaseMaterial is true and if the "volume" shader source
    /// is specified in the base-material of this material, then this
    /// returns an invalid shader object.
    USDRI_API
    UsdShadeShader GetVolume(bool ignoreBaseMaterial=false) const;

    /// @}


    /// Walks the namespace subtree below the material and computes a map
    /// containing the list of all inputs on the material and the associated
    /// vector of consumers of their values. The consumers can be inputs on
    /// shaders within the material or on node-graphs under it.
    USDRI_API
    UsdShadeNodeGraph::InterfaceInputConsumersMap
    ComputeInterfaceInputConsumersMap(
            bool computeTransitiveConsumers=false) const;

    /// @}

private:
    UsdShadeShader _GetSourceShaderObject(const UsdShadeOutput &output,
                                          bool ignoreBaseMaterial) const;

    // Helper method to get the deprecated 'bxdf' output.
    UsdShadeOutput _GetBxdfOutput(const UsdPrim &materialPrim) const;
};

FORGE_NAMESPACE_END

#endif
