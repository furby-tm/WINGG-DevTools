#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/pcp/instancing.h"
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
#ifndef FORGE_USD_PCP_INSTANCING_H
#define FORGE_USD_PCP_INSTANCING_H

/// \file pcp/instancing.h
///
/// A collection of private helper utilities to support instancing
/// functionality.

#include "forge/forge.h"
#include "forge/usd/pcp/composeSite.h"
#include "forge/usd/pcp/node_Iterator.h"
#include "forge/usd/pcp/primIndex.h"

FORGE_NAMESPACE_BEGIN

/// Helper function to determine whether the given prim index is
/// instanceable. An instanceable prim index must have instanceable
/// nodes and must have been tagged so that the composed value of
/// the metadata field 'instance' is true.
bool
Pcp_PrimIndexIsInstanceable(
    const PcpPrimIndex& primIndex);

/// Helper function for traversing a prim index in strong-to-weak
/// order while identifying instanceable nodes. This function passes
/// each node in \p primIndex to the supplied \p visitor along with
/// a flag indicating whether that node is instanceable.
///
/// The visitor needs to implement this interface:
///
/// struct Visitor {
///     bool Visit(PcpNodeRef node, bool nodeIsInstanceable)
///     { ... }
/// }
///
/// If the Visit function returns false, traversal will be pruned at that
/// node and none of the node's children will be visited.
///
template <class Visitor>
void
Pcp_TraverseInstanceableStrongToWeak(
    const PcpPrimIndex& primIndex,
    Visitor* visitor);

/// Helper function for traversing a prim index in weak-to-strong
/// order while identifying instanceable nodes. This function passes
/// each node in \p primIndex to the supplied \p visitor along with
/// a flag indicating whether that node is instanceable.
///
/// The visitor needs to implement this interface:
///
/// struct Visitor {
///     void Visit(PcpNodeRef node, bool nodeIsInstanceable)
///     { ... }
/// }
///
template <class Visitor>
void
Pcp_TraverseInstanceableWeakToStrong(
    const PcpPrimIndex& primIndex,
    Visitor* visitor);

// Implementation ----------------------------------------

inline bool
Pcp_ChildNodeIsInstanceable(
    const PcpNodeRef& node,
    bool *hasAnyDirectArcsInNodeChain)
{
    // Non-ancestral nodes are instanceable: they represent a direct
    // composition arc to a portion of scenegraph that could be shared
    // with other prim indexes, as long as the other criteria laid out
    // in PcpInstanceKey are met. But there may also be ancestral nodes that
    // exist in the graph because they were composed in a subtree of direct
    // arc to a subroot path. These nodes are also instanceable as they are
    // considered part of the direct arc that brought them in. This is why we
    // keep track of and check whether there are any direct arcs in the node's
    // chain up to the root node when determining if a node is instanceable.
    *hasAnyDirectArcsInNodeChain =
        *hasAnyDirectArcsInNodeChain || !node.IsDueToAncestor();

    // If a node has no specs, we do not consider it instanceable since
    // it has no opinions to contribute to the prim index. In particular,
    // this allows prim indexes with implied arcs in different layer stacks
    // that have no overrides to still be considered equivalent for sharing.
    return *hasAnyDirectArcsInNodeChain && node.HasSpecs();
}

inline bool
Pcp_ChildNodeIsDirectOrInDirectArcSubtree(
    const PcpNodeRef& node)
{
    if (node.IsRootNode() || !node.IsDueToAncestor()) {
        return true;
    }
    for (PcpNodeRef parent = node.GetParentNode();
         !parent.IsRootNode();
         parent = parent.GetParentNode()) {
        if (!parent.IsDueToAncestor()) {
            return true;
        }
    }
    return false;
}

inline bool
Pcp_ChildNodeInstanceableChanged(
    const PcpNodeRef& node)
{
    return Pcp_ChildNodeIsDirectOrInDirectArcSubtree(node) &&
        (PcpComposeSiteHasPrimSpecs(node) != node.HasSpecs());
}

template <class Visitor>
inline void
Pcp_TraverseInstanceableStrongToWeakHelper(
    const PcpNodeRef& node,
    Visitor* visitor,
    bool hasAnyDirectArcsInNodeChain)
{
    // If the node is culled, the entire subtree rooted at this node
    // does not contribute to the prim index, so we can prune the
    // traversal.
    if (node.IsCulled()) {
        return;
    }

    const bool isInstanceable =
        Pcp_ChildNodeIsInstanceable(node, &hasAnyDirectArcsInNodeChain);
    if (!visitor->Visit(node, isInstanceable)) {
        return;
    }

    TF_FOR_ALL(childIt, Pcp_GetChildrenRange(node)) {
        const PcpNodeRef& childNode = *childIt;
        Pcp_TraverseInstanceableStrongToWeakHelper(
            childNode, visitor, hasAnyDirectArcsInNodeChain);
    }
}

template <class Visitor>
inline void
Pcp_TraverseInstanceableStrongToWeak(
    const PcpPrimIndex& primIndex,
    Visitor* visitor)
{
    const PcpNodeRef& rootNode = primIndex.GetRootNode();
    if (!visitor->Visit(rootNode, /* nodeIsInstanceable = */ false)) {
        return;
    }

    TF_FOR_ALL(childIt, Pcp_GetChildrenRange(rootNode)) {
        const PcpNodeRef& childNode = *childIt;
        Pcp_TraverseInstanceableStrongToWeakHelper(
            childNode, visitor, /* hasAnyDirectArcsInNodeChain = */ false);
    }
}

template <class Visitor>
inline void
Pcp_TraverseInstanceableWeakToStrongHelper(
    const PcpNodeRef& node,
    Visitor* visitor,
    bool hasAnyDirectArcsInNodeChain)
{
    // If the node is culled, the entire subtree rooted at this node
    // does not contribute to the prim index, so we can prune the
    // traversal.
    if (node.IsCulled()) {
        return;
    }

    const bool isInstanceable =
        Pcp_ChildNodeIsInstanceable(node, &hasAnyDirectArcsInNodeChain);

    TF_REVERSE_FOR_ALL(childIt, Pcp_GetChildrenRange(node)) {
        const PcpNodeRef& childNode = *childIt;
        Pcp_TraverseInstanceableWeakToStrongHelper(
            childNode, visitor, hasAnyDirectArcsInNodeChain);
    }

    visitor->Visit(node, isInstanceable);
}

template <class Visitor>
inline void
Pcp_TraverseInstanceableWeakToStrong(
    const PcpPrimIndex& primIndex,
    Visitor* visitor)
{
    const PcpNodeRef& rootNode = primIndex.GetRootNode();
    TF_REVERSE_FOR_ALL(childIt, Pcp_GetChildrenRange(rootNode)) {
        const PcpNodeRef& childNode = *childIt;
        Pcp_TraverseInstanceableWeakToStrongHelper(
            childNode, visitor, /* hasAnyDirectArcsInNodeChain = */ false);
    }

    visitor->Visit(rootNode, /* nodeIsInstanceable = */ false);
}

FORGE_NAMESPACE_END

#endif // FORGE_USD_PCP_INSTANCING_H
