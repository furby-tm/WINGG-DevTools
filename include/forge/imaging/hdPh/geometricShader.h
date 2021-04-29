#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/geometricShader.h"
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
#ifndef FORGE_IMAGING_HD_PH_GEOMETRIC_SHADER_H
#define FORGE_IMAGING_HD_PH_GEOMETRIC_SHADER_H

#include "forge/forge.h"
#include "forge/imaging/garch/glApi.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/resourceRegistry.h"
#include "forge/imaging/hdPh/shaderCode.h"
#include "forge/imaging/hio/glslfx.h"
#include "forge/usd/sdf/path.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

using HdPh_GeometricShaderSharedPtr = std::shared_ptr<class HdPh_GeometricShader>;
struct HdPh_ShaderKey;

/// \class HdPh_GeometricShader
///
/// Phoenix breaks down the concept of a shader program into distinct
/// conceptual pieces that are then stitched together during code generation.
/// The pieces are:
/// (i)   geometric shader
/// (ii)  material shader
/// (iii) lighting shader
/// (iv)  render pass shader
///
/// The geometric shader contains the entry points for the relevant shader
/// stages and uses geometry opinions (such as cullstyle, double sided, etc)
/// to generate shader code variants via mixins.
///
class HdPh_GeometricShader : public HdPhShaderCode {
 public:
  /// Used in HdPh_CodeGen to generate the appropriate shader source
  enum class PrimitiveType {
    PRIM_POINTS,
    PRIM_BASIS_CURVES_LINES,           // when linear (or) non-refined cubic
    PRIM_BASIS_CURVES_LINEAR_PATCHES,  // refined linear curves
    PRIM_BASIS_CURVES_CUBIC_PATCHES,   // refined cubic curves
    PRIM_MESH_COARSE_TRIANGLES,
    PRIM_MESH_REFINED_TRIANGLES,  // e.g: loop subdiv
    PRIM_MESH_COARSE_QUADS,       // e.g: quadrangulation for ptex
    PRIM_MESH_REFINED_QUADS,      // e.g: catmark/bilinear subdiv
    PRIM_MESH_BSPLINE,            // e.g. catmark limit surface patches
    PRIM_MESH_BOXSPLINETRIANGLE,  // e.g. loop limit surface patches
    PRIM_VOLUME                   // Simply draws triangles of bounding
                                  // box of a volume.
  };

  /// static query functions for PrimitiveType
  static inline bool IsPrimTypePoints(PrimitiveType primType)
  {
    return primType == PrimitiveType::PRIM_POINTS;
  }

  static inline bool IsPrimTypeBasisCurves(PrimitiveType primType)
  {
    return (primType == PrimitiveType::PRIM_BASIS_CURVES_LINES ||
            primType == PrimitiveType::PRIM_BASIS_CURVES_CUBIC_PATCHES ||
            primType == PrimitiveType::PRIM_BASIS_CURVES_LINEAR_PATCHES);
  }

  static inline bool IsPrimTypeMesh(PrimitiveType primType)
  {
    return (primType == PrimitiveType::PRIM_MESH_COARSE_TRIANGLES ||
            primType == PrimitiveType::PRIM_MESH_REFINED_TRIANGLES ||
            primType == PrimitiveType::PRIM_MESH_COARSE_QUADS ||
            primType == PrimitiveType::PRIM_MESH_REFINED_QUADS ||
            primType == PrimitiveType::PRIM_MESH_BSPLINE ||
            primType == PrimitiveType::PRIM_MESH_BOXSPLINETRIANGLE);
  }

  static inline bool IsPrimTypeTriangles(PrimitiveType primType)
  {
    return (primType == PrimitiveType::PRIM_MESH_COARSE_TRIANGLES ||
            primType == PrimitiveType::PRIM_MESH_REFINED_TRIANGLES ||
            primType == PrimitiveType::PRIM_VOLUME);
  }

