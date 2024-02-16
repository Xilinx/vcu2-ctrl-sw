// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "DecHardwareConfig.h"

AL_EChromaMode AL_HWConfig_Dec_GetSupportedChromaMode(void)
{
  return AL_CHROMA_4_4_4;
}

int AL_HWConfig_Dec_GetSupportedBitDepth(void)
{
  return 12;
}

AL_EChromaMode AL_HWConfig_Dec_GetJpegSupportedChromaMode(void)
{
  return AL_CHROMA_4_4_4;
}

int AL_HWConfig_Dec_GetJpegSupportedBitDepth(void)
{
  return 12;
}

