#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hdPh/instancer.h"
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
#ifndef FORGE_IMAGING_HD_PH_INSTANCER_H
#define FORGE_IMAGING_HD_PH_INSTANCER_H

#include "forge/base/tf/hashmap.h"
#include "forge/base/vt/array.h"
#include "forge/forge.h"
#include "forge/imaging/hd/changeTracker.h"
#include "forge/imaging/hd/instancer.h"
#include "forge/imaging/hdPh/api.h"
#include "forge/usd/sdf/path.h"

FORGE_NAMESPACE_BEGIN

class HdRprim;
class HdPhDrawItem;
struct HdRprimSharedData;

using HdBufferArrayRangeSharedPtr = std::shared_ptr<class HdBufferArrayRange>;

/// \class HdPhInstancer
///
/// HdPh implements instancing by drawing each proto multiple times with
/// a single draw call.  Application of instance primvars (like transforms)
/// is done in shaders. Instance transforms in particular are computed in
/// ApplyInstanceTransform in instancing.glslfx.
///
/// If this instancer is nested, instance indices will be computed
/// recursively by ascending the hierarchy. HdPhInstancer computes a flattened
/// index structure for each prototype by taking the cartesian product of the
/// instance indices at each level.
///
/// For example:
///   - InstancerA draws instances [ProtoX, InstancerB, ProtoX, InstancerB]
///   - InstancerB draws instances [ProtoY, ProtoZ, ProtoY]
/// The flattened index for Proto Y is:
/// [0, 0, 1]; [1, 0, 3]; [2, 2, 1]; [3, 2, 3];
/// where the first tuple element is the position in the flattened index;
/// the second tuple element is the position in Instancer B;
/// and the last tuple element is the position in Instancer A.
///
/// The flattened index gives the number of times the proto is drawn, and the
/// index tuple can be passed to the shader so that each instance can look up
/// its instance primvars in the bound primvar arrays.

class HdPhInstancer : public HdInstancer {
 public:
  /// Constructor.
  HDPH_API
  HdPhInstancer(HdSceneDelegate *delegate, SdfPath const &id);

  // Updates the instance primvar buffers.
  // XXX: Note, this is currently called from rprimUtils instead of the
  // render index sync phase, so it needs to take a mutex.
  HDPH_API
  void Sync(HdSceneDelegate *sceneDelegate,
            HdRenderParam *renderParam,
            HdDirtyBits *dirtyBits) override;

  HdBufferArrayRangeSharedPtr GetInstancePrimvarRange() const
  {
    return _instancePrimvarRange;
  }

  /// Populates the instance index indirection buffer for \p prototypeId and
  /// returns a flat array of instance index tuples.
  HDPH_API
  VtIntArray GetInstanceIndices(SdfPath const &prototypeId);

 protected:
  HDPH_API
  void _GetInstanceIndices(SdfPath const &prototypeId,
                           std::vector<VtIntArray> *instanceIndicesArray);

  HDPH_API
  void _SyncPrimvars(HdSceneDelegate *sceneDelegate, HdDirtyBits *dirtyBits);

 private:
  // # of entries in an instance primvar.  This should be consistent between
  // all primvars, and also consistent with the instance indices (meaning
  // no instance index is out-of-range).
  size_t _instancePrimvarNumElements;

  // The BAR of the instance primvars for this instancer.
  // (Note: instance indices are computed per prototype and the rprim owns
  // the bar).
  HdBufferArrayRangeSharedPtr _instancePrimvarRange;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_PH_INSTANCER_H
