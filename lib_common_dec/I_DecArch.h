// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_decode_hls
   @{
   \file
 *****************************************************************************/

#pragma once

/****************************************************************************/
typedef AL_HANDLE AL_HDecoder;

typedef struct AL_IDecArchVtable AL_IDecArchVtable;

typedef struct AL_IDecArch
{
  const AL_IDecArchVtable* vtable;
}AL_IDecArch;

typedef struct AL_IDecArchVtable
{
  void (* Deinit)(void);
  AL_ERR (* DecoderCreate)(AL_HDecoder* hDec, void* pScheduler, AL_TAllocator* pAllocator, void* pSettings, void* pCB);
  AL_ERR (* DecoderCreateWithCtx)(AL_HDecoder* hDec, AL_RiscV_Ctx ctx, AL_TAllocator* pAllocator, void* pSettings, void* pCB);
  void (* DecoderDestroy)(AL_HDecoder hDec);
  void (* DecoderSetParam)(AL_HDecoder hDec, const char* sPrefix, int iFrmID, int iNumFrm, bool bForceCleanBuffers, bool bShouldPrintFrameDelimiter);
  void (* DecoderSetInternalFrameBuffersAllocator)(AL_HDecoder hDec, AL_TAllocator* pAllocator);
  bool (* DecoderPushStreamBuffer)(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize, uint8_t uFlags);
  bool (* DecoderPushBuffer)(AL_HDecoder hDec, AL_TBuffer* pBuf, size_t uSize);
  void (* DecoderFlush)(AL_HDecoder hDec);
  bool (* DecoderPutDisplayPicture)(AL_HDecoder hDec, AL_TBuffer* pDisplay);
  AL_ECodec (* DecoderGetCodec)(AL_HDecoder hDec);
  int (* DecoderGetMaxBD)(AL_HDecoder hDec);
  AL_ERR (* DecoderGetLastError)(AL_HDecoder hDec);
  AL_ERR (* DecoderGetFrameError)(AL_HDecoder hDec, AL_TBuffer const* pBuf);
  bool (* DecoderPreallocateBuffers)(AL_HDecoder hDec);
  uint32_t (* DecoderGetMinPitch)(uint32_t uWidth, AL_TPicFormat const* pPicFormat);
  uint32_t (* DecoderGetMinStrideHeight)(uint32_t uHeight);
  bool (* DecoderSetDecOutputSettings)(AL_HDecoder hDec, AL_TDecOutputSettings const* pDecOutputSettings);
}AL_IDecArchVtable;

/*@}*/
