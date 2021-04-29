#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/codeGen.h"
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
#ifndef FORGE_IMAGING_HD_PH_CODE_GEN_H
#define FORGE_IMAGING_HD_PH_CODE_GEN_H

#include "forge/forge.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/glslProgram.h"
#include "forge/imaging/hdPh/resourceBinder.h"

#include <map>
#include <sstream>
#include <vector>

FORGE_NAMESPACE_BEGIN

using HdPhShaderCodeSharedPtr = std::shared_ptr<class HdPhShaderCode>;
using HdPhShaderCodeSharedPtrVector = std::vector<HdPhShaderCodeSharedPtr>;
using HdPh_GeometricShaderPtr = std::shared_ptr<class HdPh_GeometricShader>;

/// \class HdPh_CodeGen
///
/// A utility class to compose glsl shader sources and compile them
/// upon request of HdShaderSpec.
///
class HdPh_CodeGen {
 public:
  typedef size_t ID;

  /// Constructor.
  HDPH_API
  HdPh_CodeGen(HdPh_GeometricShaderPtr const &geometricShader,
               HdPhShaderCodeSharedPtrVector const &shaders,
               TfToken const &materialTag);

  /// Constructor for non-geometric use cases.
  /// Don't call compile when constructed this way.
  /// Call CompileComputeProgram instead.
  HDPH_API
  HdPh_CodeGen(HdPhShaderCodeSharedPtrVector const &shaders);

  /// Return the hash value of glsl shader to be generated.
  HDPH_API
  ID ComputeHash() const;

  /// Generate shader source and compile it.
  HDPH_API
  HdPhGLSLProgramSharedPtr Compile(HdPhResourceRegistry *const registry);

  /// Generate compute shader source and compile it.
  /// It uses the compute information in the meta data to determine
  /// layouts needed for a compute program.
  /// The caller should have populated the meta data before calling this
  /// using a method like HdPh_ResourceBinder::ResolveBindings.
  ///
  /// The layout and binding information is combined with the compute stage
  /// shader code from the shader vector to form a resolved shader for
  /// compilation.
  ///
  /// The generated code that is compiled is available for diagnostic
  /// purposes from GetComputeShaderSource.
  ///
  /// \see GetComputeShaderSource
  /// \see HdPh_ResourceBinder::ResolveBindings
  HDPH_API
  HdPhGLSLProgramSharedPtr CompileComputeProgram(HdPhResourceRegistry *const registry);

  /// Return the generated vertex shader source
  const std::string &GetVertexShaderSource() const
  {
    return _vsSource;
  }

  /// Return the generated tess control shader source
  const std::string &GetTessControlShaderSource() const
  {
    return _tcsSource;
  }

  /// Return the generated tess eval shader source
  const std::string &GetTessEvalShaderSource() const
  {
    return _tesSource;
  }

  /// Return the generated geometry shader source
  const std::string &GetGeometryShaderSource() const
  {
    return _gsSource;
  }

  /// Return the generated fragment shader source
  const std::string &GetFragmentShaderSource() const
  {
    return _fsSource;
  }

  /// Return the generated compute shader source
  const std::string &GetComputeShaderSource() const
  {
    return _csSource;
  }

  /// Return the pointer of metadata to be populated by resource binder.
  HdPh_ResourceBinder::MetaData *GetMetaData()
  {
    return &_metaData;
  }

 private:
  void _GenerateDrawingCoord();
  void _GenerateConstantPrimvar();
  void _GenerateInstancePrimvar();
  void _GenerateElementPrimvar();
  void _GenerateVertexAndFaceVaryingPrimvar(bool hasGS);
  void _GenerateShaderParameters();
  void _GenerateTopologyVisibilityParameters();

  HdPh_ResourceBinder::MetaData _metaData;
  HdPh_GeometricShaderPtr _geometricShader;
  HdPhShaderCodeSharedPtrVector _shaders;
  TfToken _materialTag;

  // source buckets
  std::stringstream _genCommon, _genVS, _genTCS, _genTES;
  std::stringstream _genGS, _genFS, _genCS;
  std::stringstream _procVS, _procTCS, _procTES, _procGS;

  // generated sources (for diagnostics)
  std::string _vsSource;
  std::string _tcsSource;
  std::string _tesSource;
  std::string _gsSource;
  std::string _fsSource;
  std::string _csSource;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_CODE_GEN_H
