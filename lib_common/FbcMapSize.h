// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/PicFormat.h"

uint16_t AL_GetFbcMapPitch(uint32_t uWidth, AL_EFbStorageMode eFBStorageMode, uint8_t uBitDepth);
uint32_t AL_GetFbcMapSize(AL_TDimension tDimension, AL_TPicFormat const* pPicFormat);
uint32_t AL_GetFbcMapUVSize(AL_TDimension tDimension, AL_TPicFormat const* pPicFormat);
