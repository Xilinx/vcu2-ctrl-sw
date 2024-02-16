// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/PicFormat.h"

AL_EChromaMode AL_HWConfig_Dec_GetSupportedChromaMode(void);
int AL_HWConfig_Dec_GetSupportedBitDepth(void);

AL_EChromaMode AL_HWConfig_Dec_GetJpegSupportedChromaMode(void);
int AL_HWConfig_Dec_GetJpegSupportedBitDepth(void);
