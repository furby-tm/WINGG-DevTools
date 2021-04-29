#line 1 "C:/Users/tyler/dev/WINGG/forge/usd/usdVol/api.h"
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
#ifndef USDVOL_API_H
#define USDVOL_API_H

#include "forge/base/arch/export.h"

#if defined(FORGE_STATIC)
#   define USDVOL_API
#   define USDVOL_API_TEMPLATE_CLASS(...)
#   define USDVOL_API_TEMPLATE_STRUCT(...)
#   define USDVOL_LOCAL
#else
#   if defined(USDVOL_EXPORTS)
#       define USDVOL_API ARCH_EXPORT
#       define USDVOL_API_TEMPLATE_CLASS(...) ARCH_EXPORT_TEMPLATE(class, __VA_ARGS__)
#       define USDVOL_API_TEMPLATE_STRUCT(...) ARCH_EXPORT_TEMPLATE(struct, __VA_ARGS__)
#   else
#       define USDVOL_API ARCH_IMPORT
#       define USDVOL_API_TEMPLATE_CLASS(...) ARCH_IMPORT_TEMPLATE(class, __VA_ARGS__)
#       define USDVOL_API_TEMPLATE_STRUCT(...) ARCH_IMPORT_TEMPLATE(struct, __VA_ARGS__)
#   endif
#   define USDVOL_LOCAL ARCH_HIDDEN
#endif

#endif
