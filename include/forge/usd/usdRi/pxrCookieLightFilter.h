#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdRi/pxrCookieLightFilter.h"
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
#ifndef USDRI_GENERATED_PXRCOOKIELIGHTFILTER_H
#define USDRI_GENERATED_PXRCOOKIELIGHTFILTER_H

/// \file usdRi/pxrCookieLightFilter.h

#include "forge/forge.h"
#include "forge/usd/usdRi/api.h"
#include "forge/usd/usdLux/lightFilter.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdRi/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// PXRCOOKIELIGHTFILTER                                                       //
// -------------------------------------------------------------------------- //

/// \class UsdRiPxrCookieLightFilter
///
///
/// \deprecated This schema will be replaced in a future release.
/// A textured surface that filters light.
///
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdRiTokens.
/// So to set an attribute to the value "rightHanded", use UsdRiTokens->rightHanded
/// as the value.
///
class UsdRiPxrCookieLightFilter : public UsdLuxLightFilter
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

    /// Construct a UsdRiPxrCookieLightFilter on UsdPrim \p prim .
    /// Equivalent to UsdRiPxrCookieLightFilter::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdRiPxrCookieLightFilter(const UsdPrim& prim=UsdPrim())
        : UsdLuxLightFilter(prim)
    {
    }

    /// Construct a UsdRiPxrCookieLightFilter on the prim held by \p schemaObj .
    /// Should be preferred over UsdRiPxrCookieLightFilter(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdRiPxrCookieLightFilter(const UsdSchemaBase& schemaObj)
        : UsdLuxLightFilter(schemaObj)
    {
    }

    /// Destructor.
    USDRI_API
    virtual ~UsdRiPxrCookieLightFilter();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDRI_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdRiPxrCookieLightFilter holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdRiPxrCookieLightFilter(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDRI_API
    static UsdRiPxrCookieLightFilter
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
    USDRI_API
    static UsdRiPxrCookieLightFilter
    Define(const UsdStagePtr &stage, const SdfPath &path);

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
    // COOKIEMODE
    // --------------------------------------------------------------------- //
    /// Chooses a physical or analytic evaluation model for
    /// the cookie:
    /// - physical: The cookie behaves like a stained glass window
    /// through which light falls. The falloff and blur are determined
    /// by the size of the light, the distance to the light and distance
    /// from the cookie.
    /// - analytic: The cookie has a fixed projection and manual blur
    /// and falloff controls.
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token cookieMode = "physical"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdRiTokens "Allowed Values" | physical, analytic |
    USDRI_API
    UsdAttribute GetCookieModeAttr() const;

    /// See GetCookieModeAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateCookieModeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // WIDTH
    // --------------------------------------------------------------------- //
    /// Width of the rect the light is shining through.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float width = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetWidthAttr() const;

    /// See GetWidthAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateWidthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // HEIGHT
    // --------------------------------------------------------------------- //
    /// Height of the rect the light is shining through.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float height = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetHeightAttr() const;

    /// See GetHeightAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateHeightAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREMAP
    // --------------------------------------------------------------------- //
    /// A color texture to use on the cookie.  May use alpha.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `asset texture:map` |
    /// | C++ Type | SdfAssetPath |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Asset |
    USDRI_API
    UsdAttribute GetTextureMapAttr() const;

    /// See GetTextureMapAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureMapAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREWRAPMODE
    // --------------------------------------------------------------------- //
    /// Specifies what value to use outside the texture's domain:
    /// - off: no repeat
    /// - repeat: repeats in X and Y
    /// - clamp: uses the value from the nearest edge
    ///
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token texture:wrapMode = "off"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdRiTokens "Allowed Values" | off, repeat, clamp |
    USDRI_API
    UsdAttribute GetTextureWrapModeAttr() const;

    /// See GetTextureWrapModeAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureWrapModeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREFILLCOLOR
    // --------------------------------------------------------------------- //
    /// If the texture is not repeating, this specifies the
    /// color for the region outside of and behind the projected rectangle.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `color3f texture:fillColor = (1, 1, 1)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Color3f |
    USDRI_API
    UsdAttribute GetTextureFillColorAttr() const;

    /// See GetTextureFillColorAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureFillColorAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREPREMULTIPLIEDALPHA
    // --------------------------------------------------------------------- //
    /// Textures are usually premultiplied by their alpha. If this not
    /// the case, uncheck this.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool texture:premultipliedAlpha = 1` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetTexturePremultipliedAlphaAttr() const;

    /// See GetTexturePremultipliedAlphaAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTexturePremultipliedAlphaAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREINVERTU
    // --------------------------------------------------------------------- //
    /// Flips the texture from left to right. By default, the
    /// orientation of the texture as seen from the light source matches
    /// the orientation as it is viewed in an image viewer.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool texture:invertU = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetTextureInvertUAttr() const;

    /// See GetTextureInvertUAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureInvertUAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREINVERTV
    // --------------------------------------------------------------------- //
    /// Flips the texture from top to bottom. By default, the
    /// orientation of the texture as seen from the light source matches
    /// the orientation as it is viewed in an image viewer.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool texture:invertV = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetTextureInvertVAttr() const;

    /// See GetTextureInvertVAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureInvertVAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTURESCALEU
    // --------------------------------------------------------------------- //
    /// Scales the U dimension.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float texture:scaleU = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetTextureScaleUAttr() const;

    /// See GetTextureScaleUAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureScaleUAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTURESCALEV
    // --------------------------------------------------------------------- //
    /// Scales the V dimension.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float texture:scaleV = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetTextureScaleVAttr() const;

    /// See GetTextureScaleVAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureScaleVAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREOFFSETU
    // --------------------------------------------------------------------- //
    /// Offsets the texture in the U direction.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float texture:offsetU = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetTextureOffsetUAttr() const;

    /// See GetTextureOffsetUAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureOffsetUAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // TEXTUREOFFSETV
    // --------------------------------------------------------------------- //
    /// Offsets the texture in the V direction.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float texture:offsetV = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetTextureOffsetVAttr() const;

    /// See GetTextureOffsetVAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateTextureOffsetVAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDIRECTIONAL
    // --------------------------------------------------------------------- //
    /// When this is on, the texture projects along a direction
    /// using the orthographic projection. When it is off, the texture
    /// projects using a focal point specified by the analytic:apex.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool analytic:directional = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetAnalyticDirectionalAttr() const;

    /// See GetAnalyticDirectionalAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDirectionalAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICSHEARX
    // --------------------------------------------------------------------- //
    /// Shear the projection along the X axis.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:shearX = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticShearXAttr() const;

    /// See GetAnalyticShearXAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticShearXAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICSHEARY
    // --------------------------------------------------------------------- //
    /// Shear the projection along the Y axis.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:shearY = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticShearYAttr() const;

    /// See GetAnalyticShearYAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticShearYAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICAPEX
    // --------------------------------------------------------------------- //
    /// Distance between the center of cookie and the center of projection.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:apex = 25` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticApexAttr() const;

    /// See GetAnalyticApexAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticApexAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICUSELIGHTDIRECTION
    // --------------------------------------------------------------------- //
    /// When this is on, If this is on, the projection direction
    /// is determined by the position of the center of the light source.
    /// Otherwise, it only follows the orientation of the filter. WARNING:
    /// This does not work with dome and mesh lights.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `bool analytic:useLightDirection = 0` |
    /// | C++ Type | bool |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Bool |
    USDRI_API
    UsdAttribute GetAnalyticUseLightDirectionAttr() const;

    /// See GetAnalyticUseLightDirectionAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticUseLightDirectionAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURAMOUNT
    // --------------------------------------------------------------------- //
    /// Specify the blur of projected texture from 0-1. This
    /// gets multiplied by the blurNear/blurFar interpolation. This
    /// blurs between the projected color and the fill color when the
    /// texture is not repeating.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:amount = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurAmountAttr() const;

    /// See GetAnalyticBlurAmountAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurAmountAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURSMULT
    // --------------------------------------------------------------------- //
    /// Blur multiplier in the S direction.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:sMult = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurSMultAttr() const;

    /// See GetAnalyticBlurSMultAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurSMultAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURTMULT
    // --------------------------------------------------------------------- //
    /// Blur multiplier in the T direction.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:tMult = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurTMultAttr() const;

    /// See GetAnalyticBlurTMultAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurTMultAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURNEARDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance from the cookie where the blur interpolation
    /// starts.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:nearDistance = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurNearDistanceAttr() const;

    /// See GetAnalyticBlurNearDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurNearDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURMIDPOINT
    // --------------------------------------------------------------------- //
    /// Distance between near and far where midValue is located.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:midpoint = 0.5` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurMidpointAttr() const;

    /// See GetAnalyticBlurMidpointAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurMidpointAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURFARDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance from the cookie where the blur interpolation ends.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:farDistance = 10` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurFarDistanceAttr() const;

    /// See GetAnalyticBlurFarDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurFarDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURNEARVALUE
    // --------------------------------------------------------------------- //
    /// Blur multiplier where the blur interpolation starts.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:nearValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurNearValueAttr() const;

    /// See GetAnalyticBlurNearValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurNearValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURMIDVALUE
    // --------------------------------------------------------------------- //
    /// Blur multiplier in the middle of interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:midValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurMidValueAttr() const;

    /// See GetAnalyticBlurMidValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurMidValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLURFARVALUE
    // --------------------------------------------------------------------- //
    /// Blur multiplier at the end of interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:farValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurFarValueAttr() const;

    /// See GetAnalyticBlurFarValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurFarValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICBLUREXPONENT
    // --------------------------------------------------------------------- //
    /// Power exponent of the blur interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:blur:exponent = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticBlurExponentAttr() const;

    /// See GetAnalyticBlurExponentAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticBlurExponentAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYNEARDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance from the cookie where the density
    /// interpolation starts.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:nearDistance = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityNearDistanceAttr() const;

    /// See GetAnalyticDensityNearDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityNearDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYMIDPOINT
    // --------------------------------------------------------------------- //
    /// Distance between near and far where midValue is located.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:midpoint = 0.5` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityMidpointAttr() const;

    /// See GetAnalyticDensityMidpointAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityMidpointAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYFARDISTANCE
    // --------------------------------------------------------------------- //
    /// Distance from the cookie where the density interpolation
    /// ends.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:farDistance = 10` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityFarDistanceAttr() const;

    /// See GetAnalyticDensityFarDistanceAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityFarDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYNEARVALUE
    // --------------------------------------------------------------------- //
    /// Density multiplier where the density interpolation starts.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:nearValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityNearValueAttr() const;

    /// See GetAnalyticDensityNearValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityNearValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYMIDVALUE
    // --------------------------------------------------------------------- //
    /// Density multiplier in the middle of interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:midValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityMidValueAttr() const;

    /// See GetAnalyticDensityMidValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityMidValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYFARVALUE
    // --------------------------------------------------------------------- //
    /// Density multiplier at the end of interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:farValue = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityFarValueAttr() const;

    /// See GetAnalyticDensityFarValueAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityFarValueAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // ANALYTICDENSITYEXPONENT
    // --------------------------------------------------------------------- //
    /// Power exponent of the density interpolation.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float analytic:density:exponent = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetAnalyticDensityExponentAttr() const;

    /// See GetAnalyticDensityExponentAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateAnalyticDensityExponentAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORSATURATION
    // --------------------------------------------------------------------- //
    /// Saturation of the result (0=greyscale, 1=normal,
    /// >1=boosted colors).
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float color:saturation = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetColorSaturationAttr() const;

    /// See GetColorSaturationAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorSaturationAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORMIDPOINT
    // --------------------------------------------------------------------- //
    /// Midpoint for the contrast control.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float color:midpoint = 0.18` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetColorMidpointAttr() const;

    /// See GetColorMidpointAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorMidpointAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORCONTRAST
    // --------------------------------------------------------------------- //
    /// Contrast control (less than 1 = contrast reduction,
    /// larger than 1 = contrast increase).
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float color:contrast = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetColorContrastAttr() const;

    /// See GetColorContrastAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorContrastAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORWHITEPOINT
    // --------------------------------------------------------------------- //
    /// White point for the contrast control if (contrast > 1.0).
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float color:whitepoint = 1` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDRI_API
    UsdAttribute GetColorWhitepointAttr() const;

    /// See GetColorWhitepointAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorWhitepointAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // COLORTINT
    // --------------------------------------------------------------------- //
    /// Tint of the resulting color after saturation, contrast
    /// and clamp.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `color3f color:tint = (1, 1, 1)` |
    /// | C++ Type | GfVec3f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Color3f |
    USDRI_API
    UsdAttribute GetColorTintAttr() const;

    /// See GetColorTintAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDRI_API
    UsdAttribute CreateColorTintAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
};

FORGE_NAMESPACE_END

#endif
