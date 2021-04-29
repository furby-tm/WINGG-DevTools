#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdUI/window.h"
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

#ifndef USDUI_WINDOW_H
#define USDUI_WINDOW_H

/** @file usdUI/window.h */

#include "forge/forge.h"
#include "forge/usd/usdUI/api.h"
#include "forge/usd/usd/typed.h"
#include "forge/usd/usd/prim.h"
#include "forge/usd/usd/stage.h"
#include "forge/usd/usdUI/tokens.h"

#include "forge/base/vt/value.h"

#include "forge/base/gf/vec3d.h"
#include "forge/base/gf/vec3f.h"
#include "forge/base/gf/matrix4d.h"

#include "forge/base/tf/token.h"
#include "forge/base/tf/type.h"

FORGE_NAMESPACE_BEGIN

class SdfAssetPath;

/*
 * --------------------------------------------------------------------------
 * WINDOW
 * --------------------------------------------------------------------------
 */

/**
 * @class UsdUIWindow
 *
 * Provides a window for the purpose of displaying an application's GUI.
 *
 * For any described attribute @em Fallback @em Value or @em Allowed @em Values below
 * that are text/tokens, the actual token is published and defined in @ref UsdUITokens.
 * So to set an attribute to the value "rightHanded", use UsdUITokens->rightHanded
 * as the value.
 */

class UsdUIWindow : public UsdTyped
{
 public:

  /**
   * Compile time constant representing what kind of schema this class is.
   * @sa UsdSchemaKind
   */

  static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;
  
  /**
   * Construct a UsdUIWindow on UsdPrim @p prim.
   * Equivalent to UsdUIWindow::Get(prim.GetStage(), prim.GetPath())
   * for a @em valid @p prim, but will not immediately throw an error for
   * an invalid @p prim
   */

  explicit UsdUIWindow(const UsdPrim& prim=UsdPrim())
      : UsdTyped(prim)
  {}
  
  /**
   * Construct a UsdUIWindow on the prim held by @p schemaObj .
   * Should be preferred over UsdUIWindow(schemaObj.GetPrim()),
   * as it preserves SchemaBase state.
   */

  explicit UsdUIWindow(const UsdSchemaBase& schemaObj)
      : UsdTyped(schemaObj)
  {}
  
  /** Destructor. */

  USDUI_API
  virtual ~UsdUIWindow();
  
  /**
   * Return a vector of names of all pre-declared attributes for this schema
   * class and all its ancestor classes.  Does not include attributes that
   * may be authored by custom/extended methods of the schemas involved.
   */

  USDUI_API
  static const TfTokenVector &GetSchemaAttributeNames(bool includeInherited=true);
  
  /** 
   * Return a UsdUIWindow holding the prim adhering to this
   * schema at @p path on @p stage.  If no prim exists at @p path on
   * @p stage, or if the prim at that path does not adhere to this schema,
   * return an invalid schema object.  This is shorthand for the following:
   *
   * @code
   * UsdUIWindow(stage->GetPrimAtPath(path));
   * @endcode
   */

  USDUI_API
  static UsdUIWindow Get(const UsdStagePtr &stage, const SdfPath &path);
  
  /** 
   * Attempt to ensure a @a UsdPrim adhering to this schema at @p path
   * is defined (according to UsdPrim::IsDefined()) on this stage.
   *
   * If a prim adhering to this schema at @p path is already defined on this
   * stage, return that prim.  Otherwise author an @a SdfPrimSpec with
   * @a specifier == @a SdfSpecifierDef and this schema's prim type name for
   * the prim at @p path at the current EditTarget.  Author @a SdfPrimSpec s
   * with @p specifier == @a SdfSpecifierDef and empty typeName at the
   * current EditTarget for any nonexistent, or existing but not @a Defined
   * ancestors.
   *
   * The given @a path must be an absolute prim path that does not contain
   * any variant selections.
   *
   * If it is impossible to author any of the necessary PrimSpecs, (for
   * example, in case @a path cannot map to the current UsdEditTarget's
   * namespace) issue an error and return an invalid @a UsdPrim.
   *
   * Note that this method may return a defined prim whose typeName does not
   * specify this schema class, in case a stronger typeName opinion overrides
   * the opinion at the current EditTarget.
   */

  USDUI_API
  static UsdUIWindow Define(const UsdStagePtr &stage, const SdfPath &path);

 protected:

  /**
   * Returns the kind of schema this class belongs to.
   * @sa UsdSchemaKind
   */

  USDUI_API
  UsdSchemaKind _GetSchemaKind() const override;

 private:

  /** needs to invoke _GetStaticTfType. */
  friend class UsdSchemaRegistry;
  
  USDUI_API
  static const TfType &_GetStaticTfType();
  
  static bool _IsTypedSchema();
  
  /** override SchemaBase virtuals. */
  USDUI_API
  const TfType &_GetTfType() const override;

 public:

  /**
   * ---------------------------------------------------------------------
   *  TITLE
   * ---------------------------------------------------------------------
   *  The window title that is displayed on the top of the window. This
   *  window title gives context for what this window is used for.
   *
   *
   *  | ||
   *  | -- | -- |
   *  | Declaration | `uniform token ui:title` |
   *  | C++ Type | TfToken |
   *  | @ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
   *  | @ref SdfVariability "Variability" | SdfVariabilityUniform |
   */

  USDUI_API
  UsdAttribute GetTitleAttr() const;

  /** 
   * See GetTitleAttr(), and also
   * @ref Usd_Create_Or_Get_Property for when to use Get vs Create.
   * If specified, author @p defaultValue as the attribute's default,
   * sparsely (when it makes sense to do so) if @p writeSparsely is @c true -
   * the default for @p writeSparsely is @c false.
   */

  USDUI_API
  UsdAttribute CreateTitleAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

 public:

  /** 
   * =====================================================================
   *  Feel free to add custom code below this line, it will be preserved
   *  by the code generator.
   *
   *  Just remember to:
   *   - Close the class declaration with };
   *   - Close the namespace with FORGE_NAMESPACE_END
   *   - Close the include guard with #endif
   * =====================================================================
   * --(BEGIN CUSTOM CODE)--
   */
  
};

FORGE_NAMESPACE_END

#endif /* USDUI_WINDOW_H */
