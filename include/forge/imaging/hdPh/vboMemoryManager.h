#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/vboMemoryManager.h"
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
#ifndef FORGE_IMAGING_HD_PH_VBO_MEMORY_MANAGER_H
#define FORGE_IMAGING_HD_PH_VBO_MEMORY_MANAGER_H

#include "forge/forge.h"
#include "forge/imaging/hd/bufferArray.h"
#include "forge/imaging/hd/bufferSource.h"
#include "forge/imaging/hd/bufferSpec.h"
#include "forge/imaging/hd/strategyBase.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/imaging/hdPh/bufferArrayRange.h"

#include "forge/base/tf/mallocTag.h"
#include "forge/base/tf/token.h"

#include <list>
#include <memory>

FORGE_NAMESPACE_BEGIN

class HdPhResourceRegistry;

/// \class HdPhVBOMemoryManager
///
/// VBO memory manager.
///
class HdPhVBOMemoryManager : public HdAggregationStrategy {
 public:
  HdPhVBOMemoryManager(HdPhResourceRegistry *resourceRegistry)
      : HdAggregationStrategy(), _resourceRegistry(resourceRegistry)
  {
  }

  /// Factory for creating HdBufferArray managed by
  /// HdPhVBOMemoryManager aggregation.
  HDPH_API
  virtual HdBufferArraySharedPtr CreateBufferArray(TfToken const &role,
                                                   HdBufferSpecVector const &bufferSpecs,
                                                   HdBufferArrayUsageHint usageHint);

  /// Factory for creating HdBufferArrayRange managed by
  /// HdPhVBOMemoryManager aggregation.
  HDPH_API
  virtual HdBufferArrayRangeSharedPtr CreateBufferArrayRange();

  /// Returns id for given bufferSpecs to be used for aggregation
  HDPH_API
  virtual AggregationId ComputeAggregationId(HdBufferSpecVector const &bufferSpecs,
                                             HdBufferArrayUsageHint usageHint) const;

  /// Returns the buffer specs from a given buffer array
  virtual HdBufferSpecVector GetBufferSpecs(HdBufferArraySharedPtr const &bufferArray) const;

  /// Returns the size of the GPU memory used by the passed buffer array
  virtual size_t GetResourceAllocation(HdBufferArraySharedPtr const &bufferArray,
                                       VtDictionary &result) const;

 protected:
  class _StripedBufferArray;

  /// specialized buffer array range
  class _StripedBufferArrayRange : public HdPhBufferArrayRange {
   public:
    /// Constructor.
    _StripedBufferArrayRange(HdPhResourceRegistry *resourceRegistry)
        : HdPhBufferArrayRange(resourceRegistry),
          _stripedBufferArray(nullptr),
          _elementOffset(0),
          _numElements(0),
          _capacity(0)
    {
    }

    /// Destructor.
    HDPH_API
    ~_StripedBufferArrayRange() override;

    /// Returns true if this range is valid
    bool IsValid() const override
    {
      return (bool)_stripedBufferArray;
    }

    /// Returns true is the range has been assigned to a buffer
    HDPH_API
    bool IsAssigned() const override;

    /// Returns true if this bar is marked as immutable.
    bool IsImmutable() const override;

    /// Resize memory area for this range. Returns true if it causes container
    /// buffer reallocation.
    HDPH_API
    bool Resize(int numElements) override;

    /// Copy source data into buffer
    HDPH_API
    void CopyData(HdBufferSourceSharedPtr const &bufferSource) override;

    /// Read back the buffer content
    HDPH_API
    VtValue ReadData(TfToken const &name) const override;

    /// Returns the relative element offset in aggregated buffer
    int GetElementOffset() const override
    {
      return _elementOffset;
    }

    /// Returns the byte offset at which this range begins in the underlying
    /// buffer array for the given resource.
    int GetByteOffset(TfToken const &resourceName) const override;

    /// Returns the number of elements
    size_t GetNumElements() const override
    {
      return _numElements;
    }

    /// Returns the version of the buffer array.
    size_t GetVersion() const override
    {
      return _stripedBufferArray->GetVersion();
    }

    /// Increment the version of the buffer array.
    void IncrementVersion() override
    {
      _stripedBufferArray->IncrementVersion();
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

    /// Set the relative offset for this range.
    void SetElementOffset(int offset)
    {
      _elementOffset = offset;
    }

    /// Set the number of elements for this range.
    void SetNumElements(int numElements)
    {
      _numElements = numElements;
    }

    /// Returns the capacity of allocated area
    int GetCapacity() const
    {
      return _capacity;
    }

    /// Set the capacity of allocated area for this range.
    void SetCapacity(int capacity)
    {
      _capacity = capacity;
    }

    /// Make this range invalid
    void Invalidate()
    {
      _stripedBufferArray = NULL;
    }

   protected:
    /// Returns the aggregation container
    HDPH_API
    const void *_GetAggregation() const override;

   private:
    // Returns the byte offset at which the BAR begins for the resource.
    size_t _GetByteOffset(HdPhBufferResourceSharedPtr const &resource) const;

    // holding a weak reference to container.
    // this pointer becomes null when the StripedBufferArray gets destructed,
    // in case if any drawItem still holds this bufferRange.
    _StripedBufferArray *_stripedBufferArray;
    int _elementOffset;
    size_t _numElements;
    int _capacity;
  };

  using _StripedBufferArraySharedPtr = std::shared_ptr<_StripedBufferArray>;
  using _StripedBufferArrayRangeSharedPtr = std::shared_ptr<_StripedBufferArrayRange>;
  using _StripedBufferArrayRangePtr = std::weak_ptr<_StripedBufferArrayRange>;

  /// striped buffer array
  class _StripedBufferArray : public HdBufferArray {
   public:
    /// Constructor.
    HDPH_API
    _StripedBufferArray(HdPhResourceRegistry *resourceRegistry,
                        TfToken const &role,
                        HdBufferSpecVector const &bufferSpecs,
                        HdBufferArrayUsageHint usageHint);

    /// Destructor. It invalidates _rangeList
    HDPH_API
    ~_StripedBufferArray() override;

    /// perform compaction if necessary. If it becomes empty, release all
    /// resources and returns true
    HDPH_API
    bool GarbageCollect() override;

    /// Debug output
    HDPH_API
    void DebugDump(std::ostream &out) const override;

    /// Performs reallocation.
    /// GLX context has to be set when calling this function.
    HDPH_API
    void Reallocate(std::vector<HdBufferArrayRangeSharedPtr> const &ranges,
                    HdBufferArraySharedPtr const &curRangeOwner) override;

    /// Returns the maximum number of elements capacity.
    HDPH_API
    size_t GetMaxNumElements() const override;

    /// Mark to perform reallocation on Reallocate()
    void SetNeedsReallocation()
    {
      _needsReallocation = true;
    }

    /// Mark to perform compaction on GarbageCollect()
    void SetNeedsCompaction()
    {
      _needsCompaction = true;
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
    HdPhResourceRegistry *_resourceRegistry;
    bool _needsCompaction;
    int _totalCapacity;
    size_t _maxBytesPerElement;

    HdPhBufferResourceNamedList _resourceList;

    // Helper routine to cast the range shared pointer.
    _StripedBufferArrayRangeSharedPtr _GetRangeSharedPtr(size_t idx) const
    {
      return std::static_pointer_cast<_StripedBufferArrayRange>(GetRange(idx).lock());
    }
  };

  HdPhResourceRegistry *_resourceRegistry;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_VBO_MEMORY_MANAGER_H
