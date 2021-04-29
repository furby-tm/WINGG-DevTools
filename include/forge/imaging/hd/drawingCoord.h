#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/drawingCoord.h"
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
#ifndef FORGE_IMAGING_HD_DRAWING_COORD_H
#define FORGE_IMAGING_HD_DRAWING_COORD_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/base/tf/diagnostic.h"
#include <stdint.h>

FORGE_NAMESPACE_BEGIN

/// \class HdDrawingCoord
///
/// A tiny set of integers, which provides an indirection mapping from the
/// conceptual space of an HdRprim's resources (topological, primvar &
/// instancing) to the index within HdBufferArrayRangeContainer, where the
/// resource is stored.
///
/// Each HdDrawItem contains a HdDrawingCoord, with the relevant compositional
/// hierarchy being:
///
///  HdRprim
///  |
///  +--HdRepr(s)
///  |    |
///  |    +--HdDrawItem(s)----------.
///  |         |                    |
///  |         +--HdDrawingCoord    |
///  |                              | (mapping provided by HdDrawingCoord)
///  +--HdRprimSharedData           |
///     |                           |
///     +--HdBARContainer  <--------+
///
///
/// Having this indirection provides a recipe for how to configure
/// a drawing coordinate, which is a bundle of HdBufferArrayRanges, while
/// they are shared or not shared across different representations
/// constructed on the same prim.
///
///    HullRepr --------- Rprim --------- RefinedRepr
///       |                 |                  |
///    DrawItem             |              DrawItem
///       |                 |                  |
///  DrawingCoord       Container        DrawingCoord
///     constant -------> [ 0 ] <------    constant
///     vertex   -------> [ 1 ]
///     topology -------> [ 2 ]
///                       [ 3 ]
///                       [ 4 ]
///                       [ 5 ]
///                       [ 6 ]
///                       [ 7 ]
///                       [ 8 ] <------    vertex   (refined)
///                       [ 9 ] <------    topology (refined)
///                        ...
/// instance level=0 ---> [ k ]
/// instance level=1 ---> [k+1]
/// instance level=2 ---> [k+2]
///
class HdDrawingCoord {
public:
    static const int CustomSlotsBegin = 8;
    static const int DefaultNumSlots = 3; /* Constant, Vertex, Topology */
    static const int Unassigned = -1;

    HdDrawingCoord() :
        // default slots:
        _constantPrimvar(0),
        _vertexPrimvar(1),
        _topology(2),
        _elementPrimvar(3),
        _instanceIndex(4),
        _faceVaryingPrimvar(5),
        _topologyVisibility(6),
        _varyingPrimvar(7),
        _instancePrimvar(Unassigned) {
    }

    int GetConstantPrimvarIndex() const    { return _constantPrimvar; }
    void SetConstantPrimvarIndex(int slot) { _constantPrimvar = slot; }
    int GetVertexPrimvarIndex() const      { return _vertexPrimvar; }
    void SetVertexPrimvarIndex(int slot)   { _vertexPrimvar = slot; }
    int GetTopologyIndex() const           { return _topology; }
    void SetTopologyIndex(int slot)        { _topology = slot; }
    int GetElementPrimvarIndex() const     { return _elementPrimvar; }
    void SetElementPrimvarIndex(int slot)  { _elementPrimvar = slot; }
    int GetInstanceIndexIndex() const      { return _instanceIndex; }
    void SetInstanceIndexIndex(int slot)   { _instanceIndex = slot; }
    int GetFaceVaryingPrimvarIndex() const    { return _faceVaryingPrimvar; }
    void SetFaceVaryingPrimvarIndex(int slot) { _faceVaryingPrimvar = slot; }
    int GetTopologyVisibilityIndex() const    { return _topologyVisibility; }
    void SetTopologyVisibilityIndex(int slot) { _topologyVisibility = slot; }
    int GetVaryingPrimvarIndex() const      { return _varyingPrimvar; }
    void SetVaryingPrimvarIndex(int slot)   { _varyingPrimvar = slot; }

    // instance primvars take up a range of slots.
    void SetInstancePrimvarBaseIndex(int slot) { _instancePrimvar = slot; }
    int GetInstancePrimvarIndex(int level) const {
        TF_VERIFY(_instancePrimvar != Unassigned);
        return _instancePrimvar + level;
    }

private:
    int8_t _constantPrimvar;
    int8_t _vertexPrimvar;
    int8_t _topology;
    int8_t _elementPrimvar;
    int8_t _instanceIndex;
    int8_t _faceVaryingPrimvar;
    int8_t _topologyVisibility;
    int8_t _varyingPrimvar;
    int8_t _instancePrimvar;
};


FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_DRAWING_COORD_H
