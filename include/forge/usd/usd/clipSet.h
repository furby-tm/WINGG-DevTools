#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usd/clipSet.h"
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
#ifndef FORGE_USD_USD_CLIP_SET_H
#define FORGE_USD_USD_CLIP_SET_H

#include "forge/forge.h"

#include "forge/usd/usd/clip.h"
#include "forge/usd/usd/valueUtils.h"

#include "forge/usd/sdf/path.h"

#include "forge/base/tf/declarePtrs.h"

#include <memory>

FORGE_NAMESPACE_BEGIN

TF_DECLARE_WEAK_PTRS(PcpLayerStack);

class Usd_ClipSet;
class Usd_ClipSetDefinition;

using Usd_ClipSetRefPtr = std::shared_ptr<Usd_ClipSet>;

/// \class Usd_ClipSet
///
/// Represents a clip set for value resolution. A clip set primarily
/// consists of a list of Usd_Clip objects from which attribute values
/// are retrieved during value resolution.
///
class Usd_ClipSet
{
public:
    /// Create a new clip set based on the given definition. If clip
    /// set creation fails, returns a null pointer and populates
    /// \p status with an error message. Otherwise \p status may be
    /// populated with other information or debugging output.
    static Usd_ClipSetRefPtr New(
        const std::string& name,
        const Usd_ClipSetDefinition& definition,
        std::string* status);

    Usd_ClipSet(const Usd_ClipSet&) = delete;
    Usd_ClipSet& operator=(const Usd_ClipSet&) = delete;

    /// Return the active clip at the given \p time. This should
    /// always be a valid Usd_ClipRefPtr.
    const Usd_ClipRefPtr& GetActiveClip(double time) const
    {
        return valueClips[_FindClipIndexForTime(time)];
    }

    /// Return bracketing time samples for the attribute at \p path
    /// at \p time.
    bool GetBracketingTimeSamplesForPath(
        const SdfPath& path, double time,
        double* lower, double* upper) const;

    /// Return set of time samples for attribute at \p path.
    std::set<double> ListTimeSamplesForPath(const SdfPath& path) const;

    /// Query time sample for the attribute at \p path at \p time.
    /// If no time sample exists in the active clip at \p time,
    /// \p interpolator will be used to try to interpolate the
    /// value from the surrounding time samples in the active clip.
    /// If the active clip has no time samples, use the default
    /// value for the attribute declared in the manifest. If no
    /// default value is declared, use the fallback value for
    /// the attribute's value type.
    template <class T>
    bool QueryTimeSample(
        const SdfPath& path, double time,
        Usd_InterpolatorBase* interpolator, T* value) const;

    std::string name;
    PcpLayerStackPtr sourceLayerStack;
    SdfPath sourcePrimPath;
    size_t sourceLayerIndex;
    SdfPath clipPrimPath;
    Usd_ClipRefPtr manifestClip;
    Usd_ClipRefPtrVector valueClips;
    bool interpolateMissingClipValues;

private:
    Usd_ClipSet(
        const std::string& name,
        const Usd_ClipSetDefinition& definition);

    // Return the index of the clip that is active at the given \p time.
    // This will always return a valid index into the valueClips list.
    size_t _FindClipIndexForTime(double time) const;

    // Return whether the specified clip contributes time sample values
    // to this clip set for the attribute at \p path.
    bool _ClipContributesValue(
        const Usd_ClipRefPtr& clip, const SdfPath& path) const;
};

// ------------------------------------------------------------

template <class T>
inline bool
Usd_ClipSet::QueryTimeSample(
    const SdfPath& path, double time,
    Usd_InterpolatorBase* interpolator, T* value) const
{
    const Usd_ClipRefPtr& clip = GetActiveClip(time);

    // First query the clip for time samples at the specified time.
    if (clip->QueryTimeSample(path, time, interpolator, value)) {
        return true;
    }

    // If no samples exist in the clip, get the default value from
    // the manifest. Return true if we get a non-block value, false
    // otherwise.
    return Usd_HasDefault(manifestClip, path, value) ==
        Usd_DefaultValueResult::Found;
}

// ------------------------------------------------------------

template <class T>
inline bool
Usd_QueryTimeSample(
    const Usd_ClipSetRefPtr& clipSet, const SdfPath& path,
    double time, Usd_InterpolatorBase* interpolator, T* result)
{
    return clipSet->QueryTimeSample(path, time, interpolator, result);
}

/// Generate a manifest layer for the given \p clips containing all
/// attributes under the given \p clipPrimPath. Note that this will
/// open the layers for all of these clips.
///
/// If \p writeBlocksForClipsWithMissingValues is \c true, the generated
/// manifest will have value blocks authored for each attribute at the
/// activation times of clips that do not contain time samples for that
/// attribute.
///
/// The layer will contain the given \p tag in its identifier.
SdfLayerRefPtr
Usd_GenerateClipManifest(
    const Usd_ClipRefPtrVector& clips, const SdfPath& clipPrimPath,
    const std::string& tag = std::string(),
    bool writeBlocksForClipsWithMissingValues = false);

/// Generate a manifest layer for the given \p clipLayers containing
/// all attributes under the given \p clipPrimPath. The layer will contain
/// the given tag in its identifier.
///
/// If \p clipActive is not nullptr, it must be a list of activation times
/// for the corresponding layer in \p clipLayers. This will be used to
/// author value blocks for each attribute at the activation times of clips
/// that do not contain time samples for that attribute.
SdfLayerRefPtr
Usd_GenerateClipManifest(
    const SdfLayerHandleVector& clipLayers, const SdfPath& clipPrimPath,
    const std::string& tag = std::string(),
    const std::vector<double>* clipActive = nullptr);

/// Return true if the given layer is a manifest that has been automatically
/// generated because the user has not supplied one. These layers are anonymous
/// layers with a specific tag in their identifiers.
bool
Usd_IsAutoGeneratedClipManifest(const SdfLayerHandle& manifestLayer);

FORGE_NAMESPACE_END

#endif
