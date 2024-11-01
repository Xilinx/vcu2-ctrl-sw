// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_rtos/lib_rtos.h"
#include "lib_decode/DecSettingsInternal.h"
#include "lib_common_dec/StreamSettingsInternal.h"
#include "lib_common_dec/DecHardwareConfig.h"
#include "lib_common/Utils.h"
#include "lib_common/Profiles.h"
#include "lib_common/BufConst.h"

/***************************************************************************/
#define MSGF(msg, ...) { if(pOut) fprintf(pOut, msg "\r\n", __VA_ARGS__); }
#define MSG(msg) { if(pOut) fprintf(pOut, msg "\r\n"); }

/***************************************************************************/
void AL_DecSettings_SetDefaults(AL_TDecSettings* pSettings)
{
  Rtos_Assert(pSettings);
  Rtos_Memset(pSettings, 0, sizeof(*pSettings));

  pSettings->iStackSize = 2;
  pSettings->uNumCore = NUMCORE_AUTO;
  pSettings->uFrameRate = 60000;
  pSettings->uClkRatio = 1000;
  pSettings->uDDRWidth = 32;
  pSettings->eDecUnit = AL_AU_UNIT;
  pSettings->eDpbMode = AL_DPB_NORMAL;
  pSettings->eFBStorageMode = AL_FB_TILE_64x4;
  pSettings->tStream.eChroma = AL_CHROMA_MAX_ENUM;
  pSettings->tStream.eSequenceMode = AL_SM_MAX_ENUM;
  pSettings->eCodec = AL_CODEC_HEVC;
  pSettings->bUseIFramesAsSyncPoint = false;
  pSettings->uNumBuffersHeldByNextComponent = 1;
  pSettings->eInputMode = AL_DEC_UNSPLIT_INPUT;

  pSettings->tStream.tDim.iWidth = STREAM_SETTING_UNKNOWN;
  pSettings->tStream.tDim.iHeight = STREAM_SETTING_UNKNOWN;
  pSettings->tStream.iBitDepth = STREAM_SETTING_UNKNOWN;
  pSettings->tStream.eProfile = STREAM_SETTING_UNKNOWN;
  pSettings->tStream.iLevel = STREAM_SETTING_UNKNOWN;
  pSettings->tStream.bDecodeIntraOnly = false;
  pSettings->tStream.iMaxRef = 0;
}

/***************************************************************************/
int AL_DecSettings_CheckValidity(AL_TDecSettings const* pSettings, FILE* pOut)
{
  Rtos_Assert(pSettings);

  int err = 0;

  uint8_t uMaxNumCore = AL_DEC_NUM_CORES;

  if(pSettings->eCodec == AL_CODEC_JPEG)
    uMaxNumCore = AL_DEC_NUM_CORE_JPEG;

  if(pSettings->uNumCore > uMaxNumCore)
  {
    ++err;
    MSGF("Invalid parameter: NumCore. You can use up to %d core(s) for this codec.", uMaxNumCore);
  }

  if(pSettings->uDDRWidth != 16 && pSettings->uDDRWidth != 32 && pSettings->uDDRWidth != 64)
  {
    ++err;
    MSG("Invalid DDR width.");
  }

  bool bAllStreamSettingsSet = IsAllStreamSettingsSet(&pSettings->tStream);

  if(IsAtLeastOneStreamSettingsSet(&pSettings->tStream))
  {
    if(!bAllStreamSettingsSet)
    {
      ++err;
      MSG("Invalid prealloc settings. Each parameter must be specified.");
    }
    else
    {
      if(pSettings->tStream.iBitDepth > AL_HWConfig_Dec_GetSupportedBitDepth())
      {
        ++err;
        MSG("Invalid prealloc settings. Specified bit-depth is incompatible with HW.");
      }

      if(pSettings->tStream.eChroma > AL_HWConfig_Dec_GetSupportedChromaMode())
      {
        ++err;
        MSG("Invalid prealloc settings. Specified chroma-mode is incompatible with HW.");
      }
    }
  }

  const int HStep = (pSettings->eFBStorageMode == AL_FB_TILE_64x4) ? 64 :
                    (pSettings->eFBStorageMode == AL_FB_TILE_32x4) ? 32 :
                    (pSettings->tStream.eChroma == AL_CHROMA_4_2_0) || (pSettings->tStream.eChroma == AL_CHROMA_4_2_0) ? 2 : 1;
  const int VStep = (pSettings->eFBStorageMode == AL_FB_RASTER) ?
                    (pSettings->tStream.eChroma == AL_CHROMA_4_2_0 ? 2 : 1) :
                    (pSettings->tStream.eChroma == AL_CHROMA_4_2_0 ? 8 : 4);

  if((pSettings->tOutputPosition.iX % HStep) != 0 || (pSettings->tOutputPosition.iY % VStep) != 0)
  {
    ++err;
    MSG("The output position doesn't fit the alignment constraints for the current buffer format");
  }

  if(pSettings->tStream.bDecodeIntraOnly && !(pSettings->eCodec == AL_CODEC_AVC || pSettings->eCodec == AL_CODEC_HEVC || pSettings->eCodec == AL_CODEC_VVC))
  {
    ++err;
    MSG("The decode IntraOnly mode is only available with AVC, HEVC and VVC");
  }

  if(pSettings->tStream.bDecodeIntraOnly && !(pSettings->eDecUnit == AL_AU_UNIT))
  {
    ++err;
    MSG("The decode IntraOnly mode is only available in frame latency");
  }

  return err;
}

