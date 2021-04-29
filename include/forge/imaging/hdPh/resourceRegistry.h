#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/resourceRegistry.h"
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
#ifndef FORGE_IMAGING_HD_PH_RESOURCE_REGISTRY_H
#define FORGE_IMAGING_HD_PH_RESOURCE_REGISTRY_H

#include "forge/base/vt/dictionary.h"
#include "forge/forge.h"

#include "forge/imaging/hdPh/api.h"

#include "forge/imaging/hgi/hgi.h"

#include "forge/imaging/hd/bufferArrayRange.h"
#include "forge/imaging/hd/bufferArrayRegistry.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/enums.h"
#include "forge/imaging/hd/instanceRegistry.h"
#include "forge/imaging/hd/resourceRegistry.h"

#if !defined(Q_MOC_RUN)
# include <tbb/concurrent_vector.h>
#endif /* Q_MOC_RUN */

#include <atomic>
#include <map>
#include <memory>

FORGE_NAMESPACE_BEGIN

using HdComputationSharedPtr = std::shared_ptr<class HdComputation>;
using HdPhDispatchBufferSharedPtr = std::shared_ptr<class HdPhDispatchBuffer>;
using HdPhGLSLProgramSharedPtr = std::shared_ptr<class HdPhGLSLProgram>;
using HioGlslfxSharedPtr = std::shared_ptr<class HioGlslfx>;

using HdPh_BasisCurvesTopologySharedPtr = std::shared_ptr<class HdPh_BasisCurvesTopology>;

using HdPhShaderCodePtr = std::weak_ptr<class HdPhShaderCode>;
using HdPh_GeometricShaderSharedPtr = std::shared_ptr<class HdPh_GeometricShader>;

using HdPhTextureHandleSharedPtr = std::shared_ptr<class HdPhTextureHandle>;
using HdPhTextureObjectSharedPtr = std::shared_ptr<class HdPhTextureObject>;
using HdPhBufferResourceSharedPtr = std::shared_ptr<class HdPhBufferResource>;
using HdPhResourceRegistrySharedPtr = std::shared_ptr<class HdPhResourceRegistry>;
using Hd_VertexAdjacencySharedPtr = std::shared_ptr<class Hd_VertexAdjacency>;
using HdPh_MeshTopologySharedPtr = std::shared_ptr<class HdPh_MeshTopology>;
using HgiResourceBindingsSharedPtr = std::shared_ptr<HgiResourceBindingsHandle>;
using HgiGraphicsPipelineSharedPtr = std::shared_ptr<HgiGraphicsPipelineHandle>;
using HgiComputePipelineSharedPtr = std::shared_ptr<HgiComputePipelineHandle>;

class HdPhTextureIdentifier;
class HdSamplerParameters;

/// \enum HdPhComputeQueue
///
/// Determines the 'compute queue' a computation should be added into.
///
/// We only perform synchronization between queues, not within one queue.
/// In OpenGL terms that means we insert memory barriers between computations
/// of two queues, but not between two computations in the same queue.
///
/// A prim determines the role for each queue based on its local knowledge of
/// compute dependencies. Eg. HdPhMesh knows computing normals should wait
/// until the primvar refinement computation has fnished. It can assign one
/// queue to primvar refinement and a following queue for normal computations.
///
enum HdPhComputeQueue {
  HdPhComputeQueueZero = 0,
  HdPhComputeQueueOne,
  HdPhComputeQueueTwo,
  HdPhComputeQueueThree,
  HdPhComputeQueueCount
};

using HdPhComputationSharedPtrVector =
    std::vector<std::pair<HdComputationSharedPtr, HdPhComputeQueue>>;

/// \class HdPhResourceRegistry
///
/// A central registry of all GPU resources.
///
class HdPhResourceRegistry final : public HdResourceRegistry {
 public:
  HF_MALLOC_TAG_NEW("new HdPhResourceRegistry");

  HDPH_API
  explicit HdPhResourceRegistry(Hgi *hgi);

  HDPH_API
  ~HdPhResourceRegistry() override;

  HDPH_API
  void InvalidateShaderRegistry() override;

  HDPH_API
  void ReloadResource(TfToken const &resourceType, std::string const &path) override;

  HDPH_API
  VtDictionary GetResourceAllocation() const override;

