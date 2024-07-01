// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_common/PicFormat.h"
#include "lib_decode/I_DecSchedulerInfo.h"
#include "lib_decode/lib_decode.h"
#include "lib_decode/DefaultDecoder.h"
#include "lib_common_dec/DecBuffersInternal.h"
#include "lib_rtos/types.h"
#include "lib_common_dec/I_DecArch.h"

AL_ERR CreateAvcDecoder(AL_TDecoder** hDec, AL_IDecScheduler* pScheduler, AL_TAllocator* pAllocator, AL_TDecSettings* pSettings, AL_TDecCallBacks* pCB);
AL_ERR CreateHevcDecoder(AL_TDecoder** hDec, AL_IDecScheduler* pScheduler, AL_TAllocator* pAllocator, AL_TDecSettings* pSettings, AL_TDecCallBacks* pCB);
AL_ERR CreateJpegDecoder(AL_TDecoder** hDec, AL_IDecScheduler* pScheduler, AL_TAllocator* pAllocator, AL_TDecSettings* pSettings, AL_TDecCallBacks* pCB);

static bool CheckVersion(AL_TIDecSchedulerVersion const* pVersion)
{
  if(pVersion->version.uMajor != AL_VERSION_MAJOR)
    return false;

  if(pVersion->version.uMinor != AL_VERSION_MINOR)
    return false;

  if(pVersion->version.uPatch != AL_VERSION_PATCH)
    return false;
  return true;
}

/****************************************************************************/
static AL_ERR AL_Decoder_Create_Host(AL_HDecoder* hDec, void* pSch, AL_TAllocator* pAllocator, void* pSet, void* pCallBacks)
{
  if(!pSet || !pCallBacks || !pAllocator || !pSch || !hDec)
    return AL_ERROR;

  AL_IDecScheduler* pScheduler = (AL_IDecScheduler*)pSch;
  AL_TDecSettings* pSettings = (AL_TDecSettings*)pSet;
  AL_TDecCallBacks* pCB = (AL_TDecCallBacks*)pCallBacks;

  AL_TIDecSchedulerVersion tVersion;
  AL_IDecScheduler_Get(pScheduler, AL_IDECSCHEDULER_VERSION, &tVersion);

  if(!CheckVersion(&tVersion))
    return AL_ERROR;

  if(pSettings->eCodec == AL_CODEC_AVC)
    return CreateAvcDecoder((AL_TDecoder**)hDec, pScheduler, pAllocator, pSettings, pCB);

  if(pSettings->eCodec == AL_CODEC_HEVC)
    return CreateHevcDecoder((AL_TDecoder**)hDec, pScheduler, pAllocator, pSettings, pCB);

  if(pSettings->eCodec == AL_CODEC_JPEG)
    return CreateJpegDecoder((AL_TDecoder**)hDec, pScheduler, pAllocator, pSettings, pCB);

  return AL_ERROR;
}

/*****************************************************************************/
static AL_ERR AL_Decoder_CreateWithCtx_Host(AL_HDecoder* hDec, AL_RiscV_Ctx ctx, AL_TAllocator* pAllocator, void* pSettings, void* pCB)
{
  (void)hDec;
  (void)ctx;
  (void)pAllocator;
  (void)pSettings;
  (void)pCB;

  return AL_ERROR;
}

/*****************************************************************************/
static AL_ECodec getCodec(AL_HDecoder hDec)
{
  AL_TDecoder* pDec = (AL_TDecoder*)hDec;
  return pDec->ctx.pChanParam ? pDec->ctx.pChanParam->eCodec : AL_CODEC_INVALID;
}

/*****************************************************************************/
static void AL_Decoder_Destroy_Host(AL_HDecoder hDec)
{
  AL_Default_Decoder_Destroy((AL_TDecoder*)hDec);
}

/*****************************************************************************/
static void AL_Decoder_SetParam_Host(AL_HDecoder hDec, const char* sPrefix, int iFrmID, int iNumFrm, bool bForceCleanBuffers, bool bShouldPrintFrameDelimiter)
{
  AL_Default_Decoder_SetParam((AL_TDecoder*)hDec, sPrefix, iFrmID, iNumFrm, bForceCleanBuffers, bShouldPrintFrameDelimiter);
}

/*****************************************************************************/
static void AL_Decoder_SetInternalFrameBuffersAllocator_Host(AL_HDecoder hDec, AL_TAllocator* pAllocator)
{
  AL_Default_Decoder_SetInternalFrameBuffersAllocator((AL_TDecoder*)hDec, pAllocator);
}

/*****************************************************************************/
static bool AL_Decoder_PushStreamBuffer_Host(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize, uint8_t uFlags)
{
  return AL_Default_Decoder_PushStreamBuffer((AL_TDecoder*)hDec, pBuf, uSize, uFlags);
}

/*****************************************************************************/
static bool AL_Decoder_PushBuffer_Host(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize)
{
  return AL_Default_Decoder_PushBuffer((AL_TDecoder*)hDec, pBuf, uSize);
}

/*****************************************************************************/
static void AL_Decoder_Flush_Host(AL_HDecoder hDec)
{
  AL_Default_Decoder_Flush((AL_TDecoder*)hDec);
}

