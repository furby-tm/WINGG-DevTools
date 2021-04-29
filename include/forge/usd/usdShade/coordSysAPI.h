#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdShade/coordSysAPI.h"
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
#ifndef USDSHADE_GENERATED_COORDSYSAPI_H
#define USDSHADE_GENERATED_COORDSYSAPI_H

/// \file usdShade/coordSysAPI.h

#include "forge/forge.h"
#include "forge/usd/usdShade/api.h"
#include "forge/usd/usd/apiSchemaBase.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdShade/tokens.h"

#include "forge/usd/usdGeom/xformable.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// COORDSYSAPI                                                                //
// -------------------------------------------------------------------------- //

/// \class UsdShadeCoordSysAPI
///
/// UsdShadeCoordSysAPI provides a way to designate, name,
/// and discover coordinate systems.
///
/// Coordinate systems are implicitly established by UsdGeomXformable
/// prims, using their local space.  That coordinate system may be
/// bound (i.e., named) from another prim.  The binding is encoded
/// as a single-target relationship in the "coordSys:" namespace.
/// Coordinate system bindings apply to descendants of the prim
/// where the binding is expressed, but names may be re-bound by
/// descendant prims.
///
/// Named coordinate systems are useful in shading workflows.
/// An example is projection paint, which projects a texture
/// from a certain view (the paint coordinate system).  Using
/// the paint coordinate frame avoids the need to assign a UV
/// set to the object, and can be a concise way to project
/// paint across a collection of objects with a single shared
/// paint coordinate system.
///
/// This is a non-applied API schema.
///
///
class UsdShadeCoordSysAPI : public UsdAPISchemaBase
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::NonAppliedAPI;

    /// \deprecated
    /// Same as schemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    static const UsdSchemaKind schemaType = UsdSchemaKind::NonAppliedAPI;

    /// Construct a UsdShadeCoordSysAPI on UsdPrim \p prim .
    /// Equivalent to UsdShadeCoordSysAPI::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdShadeCoordSysAPI(const UsdPrim& prim=UsdPrim())
        : UsdAPISchemaBase(prim)
    {
    }

    /// Construct a UsdShadeCoordSysAPI on the prim held by \p schemaObj .
    /// Should be preferred over UsdShadeCoordSysAPI(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdShadeCoordSysAPI(const UsdSchemaBase& schemaObj)
        : UsdAPISchemaBase(schemaObj)
    {
    }

    /// Destructor.
    USDSHADE_API
    virtual ~UsdShadeCoordSysAPI();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDSHADE_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdShadeCoordSysAPI holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdShadeCoordSysAPI(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDSHADE_API
    static UsdShadeCoordSysAPI
    Get(const UsdStagePtr &stage, const SdfPath &path);


protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDSHADE_API
    UsdSchemaKind _GetSchemaKind() const override;

    /// \deprecated
    /// Same as _GetSchemaKind, provided to maintain temporary backward
    /// compatibility with older generated schemas.
    USDSHADE_API
    UsdSchemaKind _GetSchemaType() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDSHADE_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDSHADE_API
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

    /// A coordinate system binding.
    /// Binds a name to a coordSysPrim for the bindingPrim
    /// (and its descendants, unless overriden).
    typedef struct {
        TfToken name;
        SdfPath bindingRelPath;
        SdfPath coordSysPrimPath;
    } Binding;

    /// Returns true if the prim has local coordinate system binding
    /// opinions.  Note that the resulting binding list may still be
    /// empty.
    USDSHADE_API
    bool HasLocalBindings() const;

    /// Get the list of coordinate system bindings local to this prim.
    /// This does not process inherited bindings.  It does not
    /// validate that a prim exists at the indicated path.
    /// If the binding relationship has multiple targets,
    /// only the first is used.
    USDSHADE_API
    std::vector<Binding> GetLocalBindings() const;

    /// Find the list of coordinate system bindings that apply
    /// to this prim, including inherited bindings.
    ///
    /// This computation examines this prim and ancestors for
    /// the strongest binding for each name.  A binding expressed by
    /// a child prim supercedes bindings on ancestors.
    ///
    /// Note that this API does not validate the prims at the
    /// target paths; they may be of incorrect type, or missing
    /// entirely.
    ///
    /// Binding relationships with no resolved targets are skipped.
    USDSHADE_API
    std::vector<Binding> FindBindingsWithInheritance() const;

    /// Bind the name to the given path.
    /// The prim at the given path is expected to be UsdGeomXformable,
    /// in order for the binding to be succesfully resolved.
    USDSHADE_API
    bool Bind(const TfToken &name, const SdfPath &path) const;

    /// Clear the indicated coordinate system binding on this prim
    /// from the current edit target.
    ///
    /// Only remove the spec if \p removeSpec is true (leave the spec to
    /// preserve meta-data we may have intentionally authored on the
    /// relationship)
    USDSHADE_API
    bool ClearBinding(const TfToken &name, bool removeSpec) const;

    /// Block the indicated coordinate system binding on this prim
    /// by blocking targets on the underlying relationship.
    USDSHADE_API
    bool BlockBinding(const TfToken &name) const;

    /// Returns the fully namespaced coordinate system relationship
    /// name, given the coordinate system name.
    USDSHADE_API
    static TfToken GetCoordSysRelationshipName(const std::string &coordSysName);

    /// Test whether a given \p name contains the "coordSys:" prefix
    ///
    USDSHADE_API
    static bool CanContainPropertyName(const TfToken &name);
};

FORGE_NAMESPACE_END

#endif