  /// Returns Hgi used to create/destroy GPU resources.
  HDPH_API
  Hgi *GetHgi();

  /// ------------------------------------------------------------------------
  /// Texture allocation API
  /// ------------------------------------------------------------------------
  ///

  /// Allocate texture handle (encapsulates texture and sampler
  /// object, bindless texture sampler handle, memory request and
  /// callback to shader).
  ///
  /// The actual allocation of the associated GPU texture and
  /// sampler resources and loading of the texture file is delayed
  /// until the commit phase.
  HDPH_API
  HdPhTextureHandleSharedPtr AllocateTextureHandle(
      /// Path to file and information to identify a texture if the
      /// file is a container for several textures (e.g., OpenVDB
      /// file containing several grids, movie file containing frames).
      const HdPhTextureIdentifier &textureId,
      /// Texture type, e.g., uv, ptex, ...
      HdTextureType textureType,
      /// Sampling parameters such as wrapS, ...
      /// wrapS, wrapT, wrapR mode, min filer, mag filter
      const HdSamplerParameters &samplerParams,
      /// Memory request. The texture is down-sampled to meet the
      /// target memory which is the maximum of all memory requests
      /// associated to the texture.
      /// If all memory requests are 0, no down-sampling will happen.
      size_t memoryRequest,
      /// Also create a GL texture sampler handle for bindless
      /// textures.
      bool createBindlessHandle,
      /// After the texture is committed (or after it has been
      /// changed) the given shader code can add additional buffer
      /// sources and computations using the texture metadata with
      /// AddResourcesFromTextures.
      HdPhShaderCodePtr const &shaderCode);

  /// Allocate texture object.
  ///
  /// The actual allocation of the associated GPU texture and
  /// sampler resources and loading of the texture file is delayed
  /// until the commit phase.
  HDPH_API
  HdPhTextureObjectSharedPtr AllocateTextureObject(
      /// Path to file and information to identify a texture if the
      /// file is a container for several textures (e.g., OpenVDB
      /// file containing several grids, movie file containing frames).
      const HdPhTextureIdentifier &textureId,
      /// Texture type, e.g., uv, ptex, ...
      HdTextureType textureType);

  /// Sets how much memory a single texture can consume in bytes by
  /// texture type.
  ///
  /// Only has an effect if non-zero and only applies to textures if
  /// no texture handle referencing the texture has a memory
  /// request.
  ///
  HDPH_API
  void SetMemoryRequestForTextureType(HdTextureType textureType, size_t memoryRequest);

  /// ------------------------------------------------------------------------
  /// BAR allocation API
  /// ------------------------------------------------------------------------
  ///
  /// The Allocate* flavor of methods allocate a new BAR for the given buffer
  /// specs using the chosen aggregation strategy.

