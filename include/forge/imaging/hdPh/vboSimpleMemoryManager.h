#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/vboSimpleMemoryManager.h"
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
#ifndef FORGE_IMAGING_HD_PH_VBO_SIMPLE_MEMORY_MANAGER_H
#define FORGE_IMAGING_HD_PH_VBO_SIMPLE_MEMORY_MANAGER_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferArray.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/strategyBase.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/bufferArrayRange.h"
#include "forge/imaging/hdPh/resourceRegistry.h"

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;

/// \class HdPhVBOSimpleMemoryManager
///
/// VBO simple memory manager.
///
/// This class doesn't perform any aggregation.
///
class HdPhVBOSimpleMemoryManager : public HdAggregationStrategy {
 public:
  HdPhVBOSimpleMemoryManager(HdPhResourceRegistry *resourceRegistry)
      : _resourceRegistry(resourceRegistry)
  {
  }

  /// Factory for creating HdBufferArray managed by
  /// HdPhVBOSimpleMemoryManager.
  HDPH_API
  virtual HdBufferArraySharedPtr CreateBufferArray(TfToken const &role,
                                                   HdBufferSpecVector const &bufferSpecs,
                                                   HdBufferArrayUsageHint usageHint);

  /// Factory for creating HdBufferArrayRange
  HDPH_API
  virtual HdBufferArrayRangeSharedPtr CreateBufferArrayRange();

  /// Returns id for given bufferSpecs to be used for aggregation
  HDPH_API
  virtual HdAggregationStrategy::AggregationId ComputeAggregationId(
      HdBufferSpecVector const &bufferSpecs, HdBufferArrayUsageHint usageHint) const;

  /// Returns the buffer specs from a given buffer array
  virtual HdBufferSpecVector GetBufferSpecs(HdBufferArraySharedPtr const &bufferArray) const;

  /// Returns the size of the GPU memory used by the passed buffer array
  virtual size_t GetResourceAllocation(HdBufferArraySharedPtr const &bufferArray,
                                       VtDictionary &result) const;

 protected:
  class _SimpleBufferArray;

  /// \class _SimpleBufferArrayRange
  ///
  /// Specialized buffer array range for SimpleBufferArray.
  ///
  class _SimpleBufferArrayRange final : public HdPhBufferArrayRange {
   public:
    /// Constructor.
    _SimpleBufferArrayRange(HdPhResourceRegistry *resourceRegistry)
        : HdPhBufferArrayRange(resourceRegistry), _bufferArray(nullptr), _numElements(0)
    {
    }

    /// Returns true if this range is valid
    bool IsValid() const override
    {
      return (bool)_bufferArray;
    }

    /// Returns true is the range has been assigned to a buffer
    HDPH_API
    bool IsAssigned() const override;

    /// Returns true if this range is marked as immutable.
    bool IsImmutable() const override;

    /// Resize memory area for this range. Returns true if it causes container
    /// buffer reallocation.
    bool Resize(int numElements) override
    {
      _numElements = numElements;
      return _bufferArray->Resize(numElements);
    }

    /// Copy source data into buffer
    HDPH_API
    void CopyData(HdBufferSourceSharedPtr const &bufferSource) override;

    /// Read back the buffer content
    HDPH_API
    VtValue ReadData(TfToken const &name) const override;

    /// Returns the offset at which this range begins in the underlying
    /// buffer array in terms of elements.
    int GetElementOffset() const override
    {
      return 0;
    }

    /// Returns the byte offset at which this range begins in the underlying
    /// buffer array for the given resource.
    int GetByteOffset(TfToken const &resourceName) const override
    {
      TF_UNUSED(resourceName);
      return 0;
    }

    /// Returns the number of elements allocated
    size_t GetNumElements() const override
    {
      return _numElements;
    }

    /// Returns the capacity of allocated area for this range
    int GetCapacity() const
    {
      return _bufferArray->GetCapacity();
    }

    /// Returns the version of the buffer array.
    size_t GetVersion() const override
    {
      return _bufferArray->GetVersion();
    }

    /// Increment the version of the buffer array.
    void IncrementVersion() override
    {
      _bufferArray->IncrementVersion();
    }

    /// Returns the max number of elements
    HDPH_API
    size_t GetMaxNumElements() const override;

    /// Returns the usage hint from the underlying buffer array
    HDPH_API
    HdBufferArrayUsageHint GetUsageHint() const override;

    /// Returns the GPU resource. If the buffer array contains more than one
    /// resource, this method raises a coding error.
    HDPH_API
    HdPhBufferResourceSharedPtr GetResource() const override;

    /// Returns the named GPU resource.
    HDPH_API
    HdPhBufferResourceSharedPtr GetResource(TfToken const &name) override;

