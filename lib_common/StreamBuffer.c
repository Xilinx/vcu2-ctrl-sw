// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/StreamBuffer.h"
#include "lib_common/StreamBufferPrivate.h"
#include "lib_common/Utils.h"
#include "lib_common/AvcLevelsLimit.h"
#include "lib_common/HevcLevelsLimit.h"

static const uint8_t STREAM_ALLOC_LOG2_MINCUSIZE = 4;
static const uint8_t STREAM_ALLOC_LOG2_MAXCUSIZE = 6;

/****************************************************************************/
static int GetOneLCUPCMSize(AL_EChromaMode eChromaMode, uint8_t uLog2MaxCuSize, uint8_t uBitDepth)
{
  static const uint16_t AL_PCM_SIZE[4][3] =
  {
    { 256, 1024, 4096 }, { 384, 1536, 6144 }, { 512, 2048, 8192 }, { 768, 3072, 12288 }
  };
  return AL_PCM_SIZE[eChromaMode][uLog2MaxCuSize - 4] * uBitDepth / 8;
}

/****************************************************************************/
int32_t GetPCMSize(int32_t iNumLCU, uint8_t uLog2MaxCuSize, AL_EChromaMode eChromaMode, uint8_t uBitDepth, bool bIntermediateBuffer)
{
  (void)bIntermediateBuffer;

  // Sample cost
  int32_t iLCUSize = GetOneLCUPCMSize(eChromaMode, uLog2MaxCuSize, uBitDepth);

  if(bIntermediateBuffer)
  {
    // PCM mode cost (12bits max) + byte alignment (7bits max)
    iLCUSize += 3;
  }

  // Rounding because of potential tiling
  iLCUSize = RoundUp(iLCUSize, HW_IP_BURST_ALIGNMENT);

  return iNumLCU * iLCUSize;
}

/****************************************************************************/
int GetPcmVclNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth)
{
  /* We round the dimensions according to the maximum LCU size, but then
  compute stream size according the the minimum LCU size. Indeed, smaller LCU
  can give bigger PCM sizes due to rounding */
  uint32_t uNumLCU = GetSquareBlkNumber(tDim, 1 << STREAM_ALLOC_LOG2_MAXCUSIZE);
  uNumLCU <<= 2 * (STREAM_ALLOC_LOG2_MAXCUSIZE - STREAM_ALLOC_LOG2_MINCUSIZE);
  return GetPCMSize(uNumLCU, STREAM_ALLOC_LOG2_MINCUSIZE, eMode, iBitDepth, false);
}

/****************************************************************************/
int Hevc_GetMaxVclNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth)
{
  int iLCUSize = GetOneLCUPCMSize(eMode, STREAM_ALLOC_LOG2_MAXCUSIZE, iBitDepth);
  /* Spec. A.3.2, A.3.3: Number of bits in the macroblock is at most: 5 * RawCtuBits / 3. */
  iLCUSize = (iLCUSize * 5 + 2) / 3;
  // Round at LCU?
  int iSize = GetSquareBlkNumber(tDim, 1 << STREAM_ALLOC_LOG2_MAXCUSIZE) * iLCUSize;
  return RoundUp(iSize, HW_IP_BURST_ALIGNMENT);
}

/****************************************************************************/
int AL_GetMaxNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth, AL_EProfile eProfile, int iLevel)
{
  (void)iLevel;

  AL_ECodec eCodec = AL_GET_CODEC(eProfile);

  int iMaxPCM = (eCodec == AL_CODEC_HEVC) ? Hevc_GetMaxVclNalSize(tDim, eMode, iBitDepth) : GetPcmVclNalSize(tDim, eMode, iBitDepth);

  int iNumSlices = 1;

  if(eCodec == AL_CODEC_AVC)
    iNumSlices = AL_AVC_GetMaxNumberOfSlices(eProfile, iLevel, 1, 60, INT32_MAX);

  if(eCodec == AL_CODEC_HEVC)
    iNumSlices = AL_HEVC_GetMaxNumberOfSlices(iLevel);

  int iMaxNalSize = iMaxPCM + AL_ENC_MAX_HEADER_SIZE + (iNumSlices * AL_MAX_SLICE_HEADER_SIZE);

  return RoundUp(iMaxNalSize, HW_IP_BURST_ALIGNMENT);
}

/****************************************************************************/
int AL_GetMitigatedMaxNalSize(AL_TDimension tDim, AL_EChromaMode eMode, int iBitDepth)
{
  /* Mitigated worst case: PCM + one slice per row. */
  int iMaxPCM = GetPcmVclNalSize(tDim, eMode, iBitDepth);
  int iNumSlices = ((tDim.iHeight + 15) / 16);
  iMaxPCM += AL_ENC_MAX_HEADER_SIZE + (iNumSlices * AL_MAX_SLICE_HEADER_SIZE);

  return RoundUp(iMaxPCM, HW_IP_BURST_ALIGNMENT);
}

/****************************************************************************/
int AL_GetMinimalNalSize(int iNumSlices, AL_ECodec eCodec)
{
  (void)eCodec;

  bool bHasHeaders = true;
  int iNumNal = 16;

  if(eCodec == AL_CODEC_JPEG)
  {
    bHasHeaders = false;
    iNumNal = 0;
  }
  int iNonVclSize = bHasHeaders ? RoundUp(AL_ENC_MAX_HEADER_SIZE, HW_IP_BURST_ALIGNMENT) : 0;
  int iSliceHdrSize = bHasHeaders ? iNumSlices* RoundUp(AL_MAX_SLICE_HEADER_SIZE, HW_IP_BURST_ALIGNMENT) : 0;

  int const AL_ENC_STREAM_PART_SIZE = 2 * sizeof(uint32_t);
  int iStreamPartSize = RoundUp((iNumSlices + iNumNal) * AL_ENC_STREAM_PART_SIZE, 128);
  int const iHardwareMinimalBurst = 128;

  return iNonVclSize + iSliceHdrSize + iStreamPartSize + iHardwareMinimalBurst;
}
