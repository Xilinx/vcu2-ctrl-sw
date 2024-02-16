// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common_enc/EncPicInfo.h"
#include "PictureInfo.h"
#include "RefInfo.h"

/*************************************************************************//*!
   \brief Picture parameters structure
*****************************************************************************/
typedef struct AL_TEncPicParam
{
  AL_TEncInfo tEncInfo;
  AL_TPictureInfo tPicInfo;
  AL_TRefInfo tRefInfo;
  AL_TRpsInfo tRpsInfo;

  uint8_t uNumPicTotalCurr;
  int32_t iLastIdrId;
}AL_TEncPicParam;

typedef struct
{
  AL_64U pStrmUserPtr;
  uint8_t* pStream_v;
  AL_PADDR pStream;
  int32_t iMaxSize;
  int32_t iOffset;
  int32_t iStreamPartOffset;
  uint8_t* pExternalMV_v;
}AL_EncStreamInfo;
/*************************************************************************//*!
   \brief Picture buffers structure
*****************************************************************************/
typedef struct AL_TRecInfo
{
  uint8_t uBitDepth;
  uint32_t uPitchY;
  uint32_t uPitchC;
  uint8_t uFormat;
  uint8_t uMapPitch;
}AL_TRecInfo;

typedef struct AL_TRecAddrs
{
  AL_PADDR pY;
  AL_PADDR pMapY;
  AL_PADDR pC1;
  AL_PADDR pMapC1;
  AL_PADDR pC2;
  AL_PADDR pMapC2;
}AL_TRecAddrs;

typedef struct AL_TEncPicBufAddrsFull
{
  AL_TEncPicBufAddrs tBasic;

  AL_TRecAddrs tRefAAddrs;
  AL_TRecAddrs tRefBAddrs;
  AL_TRecAddrs tRecAddrs;

  AL_PADDR pColoc;
  AL_PADDR pMV;
  AL_PADDR pWPP;
  AL_PADDR pEP1;
  AL_PADDR pEP3;
  AL_PADDR pIntermediateMap;
  AL_PADDR pIntermediateData;
  AL_TRecInfo tRecInfo;
  AL_EncStreamInfo* pStreamInfo;
  AL_VADDR pMV_v;
  AL_VADDR pWPP_v;
  AL_VADDR pEP3_v;
  AL_VADDR pEP1_v;
}AL_TEncPicBufAddrsFull;
