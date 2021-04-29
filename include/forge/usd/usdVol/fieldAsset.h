#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdVol/fieldAsset.h"
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
#ifndef USDVOL_GENERATED_FIELDASSET_H
#define USDVOL_GENERATED_FIELDASSET_H

/// \file usdVol/fieldAsset.h

#include "forge/forge.h"
#include "forge/usd/usdVol/api.h"
#include "forge/usd/usdVol/fieldBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdVol/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// FIELDASSET                                                                 //
// -------------------------------------------------------------------------- //

/// \class UsdVolFieldAsset
///
/// Base class for field primitives defined by an external file.
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdVolTokens.
/// So to set an attribute to the value "rightHanded", use UsdVolTokens->rightHanded
/// as the value.
///
class UsdVolFieldAsset : public UsdVolFieldBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::AbstractTyped;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::AbstractTyped;

    /// Construct a UsdVolFieldAsset on UsdPrim \p prim .
    /// Equivalent to UsdVolFieldAsset::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdVolFieldAsset(const UsdPrim& prim=UsdPrim())
        : UsdVolFieldBase(prim)
    {
    }

    /// Construct a UsdVolFieldAsset on the prim held by \p schemaObj .
    /// Should be preferred over UsdVolFieldAsset(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdVolFieldAsset(const UsdSchemaBase& schemaObj)
        : UsdVolFieldBase(schemaObj)
    {
    }

    /// Destructor.
    USDVOL_API
    virtual ~UsdVolFieldAsset();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDVOL_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdVolFieldAsset holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdVolFieldAsset(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDVOL_API
    static UsdVolFieldAsset
    Get(const UsdStagePtr &stage, const SdfPath &path);


protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDVOL_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDVOL_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDVOL_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDVOL_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // FILEPATH
    // --------------------------------------------------------------------- //
    /// An asset path attribute that points to a file on disk.
    /// For each supported file format, a separate FieldAsset
    /// subclass is required.
    ///
    /// This attribute's value can be animated over time, as most
    /// volume asset formats represent just a single timeSample of
    /// a volume.  However, it does not, at this time, support
    /// any pattern substitutions like "$F".
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `asset filePath` |
    /// | C++ Type | SdfAssetPath |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Asset |
    USDVOL_API
    UsdAttribute GetFilePathAttr() const;

    /// See GetFilePathAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDVOL_API
    UsdAttribute CreateFilePathAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FIELDNAME
    // --------------------------------------------------------------------- //
    /// Name of an individual field within the file specified by
    /// the filePath attribute.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token fieldName` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    USDVOL_API
    UsdAttribute GetFieldNameAttr() const;

    /// See GetFieldNameAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDVOL_API
    UsdAttribute CreateFieldNameAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FIELDINDEX
    // --------------------------------------------------------------------- //
    /// A file can contain multiple fields with the same
    /// name. This optional attribute is an index used to
    /// disambiguate between these multiple fields with the same
    /// name.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `int fieldIndex` |
    /// | C++ Type | int |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Int |
    USDVOL_API
    UsdAttribute GetFieldIndexAttr() const;

    /// See GetFieldIndexAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDVOL_API
    UsdAttribute CreateFieldIndexAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FIELDDATATYPE
    // --------------------------------------------------------------------- //
    /// Token which is used to indicate the data type of an
    /// individual field. Authors use this to tell consumers more
    /// about the field without opening the file on disk. The list of
    /// allowed tokens is specified with the specific asset type.
    /// A missing value is considered an error.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token fieldDataType` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    USDVOL_API
    UsdAttribute GetFieldDataTypeAttr() const;

    /// See GetFieldDataTypeAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDVOL_API
    UsdAttribute CreateFieldDataTypeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VECTORDATAROLEHINT
    // --------------------------------------------------------------------- //
    /// Optional token which is used to indicate the role of a vector
    /// valued field. This can drive the data type in which fields
    /// are made available in a renderer or whether the vector values
    /// are to be transformed.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token vectorDataRoleHint = "None"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdVolTokens "Allowed Values" | None, Point, Normal, Vector, Color |
    USDVOL_API
    UsdAttribute GetVectorDataRoleHintAttr() const;

    /// See GetVectorDataRoleHintAttr(), and also
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDVOL_API
    UsdAttribute CreateVectorDataRoleHintAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

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