  HDPH_API
  HdBufferArrayRangeSharedPtr AllocateNonUniformBufferArrayRange(
      TfToken const &role,
      HdBufferSpecVector const &bufferSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr AllocateNonUniformImmutableBufferArrayRange(
      TfToken const &role,
      HdBufferSpecVector const &bufferSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr AllocateUniformBufferArrayRange(
      TfToken const &role,
      HdBufferSpecVector const &bufferSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr AllocateShaderStorageBufferArrayRange(
      TfToken const &role,
      HdBufferSpecVector const &bufferSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr AllocateSingleBufferArrayRange(TfToken const &role,
                                                             HdBufferSpecVector const &bufferSpecs,
                                                             HdBufferArrayUsageHint usageHint);

  /// ------------------------------------------------------------------------
  /// BAR allocation/migration/update API
  /// ------------------------------------------------------------------------
  ///
  /// The Update* flavor of methods handle both allocation of a new BAR and
  /// reallocation-migration based on the existing range, updated/added specs,
  /// removed specs and usage hint. This allows client code to be less verbose
  /// when a range's signature (specs) can change.
  ///
  /// If \p curRange is invalid, this is equivalent to calling Allocate*.
  /// Otherwise, checks if \p curRange needs to be migrated to a new range
  /// (based on \p updatedOrAddedSpecs and \p removedSpecs and \p usageHint).
  /// If migration is necessary, allocate a new range and register necessary
  /// migration computations and return the new range.
  /// Otherwise, just return the same range.

  HDPH_API
  HdBufferArrayRangeSharedPtr UpdateNonUniformBufferArrayRange(
      TfToken const &role,
      HdBufferArrayRangeSharedPtr const &curRange,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr UpdateNonUniformImmutableBufferArrayRange(
      TfToken const &role,
      HdBufferArrayRangeSharedPtr const &curRange,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr UpdateUniformBufferArrayRange(
      TfToken const &role,
      HdBufferArrayRangeSharedPtr const &curRange,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayUsageHint usageHint);

  HDPH_API
  HdBufferArrayRangeSharedPtr UpdateShaderStorageBufferArrayRange(
      TfToken const &role,
      HdBufferArrayRangeSharedPtr const &curRange,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayUsageHint usageHint);

  /// ------------------------------------------------------------------------
  /// Resource update & computation queuing API
  /// ------------------------------------------------------------------------

  /// Append source data for given range to be committed later.
  HDPH_API
  void AddSources(HdBufferArrayRangeSharedPtr const &range,
                  HdBufferSourceSharedPtrVector &&sources);

  /// Append a source data for given range to be committed later.
  HDPH_API
  void AddSource(HdBufferArrayRangeSharedPtr const &range, HdBufferSourceSharedPtr const &source);

  /// Append a source data just to be resolved (used for cpu computations).
  HDPH_API
  void AddSource(HdBufferSourceSharedPtr const &source);

  /// Append a gpu computation into queue.
  /// The parameter 'range' specifies the destination buffer range,
  /// which has to be allocated by caller of this function.
  ///
  /// note: GPU computations will be executed in the order that
  /// they are registered.
  HDPH_API
  void AddComputation(HdBufferArrayRangeSharedPtr const &range,
                      HdComputationSharedPtr const &computation,
                      HdPhComputeQueue const queue);

  /// ------------------------------------------------------------------------
  /// Dispatch & buffer API
  /// ------------------------------------------------------------------------

  /// Register a buffer allocated with \a count * \a commandNumUints *
  /// sizeof(uint32_t) to be used as an indirect dispatch buffer.
  HDPH_API
  HdPhDispatchBufferSharedPtr RegisterDispatchBuffer(TfToken const &role,
                                                     int count,
                                                     int commandNumUints);

  /// Register a misc buffer resource.
  /// Usually buffers are part of a buffer array (buffer aggregation) and are
  /// managed via buffer array APIs.
  /// RegisterBufferResource lets you create a standalone buffer that can
  /// be used for misc purposes (Eg. GPU frustum cull prim count read back).
  HDPH_API
  HdPhBufferResourceSharedPtr RegisterBufferResource(TfToken const &role, HdTupleType tupleType);

  /// Remove any entries associated with expired dispatch buffers.
  HDPH_API
  void GarbageCollectDispatchBuffers();

  /// Remove any entries associated with expired misc buffers.
  HDPH_API
  void GarbageCollectBufferResources();

  /// ------------------------------------------------------------------------
  /// Instance Registries
  /// ------------------------------------------------------------------------

  /// These registries implement sharing and deduplication of data based
  /// on computed hash identifiers. Each returned HdInstance object retains
  /// a shared pointer to a data instance. When an HdInstance is registered
  /// for a previously unused ID, the data pointer will be null and it is
  /// the caller's responsibility to set its value. The instance registries
  /// are cleaned of unreferenced entries during garbage collection.
  ///
  /// Note: As entries can be registered from multiple threads, the returned
  /// object holds a lock on the instance registry. This lock is held
  /// until the returned HdInstance object is destroyed.

  /// Topology instancing
  HDPH_API
  HdInstance<HdPh_MeshTopologySharedPtr> RegisterMeshTopology(
      HdInstance<HdPh_MeshTopologySharedPtr>::ID id);

  HDPH_API
  HdInstance<HdPh_BasisCurvesTopologySharedPtr> RegisterBasisCurvesTopology(
      HdInstance<HdPh_BasisCurvesTopologySharedPtr>::ID id);

  HDPH_API
  HdInstance<Hd_VertexAdjacencySharedPtr> RegisterVertexAdjacency(
      HdInstance<Hd_VertexAdjacencySharedPtr>::ID id);

  /// Topology Index buffer array range instancing
  /// Returns the HdInstance points to shared HdBufferArrayRange,
  /// distinguished by given ID.
  /// *Refer the comment on RegisterTopology for the same consideration.
  HDPH_API
  HdInstance<HdBufferArrayRangeSharedPtr> RegisterMeshIndexRange(
      HdInstance<HdBufferArrayRangeSharedPtr>::ID id, TfToken const &name);

  HDPH_API
  HdInstance<HdBufferArrayRangeSharedPtr> RegisterBasisCurvesIndexRange(
      HdInstance<HdBufferArrayRangeSharedPtr>::ID id, TfToken const &name);

  /// Primvar array range instancing
  /// Returns the HdInstance pointing to shared HdBufferArrayRange,
  /// distinguished by given ID.
  /// *Refer the comment on RegisterTopology for the same consideration.
  HDPH_API
  HdInstance<HdBufferArrayRangeSharedPtr> RegisterPrimvarRange(
      HdInstance<HdBufferArrayRangeSharedPtr>::ID id);

  /// ExtComputation data array range instancing
  /// Returns the HdInstance pointing to shared HdBufferArrayRange,
  /// distinguished by given ID.
  /// *Refer the comment on RegisterTopology for the same consideration.
  HDPH_API
  HdInstance<HdBufferArrayRangeSharedPtr> RegisterExtComputationDataRange(
      HdInstance<HdBufferArrayRangeSharedPtr>::ID id);

  /// Register a geometric shader.
  HDPH_API
  HdInstance<HdPh_GeometricShaderSharedPtr> RegisterGeometricShader(
      HdInstance<HdPh_GeometricShaderSharedPtr>::ID id);

  /// Register a GLSL program into the program registry.
  HDPH_API
  HdInstance<HdPhGLSLProgramSharedPtr> RegisterGLSLProgram(
      HdInstance<HdPhGLSLProgramSharedPtr>::ID id);

  /// Register a GLSLFX file.
  HDPH_API
  HdInstance<HioGlslfxSharedPtr> RegisterGLSLFXFile(HdInstance<HioGlslfxSharedPtr>::ID id);

  /// Register a Hgi resource bindings into the registry.
  HDPH_API
  HdInstance<HgiResourceBindingsSharedPtr> RegisterResourceBindings(
      HdInstance<HgiResourceBindingsSharedPtr>::ID id);

  /// Register a Hgi graphics pipeline into the registry.
  HDPH_API
  HdInstance<HgiGraphicsPipelineSharedPtr> RegisterGraphicsPipeline(
      HdInstance<HgiGraphicsPipelineSharedPtr>::ID id);

  /// Register a Hgi compute pipeline into the registry.
  HDPH_API
  HdInstance<HgiComputePipelineSharedPtr> RegisterComputePipeline(
      HdInstance<HgiComputePipelineSharedPtr>::ID id);

  /// Returns the global hgi blit command queue for recording blitting work.
  /// When using this global cmd instead of creating a new HgiBlitCmds we
  /// reduce the number of command buffers being created.
  /// The returned pointer should not be held onto by the client as it is
  /// only valid until the HgiBlitCmds has been submitted.
  HDPH_API
  HgiBlitCmds *GetGlobalBlitCmds();

  /// Returns the global hgi compute cmd queue for recording compute work.
  /// When using this global cmd instead of creating a new HgiComputeCmds we
  /// reduce the number of command buffers being created.
  /// The returned pointer should not be held onto by the client as it is
  /// only valid until the HgiComputeCmds has been submitted.
  HDPH_API
  HgiComputeCmds *GetGlobalComputeCmds();

  /// Submits blit work queued in global blit cmds for GPU execution.
  /// We can call this when we want to submit some work to the GPU.
  /// To stall the CPU and wait for the GPU to finish, 'wait' can be provided.
  /// To insert a barrier to ensure memory writes are visible after the
  /// barrier a HgiMemoryBarrier can be provided.
  HDPH_API
  void SubmitBlitWork(HgiSubmitWaitType wait = HgiSubmitWaitTypeNoWait);

  /// Submits compute work queued in global compute cmds for GPU execution.
  /// We can call this when we want to submit some work to the GPU.
  /// To stall the CPU and wait for the GPU to finish, 'wait' can be provided.
  /// To insert a barrier to ensure memory writes are visible after the
  /// barrier a HgiMemoryBarrier can be provided.
  HDPH_API
  void SubmitComputeWork(HgiSubmitWaitType wait = HgiSubmitWaitTypeNoWait);

 public:
  //
  // Unit test API
  //

  /// Set the aggregation strategy for non uniform parameters
  /// (vertex, varying, facevarying)
  /// Takes ownership of the passed in strategy object.
  void SetNonUniformAggregationStrategy(std::unique_ptr<HdAggregationStrategy> &&strategy)
  {
    _nonUniformAggregationStrategy = std::move(strategy);
  }

  /// Set the aggregation strategy for non uniform immutable parameters
  /// (vertex, varying, facevarying)
  /// Takes ownership of the passed in strategy object.
  void SetNonUniformImmutableAggregationStrategy(std::unique_ptr<HdAggregationStrategy> &&strategy)
  {
    _nonUniformImmutableAggregationStrategy = std::move(strategy);
  }

  /// Set the aggregation strategy for uniform (shader globals)
  /// Takes ownership of the passed in strategy object.
  void SetUniformAggregationStrategy(std::unique_ptr<HdAggregationStrategy> &&strategy)
  {
    _uniformUboAggregationStrategy = std::move(strategy);
  }

  /// Set the aggregation strategy for SSBO (uniform primvars)
  /// Takes ownership of the passed in strategy object.
  void SetShaderStorageAggregationStrategy(std::unique_ptr<HdAggregationStrategy> &&strategy)
  {
    _uniformSsboAggregationStrategy = std::move(strategy);
  }

  /// Set the aggregation strategy for single buffers (for nested instancer).
  /// Takes ownership of the passed in strategy object.
  void SetSingleStorageAggregationStrategy(std::unique_ptr<HdAggregationStrategy> &&strategy)
  {
    _singleAggregationStrategy = std::move(strategy);
  }

  /// Debug dump
  HDPH_API
  friend std::ostream &operator<<(std::ostream &out, const HdPhResourceRegistry &self);

 protected:
  void _Commit() override;
  void _GarbageCollect() override;

 private:
  void _CommitTextures();
  // Wrapper function for BAR allocation
  HdBufferArrayRangeSharedPtr _AllocateBufferArrayRange(HdAggregationStrategy *strategy,
                                                        HdBufferArrayRegistry &bufferArrayRegistry,
                                                        TfToken const &role,
                                                        HdBufferSpecVector const &bufferSpecs,
                                                        HdBufferArrayUsageHint usageHint);

  /// Wrapper function for BAR allocation/reallocation-migration.
  HdBufferArrayRangeSharedPtr _UpdateBufferArrayRange(
      HdAggregationStrategy *strategy,
      HdBufferArrayRegistry &bufferArrayRegistry,
      TfToken const &role,
      HdBufferArrayRangeSharedPtr const &curRange,
      HdBufferSpecVector const &updatedOrAddedSpecs,
      HdBufferSpecVector const &removedSpecs,
      HdBufferArrayUsageHint usageHint);

  // Tally resources by key into the given dictionary. Any additions should
  // be cumulative with the existing key values.
  void _TallyResourceAllocation(VtDictionary *result) const;

  // TODO: this is a transient structure. we'll revisit the BufferSource
  // interface later.
  struct _PendingSource {
    _PendingSource(HdBufferArrayRangeSharedPtr const &range) : range(range), sources()
    {
    }

    _PendingSource(HdBufferArrayRangeSharedPtr const &range, HdBufferSourceSharedPtr const &source)
        : range(range), sources(1, source)
    {
    }

    _PendingSource(HdBufferArrayRangeSharedPtr const &range,
                   HdBufferSourceSharedPtrVector &&sources)
        : range(range), sources(std::move(sources))
    {
    }

    HdBufferArrayRangeSharedPtr range;
    HdBufferSourceSharedPtrVector sources;
  };

  Hgi *_hgi;

  typedef tbb::concurrent_vector<_PendingSource> _PendingSourceList;
  _PendingSourceList _pendingSources;
  std::atomic_size_t _numBufferSourcesToResolve;

  struct _PendingComputation {
    _PendingComputation(HdBufferArrayRangeSharedPtr const &range,
                        HdComputationSharedPtr const &computation)
        : range(range), computation(computation)
    {
    }
    HdBufferArrayRangeSharedPtr range;
    HdComputationSharedPtr computation;
  };

  // If we need more 'compute queues' we can increase HdPhComputeQueueCount.
  // We could also consider tbb::concurrent_priority_queue if we want this
  // to be dynamically scalable.
  typedef tbb::concurrent_vector<_PendingComputation> _PendingComputationList;
  _PendingComputationList _pendingComputations[HdPhComputeQueueCount];

  // aggregated buffer array
  HdBufferArrayRegistry _nonUniformBufferArrayRegistry;
  HdBufferArrayRegistry _nonUniformImmutableBufferArrayRegistry;
  HdBufferArrayRegistry _uniformUboBufferArrayRegistry;
  HdBufferArrayRegistry _uniformSsboBufferArrayRegistry;
  HdBufferArrayRegistry _singleBufferArrayRegistry;

  // current aggregation strategies
  std::unique_ptr<HdAggregationStrategy> _nonUniformAggregationStrategy;
  std::unique_ptr<HdAggregationStrategy> _nonUniformImmutableAggregationStrategy;
  std::unique_ptr<HdAggregationStrategy> _uniformUboAggregationStrategy;
  std::unique_ptr<HdAggregationStrategy> _uniformSsboAggregationStrategy;
  std::unique_ptr<HdAggregationStrategy> _singleAggregationStrategy;

  typedef std::vector<HdPhDispatchBufferSharedPtr> _DispatchBufferRegistry;
  _DispatchBufferRegistry _dispatchBufferRegistry;

  typedef std::vector<HdPhBufferResourceSharedPtr> _BufferResourceRegistry;
  _BufferResourceRegistry _bufferResourceRegistry;

  // Register mesh topology.
  HdInstanceRegistry<HdPh_MeshTopologySharedPtr> _meshTopologyRegistry;

  // Register basisCurves topology.
  HdInstanceRegistry<HdPh_BasisCurvesTopologySharedPtr> _basisCurvesTopologyRegistry;

  // Register vertex adjacency.
  HdInstanceRegistry<Hd_VertexAdjacencySharedPtr> _vertexAdjacencyRegistry;

  // Register topology index buffers.
  typedef HdInstanceRegistry<HdBufferArrayRangeSharedPtr> _TopologyIndexRangeInstanceRegistry;
  typedef tbb::
      concurrent_unordered_map<TfToken, _TopologyIndexRangeInstanceRegistry, TfToken::HashFunctor>
          _TopologyIndexRangeInstanceRegMap;

  _TopologyIndexRangeInstanceRegMap _meshTopologyIndexRangeRegistry;
  _TopologyIndexRangeInstanceRegMap _basisCurvesTopologyIndexRangeRegistry;

  // Register shared primvar buffers.
  HdInstanceRegistry<HdBufferArrayRangeSharedPtr> _primvarRangeRegistry;

  // Register ext computation resource.
  HdInstanceRegistry<HdBufferArrayRangeSharedPtr> _extComputationDataRangeRegistry;

  // geometric shader registry
  HdInstanceRegistry<HdPh_GeometricShaderSharedPtr> _geometricShaderRegistry;

  // glsl shader program registry
  HdInstanceRegistry<HdPhGLSLProgramSharedPtr> _glslProgramRegistry;

  // glslfx file registry
  HdInstanceRegistry<HioGlslfxSharedPtr> _glslfxFileRegistry;

  // texture handle registry
  std::unique_ptr<class HdPh_TextureHandleRegistry> _textureHandleRegistry;

  // Hgi resource bindings registry
  HdInstanceRegistry<HgiResourceBindingsSharedPtr> _resourceBindingsRegistry;

  // Hgi graphics pipeline registry
  HdInstanceRegistry<HgiGraphicsPipelineSharedPtr> _graphicsPipelineRegistry;

  // Hgi compute pipeline registry
  HdInstanceRegistry<HgiComputePipelineSharedPtr> _computePipelineRegistry;

  HgiBlitCmdsUniquePtr _blitCmds;
  HgiComputeCmdsUniquePtr _computeCmds;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_RESOURCE_REGISTRY_H