    /// Returns the list of all named GPU resources for this bufferArrayRange.
    HDPH_API
    HdPhBufferResourceNamedList const &GetResources() const override;

    /// Sets the buffer array associated with this buffer;
    HDPH_API
    void SetBufferArray(HdBufferArray *bufferArray) override;

    /// Debug dump
    HDPH_API
    void DebugDump(std::ostream &out) const override;

    /// Make this range invalid
    void Invalidate()
    {
      _bufferArray = NULL;
    }

   protected:
    /// Returns the aggregation container
    HDPH_API
    const void *_GetAggregation() const override;

    /// Adds a new, named GPU resource and returns it.
    HDPH_API
    HdPhBufferResourceSharedPtr _AddResource(TfToken const &name,
                                             HdTupleType tupleType,
                                             int offset,
                                             int stride);

   private:
    _SimpleBufferArray *_bufferArray;
    size_t _numElements;
  };

  using _SimpleBufferArraySharedPtr = std::shared_ptr<_SimpleBufferArray>;
  using _SimpleBufferArrayRangeSharedPtr = std::shared_ptr<_SimpleBufferArrayRange>;
  using _SimpleBufferArrayRangePtr = std::weak_ptr<_SimpleBufferArrayRange>;

  /// \class _SimpleBufferArray
  ///
  /// Simple buffer array (non-aggregated).
  ///
  class _SimpleBufferArray final : public HdBufferArray {
   public:
    /// Constructor.
    HDPH_API
    _SimpleBufferArray(HdPhResourceRegistry *resourceRegistry,
                       TfToken const &role,
                       HdBufferSpecVector const &bufferSpecs,
                       HdBufferArrayUsageHint usageHint);

    /// Destructor. It invalidates _range
    HDPH_API
    ~_SimpleBufferArray() override;

    /// perform compaction if necessary, returns true if it becomes empty.
    HDPH_API
    bool GarbageCollect() override;

    /// Debug output
    HDPH_API
    void DebugDump(std::ostream &out) const override;

    /// Set to resize buffers. Actual reallocation happens on Reallocate()
    HDPH_API
    bool Resize(int numElements);

    /// Performs reallocation.
    /// GLX context has to be set when calling this function.
    HDPH_API
    void Reallocate(std::vector<HdBufferArrayRangeSharedPtr> const &ranges,
                    HdBufferArraySharedPtr const &curRangeOwner) override;

    /// Returns the maximum number of elements capacity.
    HDPH_API
    size_t GetMaxNumElements() const override;

    /// Returns current capacity. It could be different from numElements.
    int GetCapacity() const
    {
      return _capacity;
    }

    /// TODO: We need to distinguish between the primvar types here, we should
    /// tag each HdBufferSource and HdBufferResource with Constant, Uniform,
    /// Varying, Vertex, or FaceVarying and provide accessors for the specific
    /// buffer types.

    /// Returns the GPU resource. If the buffer array contains more than one
    /// resource, this method raises a coding error.
    HDPH_API
    HdPhBufferResourceSharedPtr GetResource() const;

    /// Returns the named GPU resource. This method returns the first found
    /// resource. In HD_SAFE_MODE it checks all underlying GL buffers
    /// in _resourceMap and raises a coding error if there are more than
    /// one GL buffers exist.
    HDPH_API
    HdPhBufferResourceSharedPtr GetResource(TfToken const &name);

    /// Returns the list of all named GPU resources for this bufferArray.
    HdPhBufferResourceNamedList const &GetResources() const
    {
      return _resourceList;
    }

    /// Reconstructs the bufferspecs and returns it (for buffer splitting)
    HDPH_API
    HdBufferSpecVector GetBufferSpecs() const;

   protected:
    HDPH_API
    void _DeallocateResources();

    /// Adds a new, named GPU resource and returns it.
    HDPH_API
    HdPhBufferResourceSharedPtr _AddResource(TfToken const &name,
                                             HdTupleType tupleType,
                                             int offset,
                                             int stride);

   private:
    HdPhResourceRegistry *const _resourceRegistry;
    int _capacity;
    size_t _maxBytesPerElement;

    HdPhBufferResourceNamedList _resourceList;

    _SimpleBufferArrayRangeSharedPtr _GetRangeSharedPtr() const
    {
      return GetRangeCount() > 0 ?
                 std::static_pointer_cast<_SimpleBufferArrayRange>(GetRange(0).lock()) :
                 _SimpleBufferArrayRangeSharedPtr();
    }
  };

  HdPhResourceRegistry *const _resourceRegistry;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_VBO_SIMPLE_MEMORY_MANAGER_H
