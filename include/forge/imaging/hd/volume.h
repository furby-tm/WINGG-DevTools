#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hd/volume.h"
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
#ifndef FORGE_IMAGING_HD_VOLUME_H
#define FORGE_IMAGING_HD_VOLUME_H

#include "forge/forge.h"
#include "forge/imaging/hd/api.h"
#include "forge/imaging/hd/version.h"
#include "forge/imaging/hd/rprim.h"

#include <vector>

FORGE_NAMESPACE_BEGIN

class HdSceneDelegate;
typedef std::vector<class HdVolume const *> HdVolumePtrConstVector;

/// \class HdVolume
///
/// Hd schema for a renderable volume primitive.
///
class HdVolume : public HdRprim {
public:
    HD_API
    HdVolume(SdfPath const& id);

    HD_API
    virtual ~HdVolume();

    HD_API
    TfTokenVector const & GetBuiltinPrimvarNames() const override;
};

FORGE_NAMESPACE_END

#endif  // FORGE_IMAGING_HD_VOLUME_H
