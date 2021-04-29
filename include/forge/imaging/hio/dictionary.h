#line 1 "C:/Users/tyler/dev/WINGG/forge/imaging/hio/dictionary.h"
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
#ifndef FORGE_IMAGING_HIO_DICTIONARY_H
#define FORGE_IMAGING_HIO_DICTIONARY_H

/// \file hio/dictionary.h

#include "forge/forge.h"

#include "forge/base/vt/dictionary.h"
#include <string>

FORGE_NAMESPACE_BEGIN

VtDictionary
Hio_GetDictionaryFromInput(
    const std::string &input,
    const std::string &filename,
    std::string *errorStr);

FORGE_NAMESPACE_END

#endif