/***************************************************************************/
int AL_DecSettings_CheckCoherency(AL_TDecSettings* pSettings, FILE* pOut)
{
  Rtos_Assert(pSettings);

  int numIncoherency = 0;

  int iMinStackSize = 1;

  if(pSettings->eCodec == AL_CODEC_JPEG)
    iMinStackSize = (pSettings->uNumCore == NUMCORE_AUTO ? AL_DEC_NUM_CORE_JPEG : pSettings->uNumCore) * AL_DEC_NUM_JPEG_PER_CORE;

  if(pSettings->iStackSize < iMinStackSize)
  {
    MSGF("!! Stack size must be greater or equal than %d. Adjusting parameter !!", iMinStackSize);
    pSettings->iStackSize = iMinStackSize;
    ++numIncoherency;
  }

  if(pSettings->iStreamBufSize > 0)
  {
    int iAlignedStreamBufferSize = GetAlignedStreamBufferSize(pSettings->iStreamBufSize);

    if(iAlignedStreamBufferSize != pSettings->iStreamBufSize)
    {
      MSG("!! Aligning stream buffer size to HW constraints !!");
      pSettings->iStreamBufSize = iAlignedStreamBufferSize;
    }
  }

  if(IsAllStreamSettingsSet(&pSettings->tStream))
  {
    if(pSettings->eCodec == AL_CODEC_AVC)
    {
      static int const AVC_ROUND_DIM = 16;

      if(((pSettings->tStream.tDim.iWidth % AVC_ROUND_DIM) != 0) || ((pSettings->tStream.tDim.iHeight % AVC_ROUND_DIM) != 0))
      {
        MSG("!! AVC preallocation dimensions must be multiple of 16. Adjusting parameter !!");
        pSettings->tStream.tDim.iWidth = RoundUp(pSettings->tStream.tDim.iWidth, AVC_ROUND_DIM);
        pSettings->tStream.tDim.iHeight = RoundUp(pSettings->tStream.tDim.iHeight, AVC_ROUND_DIM);
        ++numIncoherency;
      }
    }
  }

  return numIncoherency;
}

int GetAlignedStreamBufferSize(int iStreamBufferSize)
{
  /* Buffer size must be aligned with hardware requests. For VP9/AV1, alignment to 32 bytes is required. For other
     codecs, 2048 or 4096 bytes alignment is required for dec1 units (for old or new decoder respectively).
  */
  static int const BITSTREAM_REQUEST_SIZE = 4096;
  return RoundUp(iStreamBufferSize, BITSTREAM_REQUEST_SIZE);
}

int AL_DecOutputSettings_CheckValidity(AL_TDecOutputSettings const* pDecOutSettings, AL_ECodec eCodec, FILE* pOut)
{
  Rtos_Assert(pDecOutSettings);
  (void)eCodec;
  (void)pOut;
  int err = 0;

  return err;
}
