// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "EncSize.h"
#include "lib_common/StreamBufferPrivate.h"

/****************************************************************************/
int AL_GetCompDataSize(uint32_t uNumLCU, uint8_t uLog2MaxCUSize, uint8_t uBitDepth, AL_EChromaMode eChromaMode, bool bUseEnt)
{

  if(bUseEnt)
    return GetPCMSize(uNumLCU, uLog2MaxCUSize, eChromaMode, uBitDepth, true);

  (void)uNumLCU, (void)uLog2MaxCUSize, (void)uBitDepth, (void)eChromaMode, (void)bUseEnt;
  // header + MVDs + residuals words size
  return uNumLCU * 1312;
}

/****************************************************************************/