  static inline bool IsPrimTypeQuads(PrimitiveType primType)
  {
    return (primType == PrimitiveType::PRIM_MESH_COARSE_QUADS ||
            primType == PrimitiveType::PRIM_MESH_REFINED_QUADS);
  }

  static inline bool IsPrimTypePatches(PrimitiveType primType)
  {
    return primType == PrimitiveType::PRIM_MESH_BSPLINE ||
           primType == PrimitiveType::PRIM_MESH_BOXSPLINETRIANGLE ||
           primType == PrimitiveType::PRIM_BASIS_CURVES_CUBIC_PATCHES ||
           primType == PrimitiveType::PRIM_BASIS_CURVES_LINEAR_PATCHES;
  }

  HDPH_API
  HdPh_GeometricShader(std::string const &glslfxString,
                       PrimitiveType primType,
                       HdCullStyle cullStyle,
                       bool useHardwareFaceCulling,
                       bool hasMirroredTransform,
                       bool doubleSided,
                       HdPolygonMode polygonMode,
                       bool cullingPass,
                       SdfPath const &debugId = SdfPath(),
                       float lineWidth = 0);

  HDPH_API
  ~HdPh_GeometricShader() override;

  // HdShader overrides
  HDPH_API
  ID ComputeHash() const override;
  HDPH_API
  std::string GetSource(TfToken const &shaderStageKey) const override;
  HDPH_API
  void BindResources(int program,
                     HdPh_ResourceBinder const &binder,
                     HdRenderPassState const &state) override;

  HDPH_API
  void UnbindResources(int program,
                       HdPh_ResourceBinder const &binder,
                       HdRenderPassState const &state) override;
  HDPH_API
  void AddBindings(HdBindingRequestVector *customBindings) override;

  /// Returns true if this geometric shader is used for GPU frustum culling.
  bool IsFrustumCullingPass() const
  {
    return _frustumCullingPass;
  }

  PrimitiveType GetPrimitiveType() const
  {
    return _primType;
  }

  /// member query functions for PrimitiveType
  inline bool IsPrimTypePoints() const
  {
    return IsPrimTypePoints(_primType);
  }

  inline bool IsPrimTypeBasisCurves() const
  {
    return IsPrimTypeBasisCurves(_primType);
  }

  inline bool IsPrimTypeMesh() const
  {
    return IsPrimTypeMesh(_primType);
  }

  inline bool IsPrimTypeTriangles() const
  {
    return IsPrimTypeTriangles(_primType);
  }

  inline bool IsPrimTypeQuads() const
  {
    return IsPrimTypeQuads(_primType);
  }

  inline bool IsPrimTypePatches() const
  {
    return IsPrimTypePatches(_primType);
  }

  /// Return the GL primitive type of the draw item based on _primType
  HDPH_API
  GLenum GetPrimitiveMode() const;

  // Returns the primitive index size based on the primitive mode
  // 3 for triangles, 4 for quads, 16 for regular b-spline patches etc.
  HDPH_API
  int GetPrimitiveIndexSize() const;

  // Returns the primitive index size for the geometry shader shade
  // 1 for points, 2 for lines, 3 for triangles, 4 for lines_adjacency
  HDPH_API
  int GetNumPrimitiveVertsForGeometryShader() const;

  // Factory for convenience.
  static HdPh_GeometricShaderSharedPtr Create(
      HdPh_ShaderKey const &shaderKey, HdPhResourceRegistrySharedPtr const &resourceRegistry);

 private:
  PrimitiveType _primType;
  HdCullStyle _cullStyle;
  bool _useHardwareFaceCulling;
  bool _hasMirroredTransform;
  bool _doubleSided;
  HdPolygonMode _polygonMode;
  float _lineWidth;

  std::unique_ptr<HioGlslfx> _glslfx;
  bool _frustumCullingPass;
  ID _hash;

  // No copying
  HdPh_GeometricShader(const HdPh_GeometricShader &) = delete;
  HdPh_GeometricShader &operator=(const HdPh_GeometricShader &) = delete;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_GEOMETRIC_SHADER_H
