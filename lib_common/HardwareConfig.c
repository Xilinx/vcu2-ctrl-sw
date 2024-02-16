// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/HardwareConfig.h"

AL_EChromaMode AL_HWConfig_Enc_GetSupportedChromaMode(void)
{
  return AL_CHROMA_4_4_4;
}

int AL_HWConfig_Enc_GetSupportedBitDepth(void)
{
  return 12;
}

