#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdSkel/blendShape.h"
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
#ifndef USDSKEL_GENERATED_BLENDSHAPE_H
#define USDSKEL_GENERATED_BLENDSHAPE_H

/// \file usdSkel/blendShape.h

#include "forge/forge.h"
#include "forge/usd/usdSkel/api.h"
#include "forge/usd/usd/typed.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdSkel/tokens.h"

#include "forge/base/tf/span.h"
#include "forge/usd/usdSkel/inbetweenShape.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// BLENDSHAPE                                                                 //
// -------------------------------------------------------------------------- //

/// \class UsdSkelBlendShape
///
/// Describes a target blend shape, possibly containing inbetween
/// shapes.
///
/// See the extended \ref UsdSkel_BlendShape "Blend Shape Schema
/// documentation for information.
///
///
class UsdSkelBlendShape : public UsdTyped
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

    /// Construct a UsdSkelBlendShape on UsdPrim \p prim .
    /// Equivalent to UsdSkelBlendShape::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdSkelBlendShape(const UsdPrim& prim=UsdPrim())
        : UsdTyped(prim)
    {
    }

    /// Construct a UsdSkelBlendShape on the prim held by \p schemaObj .
    /// Should be preferred over UsdSkelBlendShape(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdSkelBlendShape(const UsdSchemaBase& schemaObj)
        : UsdTyped(schemaObj)
    {
    }

    /// Destructor.
    USDSKEL_API
    virtual ~UsdSkelBlendShape();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDSKEL_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdSkelBlendShape holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdSkelBlendShape(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDSKEL_API
    static UsdSkelBlendShape
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
    USDSKEL_API
    static UsdSkelBlendShape
    Define(const UsdStagePtr &stage, const SdfPath &path);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDSKEL_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDSKEL_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDSKEL_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDSKEL_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // OFFSETS
    // --------------------------------------------------------------------- //
    /// **Required property**. Position offsets which, when added to the
    /// base pose, provides the target shape.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform vector3f[] offsets` |
    /// | C++ Type | VtArray<GfVec3f> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Vector3fArray |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    USDSKEL_API
    UsdAttribute GetOffsetsAttr() const;

    /// See GetOffsetsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDSKEL_API
    UsdAttribute CreateOffsetsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // NORMALOFFSETS
    // --------------------------------------------------------------------- //
    /// **Required property**. Normal offsets which, when added to the
    /// base pose, provides the normals of the target shape.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform vector3f[] normalOffsets` |
    /// | C++ Type | VtArray<GfVec3f> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Vector3fArray |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    USDSKEL_API
    UsdAttribute GetNormalOffsetsAttr() const;

    /// See GetNormalOffsetsAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDSKEL_API
    UsdAttribute CreateNormalOffsetsAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // POINTINDICES
    // --------------------------------------------------------------------- //
    /// **Optional property**. Indices into the original mesh that
    /// correspond to the values in *offsets* and of any inbetween shapes. If
    /// authored, the number of elements must be equal to the number of elements
    /// in the *offsets* array.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform int[] pointIndices` |
    /// | C++ Type | VtArray<int> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->IntArray |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    USDSKEL_API
    UsdAttribute GetPointIndicesAttr() const;

    /// See GetPointIndicesAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDSKEL_API
    UsdAttribute CreatePointIndicesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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

    /// Author scene description to create an attribute on this prim that
    /// will be recognized as an Inbetween (i.e. will present as a valid
    /// UsdSkelInbetweenShape).
    ///
    /// The name of the created attribute or may or may not be the specified
    /// \p attrName, due to the possible need to apply property namespacing.
    /// Creation may fail and return an invalid Inbetwen if \p attrName
    /// contains a reserved keyword.
    ///
    /// \return an invalid UsdSkelInbetweenShape if we failed to create a valid
    /// attribute, a valid UsdSkelInbetweenShape otherwise. It is not an error
    /// to create over an existing, compatible attribute.
    ///
    /// \sa UsdSkelInbetweenShape::IsInbetween()
    USDSKEL_API
    UsdSkelInbetweenShape CreateInbetween(const TfToken& name) const;

    /// Return the Inbetween corresponding to the attribute named \p name,
    /// which will be valid if an Inbetween attribute definition already exists.
    ///
    /// Name lookup will account for Inbetween namespacing, which means that
    /// this method will succeed in some cases where
    /// `UsdSkelInbetweenShape(prim->GetAttribute(name))` will not, unless
    /// \p name has the proper namespace prefix.
    ///
    /// \sa HasInbetween()
    USDSKEL_API
    UsdSkelInbetweenShape GetInbetween(const TfToken& name) const;

    /// Return true if there is a defined Inbetween named \p name on this prim.
    ///
    /// Name lookup will account for Inbetween namespacing.
    ///
    /// \sa GetInbetween()
    USDSKEL_API
    bool HasInbetween(const TfToken& name) const;

    /// Return valid UsdSkelInbetweenShape objects for all defined Inbetweens on
    /// this prim.
    USDSKEL_API
    std::vector<UsdSkelInbetweenShape> GetInbetweens() const;

    /// Like GetInbetweens(), but exclude inbetwens that have no authored scene
    //// description.
    USDSKEL_API
    std::vector<UsdSkelInbetweenShape> GetAuthoredInbetweens() const;

    /// Validates a set of point indices for a given point count.
    /// This ensures that all point indices are in the range [0, numPoints).
    /// Returns true if the indices are valid, or false otherwise.
    /// If invalid and \p reason is non-null, an error message describing
    /// the first validation error will be set.
    USDSKEL_API
    static bool ValidatePointIndices(TfSpan<const int> indices,
                                     size_t numPoints,
                                     std::string* reason=nullptr);

private:
    std::vector<UsdSkelInbetweenShape>
    _MakeInbetweens(const std::vector<UsdProperty>& props) const;
};

FORGE_NAMESPACE_END

#endif