/*****************************************************************************/
static bool AL_Decoder_PutDisplayPicture_Host(AL_HDecoder hDec, AL_TBuffer* pDisplay)
{
  return AL_Default_Decoder_PutDecPict((AL_TDecoder*)hDec, pDisplay);
}

/*****************************************************************************/
static bool AL_Decoder_ConfigureOutputSettings_Host(AL_HDecoder hDec, AL_TDecOutputSettings const* pDecOutputSettings)
{
  return AL_Default_Decoder_ConfigureOutputSettings((AL_TDecoder*)hDec, pDecOutputSettings);
}

/*****************************************************************************/
static int AL_Decoder_GetMaxBD_Host(AL_HDecoder hDec)
{
  return AL_Default_Decoder_GetMaxBD((AL_TDecoder*)hDec);
}

/*****************************************************************************/
static AL_ECodec AL_Decoder_GetCodec_Host(AL_HDecoder hDec)
{
  return getCodec(hDec);
}

/*****************************************************************************/
static AL_ERR AL_Decoder_GetLastError_Host(AL_HDecoder hDec)
{
  return AL_Default_Decoder_GetLastError((AL_TDecoder*)hDec);
}

/*****************************************************************************/
static AL_ERR AL_Decoder_GetFrameError_Host(AL_HDecoder hDec, AL_TBuffer const* pBuf)
{
  AL_TDecoder* pDec = (AL_TDecoder*)hDec;
  return AL_Default_Decoder_GetFrameError(pDec, pBuf);
}

/*****************************************************************************/
static bool AL_Decoder_PreallocateBuffers_Host(AL_HDecoder hDec)
{
  AL_TDecoder* pDec = (AL_TDecoder*)hDec;
  return AL_Default_Decoder_PreallocateBuffers(pDec);
}

static int32_t AL_Decoder_GetMinPitch_Host(int32_t iWidth, AL_TPicFormat const* pPicFormat)
{
  return RndPitch(iWidth, pPicFormat);
}

static int32_t AL_Decoder_GetMinStrideHeight_Host(int32_t iHeight, AL_TPicFormat const* pPicFormat)
{
  return RndHeight(iHeight, pPicFormat);
}

/*****************************************************************************/
UNIT_ERROR AL_Decoder_TryDecodeOneUnit(AL_HDecoder hDec, AL_TBuffer* pBufStream)
{
  return AL_Default_Decoder_TryDecodeOneUnit((AL_TDecoder*)hDec, pBufStream);
}

/*****************************************************************************/
int AL_Decoder_GetDecodedStrOffset(AL_HDecoder hDec)
{
  return AL_Default_Decoder_GetStrOffset((AL_TDecoder*)hDec);
}

/*****************************************************************************/
int AL_Decoder_SkipParsedUnits(AL_HDecoder hDec)
{
  return AL_Default_Decoder_SkipParsedNals((AL_TDecoder*)hDec);
}

/*****************************************************************************/
void AL_Decoder_InternalFlush(AL_HDecoder hDec)
{
  AL_Default_Decoder_InternalFlush((AL_TDecoder*)hDec);
}

/*****************************************************************************/
void AL_Decoder_FlushInput(AL_HDecoder hDec)
{
  AL_Default_Decoder_FlushInput((AL_TDecoder*)hDec);
}

/*****************************************************************************/
void AL_Deinit_Host(void)
{
  ;
}

static AL_IDecArchVtable vtable =
{
  .Deinit = AL_Deinit_Host,
  .DecoderCreate = AL_Decoder_Create_Host,
  .DecoderCreateWithCtx = AL_Decoder_CreateWithCtx_Host,
  .DecoderDestroy = AL_Decoder_Destroy_Host,
  .DecoderSetParam = AL_Decoder_SetParam_Host,
  .DecoderSetInternalFrameBuffersAllocator = AL_Decoder_SetInternalFrameBuffersAllocator_Host,
  .DecoderPushStreamBuffer = AL_Decoder_PushStreamBuffer_Host,
  .DecoderPushBuffer = AL_Decoder_PushBuffer_Host,
  .DecoderFlush = AL_Decoder_Flush_Host,
  .DecoderPutDisplayPicture = AL_Decoder_PutDisplayPicture_Host,
  .DecoderGetCodec = AL_Decoder_GetCodec_Host,
  .DecoderGetMaxBD = AL_Decoder_GetMaxBD_Host,
  .DecoderGetLastError = AL_Decoder_GetLastError_Host,
  .DecoderGetFrameError = AL_Decoder_GetFrameError_Host,
  .DecoderPreallocateBuffers = AL_Decoder_PreallocateBuffers_Host,
  .DecoderGetMinPitch = AL_Decoder_GetMinPitch_Host,
  .DecoderGetMinStrideHeight = AL_Decoder_GetMinStrideHeight_Host,
  .DecoderSetDecOutputSettings = AL_Decoder_ConfigureOutputSettings_Host,
};

AL_IDecArch decHost =
{
  .vtable = &vtable
};

/*****************************************************************************/
AL_IDecArch* LibDecodeHostGet(void)
{
  return &decHost;
}
