// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup lib_base
   !@{
   \file
 *****************************************************************************/
#pragma once

#include "lib_rtos/types.h"
#include "lib_common/BufCommonInternal.h"
#include "lib_common/SliceConsts.h"

/*****************************************************************************/
#define AL_DEC_OPT_EnableSclLst 0x00000001
#define AL_DEC_OPT_LoadSclLst 0x00000002
#define AL_DEC_OPT_SignHiding 0x00000004
#define AL_DEC_OPT_TransfoSkipCtx 0x00000008
#define AL_DEC_OPT_TransfoSkipRot 0x00000010
#define AL_DEC_OPT_IntraPCM 0x00000020
#define AL_DEC_OPT_AMP 0x00000040
#define AL_DEC_OPT_LossLess 0x00000080
#define AL_DEC_OPT_IntraOnly 0x00000100
#define AL_DEC_OPT_Direct8x8Infer 0x00000200// AVC
#define AL_DEC_OPT_SkipTransfo 0x00000200// HEVC
#define AL_DEC_OPT_CabacBypassAlign 0x00000400
#define AL_DEC_OPT_RiceAdapt 0x00000800
#define AL_DEC_OPT_ExplicitRdpcmFlag 0x00001000
#define AL_DEC_OPT_ImplicitRdpcmFlag 0x00002000
#define AL_DEC_OPT_ExtPrecisionFlag 0x00004000
#define AL_DEC_OPT_XTileLoopFilter 0x00008000
#define AL_DEC_OPT_DisPCMLoopFilter 0x00010000
#define AL_DEC_OPT_IntraSmoothDisable 0x00020000
#define AL_DEC_OPT_StrongIntraSmooth 0x00040000
#define AL_DEC_OPT_ConstrainedIntraPred 0x00080000
#define AL_DEC_OPT_HighPrecOffset 0x00100000
#define AL_DEC_OPT_Tile 0x00200000
#define AL_DEC_OPT_WaveFront 0x00400000
#define AL_DEC_OPT_CuQPDeltaFlag 0x00800000
#define AL_DEC_OPT_CrossCompPred 0x01000000

#define AL_SET_DEC_OPT(pPictParam, Opt, Val) (pPictParam)->OptionFlags = (((pPictParam)->OptionFlags & ~(AL_DEC_OPT_ ## Opt)) | (((Val) * (AL_DEC_OPT_ ## Opt)) & (AL_DEC_OPT_ ## Opt)))
#define AL_GET_DEC_OPT(pPictParam, Opt) ((pPictParam)->OptionFlags & (AL_DEC_OPT_ ## Opt))

/****************************************************************************/
typedef struct AL_TDecBufIDs
{
  uint8_t FrmID;
  uint8_t MvID;
}AL_TDecBufIDs;

static const AL_TDecBufIDs tEmptyBufIDs =
{
  0xFF, 0xFF,
};

/*****************************************************************************
   \brief Slice Parameters : Mimics structure for IP registers
*****************************************************************************/
typedef struct AL_TDecPictParam
{
  AL_ECodec Codec;

  AL_TDecBufIDs tBufIDs;

  uint8_t MaxTransfoDepthIntra;
  uint8_t MaxTransfoDepthInter;
  uint8_t Log2MinTUSize;
  uint8_t Log2MaxTUSize;
  uint8_t Log2MaxTUSkipSize;
  int8_t Log2MinPCMSize;
  int8_t Log2MaxPCMSize;
  int8_t Log2MinCUSize;
  uint8_t Log2MaxCUSize;
  uint8_t PcmBitDepthY;
  uint8_t PcmBitDepthC;
  uint8_t BitDepthLuma;
  uint8_t BitDepthChroma;
  uint8_t ChromaQpOffsetDepth;
  uint8_t QpOffLstSize;
  uint8_t ParallelMerge;
  uint8_t ColocPicID;

  int8_t PicCbQpOffset;
  int8_t PicCrQpOffset;
  int8_t CbQpOffLst[6];
  int8_t CrQpOffLst[6];
  int8_t DeltaQPCUDepth;

  uint16_t PicWidth;
  uint16_t PicHeight;
  uint16_t LcuPicWidth;
  uint16_t LcuPicHeight;
  uint16_t tile_column_width[AL_MAX_COLUMNS_TILE];
  uint16_t tile_row_height[AL_MAX_ROWS_TILE];
  uint16_t num_tile_columns;
  uint16_t num_tile_rows;

  int32_t CurrentPOC;
  AL_EPicStruct ePicStruct;

  uint32_t OptionFlags;

  AL_EChromaMode ChromaMode;
  AL_EEntropyMode eEntMode;

  int32_t iFrmNum;
  AL_64U UserParam;

  uint8_t log2_sao_offset_scale_luma;
  uint8_t log2_sao_offset_scale_chroma;

  bool cross_component_prediction;
}AL_TDecPicParam;

/****************************************************************************/
typedef struct AL_TDecBuffers
{
  TBuffer tCompData;
  TBuffer tCompMap;
  TBuffer tStream;
  TBuffer tListRef;
  TBuffer tListVirtRef; // only used for traces
  TBuffer tRecY;
  TBuffer tRecC1;
  TBuffer tRecC2;
  TBuffer tRecFbcMapY;
  TBuffer tRecFbcMapC1;
  TBuffer tRecFbcMapC2;
  TBuffer tScl;
  TBuffer tPoc;
  TBuffer tMV;
  TBuffer tWP;

  uint32_t uPitch;

  TBuffer tRecSecondOutputY;
  TBuffer tRecSecondOutputC1;
  TBuffer tRecSecondOutputC2;
  uint32_t uPitchSecondOutput;

}AL_TDecBuffers;

/****************************************************************************/
typedef struct AL_TDecPictBufferAddrs
{
  AL_PADDR pRecY;
  AL_PADDR pRecC1;
  AL_PADDR pRecC2;
  AL_PADDR pRecFbcMapY;
  AL_PADDR pRecFbcMapC1;
  AL_PADDR pRecFbcMapC2;
  uint32_t uPitch;
  AL_PADDR pRecSecondOutputY;
  AL_PADDR pRecSecondOutputC1;
  AL_PADDR pRecSecondOutputC2;
  uint32_t uPitchSecondOutput;
}AL_TDecPictBufferAddrs;

/****************************************************************************/
typedef struct AL_TDecBufferAddrs
{
  AL_PADDR pCompData;
  AL_PADDR pCompMap;
  AL_PADDR pListRef;
  AL_PADDR pStream;
  uint32_t uStreamSize;
  AL_PADDR pScl;
  AL_PADDR pPoc;
  AL_PADDR pMV;
  AL_PADDR pWP;
  AL_TDecPictBufferAddrs tDecBuffers;
}AL_TDecBufferAddrs;

/****************************************************************************/
typedef struct AL_TJpegBufferAddrs
{
  AL_PADDR pStream;
  uint32_t uStreamSize;
  uint32_t uOffset;
  uint32_t uAvailSize;
  AL_PADDR pHuff;
  AL_PADDR pMinMaxTab;
  AL_PADDR pQuantTab;
  AL_TDecPictBufferAddrs tDecBuffers;
}AL_TJpegBufferAddrs;

/*****************************************************************************/
typedef uint8_t AL_TDecPicState;
static const AL_TDecPicState AL_DEC_PIC_STATE_CONCEAL = 0x01;
static const AL_TDecPicState AL_DEC_PIC_STATE_HANGED = 0x02;
static const AL_TDecPicState AL_DEC_PIC_STATE_NOT_FINISHED = 0x04; /* LLP2: the frame is not finished yet */
static const AL_TDecPicState AL_DEC_PIC_STATE_CMD_INVALID = 0x08;

#define AL_DEC_ENABLE_PIC_STATE(picState, picFlag) (picState) |= (picFlag)
#define AL_DEC_DISABLE_PIC_STATE(picState, picFlag) (picState) &= ~(picFlag)
#define AL_DEC_SET_PIC_STATE(picState, picFlag, picVal) (picState) = (picVal) ? ((picState) | (picFlag)) : ((picState) & (~(picFlag)))
#define AL_DEC_IS_PIC_STATE_ENABLED(picState, picFlag) (((picState) & (picFlag)) != 0)

/*****************************************************************************/
typedef struct AL_TDecPicStatus
{
  AL_TDecBufIDs tBufIDs;

  uint32_t uNumLCU;
  uint32_t uNumBytes;
  uint32_t uNumBins;
  uint32_t uNumConcealedLCU;
  bool bConcealed;
  uint32_t uCRC;
  AL_TDecPicState tDecPicState;
}AL_TDecPicStatus;

/*****************************************************************************/

/*!@}*/
