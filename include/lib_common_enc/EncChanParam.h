// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup Encoder_Settings
   !@{
   \file
******************************************************************************/
#pragma once

#include "lib_common/SliceConsts.h"
#include "lib_common/VideoMode.h"
#include "lib_common/PicFormat.h"
#include "lib_rtos/lib_rtos.h"

/*****************************************************************************
   \brief Encoding parameters buffers (EP1, EP2, EP3 and EP4 buffers) sub buffer information
*****************************************************************************/
typedef struct AL_TBufInfo
{
  uint32_t Flag; /*!< Flag used as a bitfield bit position in an EP buffer to identify the sub buffer.*/
  size_t Size; /*!< Size of the sub buffer */
  size_t Offset; /*!< Offset of the sub buffer inside the EP buffer*/
}AL_TBufInfo;

/*****************************************************************************
   \brief Lambda Control Mode
*****************************************************************************/
typedef enum AL_ELdaCtrlMode
{
  AL_DEFAULT_LDA = 0x00, /*!< default behaviour */
  AL_CUSTOM_LDA = 0x01, /*!< used for test purpose */
  AL_DYNAMIC_LDA = 0x02, /*!< select lambda values according to the GOP pattern */
  AL_AUTO_LDA = 0x03, /*!< automatically select betxeen DEFAULT_LDA and DYNAMIC_LDA */
  AL_LOAD_LDA = 0x80, /*!< used for test purpose */
}AL_ELdaCtrlMode;

static inline bool AL_LdaIsSane(AL_ELdaCtrlMode lda)
{
  switch(lda)
  {
  case AL_DEFAULT_LDA: // fallthrough
  case AL_CUSTOM_LDA: // fallthrough
  case AL_DYNAMIC_LDA: // fallthrough
  case AL_AUTO_LDA: // fallthrough
  case AL_LOAD_LDA: // fallthrough
    return true;
  default:
    return false;
  }
}

/*****************************************************************************
   \brief GDR (Gradual Decoding Refresh) Mode
*****************************************************************************/
typedef enum AL_EGdrMode
{
  AL_GDR_OFF = 0x00,/*!< No GDR */
  AL_GDR_ON = 0x02,/*!< GDR is selected */
  AL_GDR_VERTICAL = AL_GDR_ON | 0x00,/*!< GDR is selected and the vertical intra refresh bar will move from left to right */
  AL_GDR_HORIZONTAL = AL_GDR_ON | 0x01,/*!< GDR is selected and the horizontal intra refresh bar will move from top to bottom */
  AL_GDR_MAX_ENUM, /* sentinel */
}AL_EGdrMode;

/*****************************************************************************
   \brief Multi chip clip mode
*****************************************************************************/
typedef enum AL_EMultiChipClipMode
{
  AL_MC_CLIP_NONE = 0x00,
  AL_MC_CLIP_LEFT = 0x01,
  AL_MC_CLIP_RIGHT = 0x02,
  AL_MC_CLIP_TOP = 0x04,
  AL_MC_CLIP_BOTTOM = 0x08,
  AL_MC_CLIP_MAX_ENUM,
}AL_EMultiChipClipMode;

/*****************************************************************************
   \brief Parameters for multi chip encoding
*****************************************************************************/
typedef AL_INTROSPECT (category = "debug") struct AL_TMultiChipParam
{
  AL_EMultiChipClipMode eMCClipMode;
  uint16_t uMCWidth;
  uint16_t uMCHeight;
  uint16_t uMCPosX;
  uint16_t uMCPosY;
}AL_TMultiChipParam;

/*****************************************************************************
   \brief Picture format enum
*****************************************************************************/
typedef enum AL_EPicFormat
{
  AL_400_8BITS = 0x0088,
  AL_420_8BITS = 0x0188,
  AL_422_8BITS = 0x0288,
  AL_444_8BITS = 0x0388,
  AL_400_10BITS = 0x00AA,
  AL_420_10BITS = 0x01AA,
  AL_422_10BITS = 0x02AA,
  AL_444_10BITS = 0x03AA,
  AL_400_12BITS = 0x00CC,
  AL_420_12BITS = 0x01CC,
  AL_422_12BITS = 0x02CC,
  AL_444_12BITS = 0x03CC,
}AL_EPicFormat;

static inline int AL_GET_BITDEPTH_LUMA(AL_EPicFormat ePicFormat)
{
  return ePicFormat & 0x000F;
}

static inline int AL_GET_BITDEPTH_CHROMA(AL_EPicFormat ePicFormat)
{
  return (ePicFormat & 0x00F0) >> 4;
}

static inline int AL_GET_BITDEPTH(AL_EPicFormat ePicFormat)
{
  return AL_GET_BITDEPTH_LUMA(ePicFormat) > AL_GET_BITDEPTH_CHROMA(ePicFormat) ? AL_GET_BITDEPTH_LUMA(ePicFormat) : AL_GET_BITDEPTH_CHROMA(ePicFormat);
}

static inline AL_EChromaMode AL_GET_CHROMA_MODE(AL_EPicFormat ePicFormat)
{
  return (AL_EChromaMode)((ePicFormat & 0x0F00) >> 8);
}

static inline void AL_SET_BITDEPTH_LUMA(AL_EPicFormat* pPicFormat, int iLumaBitDepth)
{
  Rtos_Assert(pPicFormat);
  Rtos_Assert(iLumaBitDepth <= 0xF);
  *pPicFormat = (AL_EPicFormat)((*pPicFormat & 0xFFF0) | (iLumaBitDepth & 0x000F));
}

static inline void AL_SET_BITDEPTH_CHROMA(AL_EPicFormat* pPicFormat, int iChromaBitDepth)
{
  Rtos_Assert(pPicFormat);
  Rtos_Assert(iChromaBitDepth <= 0xF);
  *pPicFormat = (AL_EPicFormat)((*pPicFormat & 0xFF0F) | ((iChromaBitDepth << 4) & 0x00F0));
}

static inline void AL_SET_BITDEPTH(AL_EPicFormat* pPicFormat, int iBitDepth)
{
  Rtos_Assert(pPicFormat);
  Rtos_Assert(iBitDepth <= 0xF);
  AL_SET_BITDEPTH_LUMA(pPicFormat, iBitDepth);
  AL_SET_BITDEPTH_CHROMA(pPicFormat, iBitDepth);
}

static inline void AL_SET_CHROMA_MODE(AL_EPicFormat* pPicFormat, AL_EChromaMode eChromaMode)
{
  Rtos_Assert(pPicFormat);
  Rtos_Assert((int)eChromaMode <= 0xF);
  *pPicFormat = (AL_EPicFormat)((*pPicFormat & 0xF0FF) | (((int)eChromaMode << 8) & 0x0F00));
}

/*****************************************************************************
   \brief Encoding High level syntax enum
*****************************************************************************/
typedef enum AL_EHlsFlag
{
  AL_SPS_LOG2_MAX_POC_MASK = 0x0000000F,
  AL_SPS_LOG2_MAX_FRAME_NUM_MASK = 0x000000F0,
  AL_SPS_LOG2_NUM_SHORT_TERM_RPS_MASK = 0x00003F00,
  AL_SPS_LOG2_NUM_LONG_TERM_RPS_MASK = 0x000FC000,
  AL_SPS_TEMPORAL_MVP_EN_FLAG = 0x00100000,

  AL_PPS_ENABLE_REORDERING = 0x00000001,
  AL_PPS_CABAC_INIT_PRES_FLAG = 0x00000002,
  AL_PPS_DBF_OVR_EN_FLAG = 0x00000004,
  AL_PPS_SLICE_SEG_EN_FLAG = 0x00000008,
  AL_PPS_NUM_ACT_REF_L0 = 0x000000F0,
  AL_PPS_NUM_ACT_REF_L1 = 0x00000F00,
  AL_PPS_OVERRIDE_LF = 0x00001000,
  AL_PPS_DISABLE_LF = 0x00002000,
  AL_PPS_SLICE_CHROMA_QP_OFFSET_PRES_FLAG = 0x00004000,
  AL_PPS_CU_QP_DELTA_EN_FLAG = 0x00008000,
}AL_EHlsFlag;

static inline uint32_t AL_GET_SPS_LOG2_MAX_POC(uint32_t uHlsParam)
{
  return (uHlsParam & AL_SPS_LOG2_MAX_POC_MASK) + 1;
}

static inline void AL_SET_SPS_LOG2_MAX_POC(uint32_t* pHlsParam, int iLog2MaxPoc)
{
  Rtos_Assert(pHlsParam);
  Rtos_Assert(iLog2MaxPoc <= 16);
  *pHlsParam = ((*pHlsParam & ~AL_SPS_LOG2_MAX_POC_MASK) | (iLog2MaxPoc - 1));
}

static inline uint32_t AL_GET_SPS_LOG2_MAX_FRAME_NUM(uint32_t uHlsParam)
{
  return (uHlsParam & AL_SPS_LOG2_MAX_FRAME_NUM_MASK) >> 4;
}

static inline void AL_SET_SPS_LOG2_MAX_FRAME_NUM(uint32_t* pHlsParam, int iLog2MaxFrameNum)
{
  Rtos_Assert(pHlsParam);
  Rtos_Assert(iLog2MaxFrameNum < 0xF);
  *pHlsParam = ((*pHlsParam & ~AL_SPS_LOG2_MAX_FRAME_NUM_MASK) | (iLog2MaxFrameNum << 4));
}

static inline uint32_t AL_GET_SPS_LOG2_NUM_SHORT_TERM_RPS(uint32_t uHlsParam)
{
  return (uHlsParam & AL_SPS_LOG2_NUM_SHORT_TERM_RPS_MASK) >> 8;
}

static inline void AL_SET_SPS_LOG2_NUM_SHORT_TERM_RPS(uint32_t* pHlsParam, int iLog2NumShortTermRps)
{
  Rtos_Assert(pHlsParam);
  Rtos_Assert(iLog2NumShortTermRps < 0x3F);
  *pHlsParam = ((*pHlsParam & ~AL_SPS_LOG2_NUM_SHORT_TERM_RPS_MASK) | (iLog2NumShortTermRps << 8));
}

static inline uint32_t AL_GET_SPS_LOG2_NUM_LONG_TERM_RPS(uint32_t uHlsParam)
{
  return (uHlsParam & AL_SPS_LOG2_NUM_LONG_TERM_RPS_MASK) >> 14;
}

static inline void AL_SET_SPS_LOG2_NUM_LONG_TERM_RPS(uint32_t* pHlsParam, int iLog2NumLongTermRps)
{
  Rtos_Assert(pHlsParam);
  Rtos_Assert(iLog2NumLongTermRps < 0xFC);
  *pHlsParam = ((*pHlsParam & ~AL_SPS_LOG2_NUM_LONG_TERM_RPS_MASK) | (iLog2NumLongTermRps << 14));
}

#define AL_GET_SPS_TEMPORAL_MVP_EN_FLAG(HlsParam) (((HlsParam) & AL_SPS_TEMPORAL_MVP_EN_FLAG) >> 20)

#define AL_GET_PPS_ENABLE_REORDERING(HlsParam) ((HlsParam) & AL_PPS_ENABLE_REORDERING)
#define AL_GET_PPS_CABAC_INIT_PRES_FLAG(HlsParam) (((HlsParam) & AL_PPS_CABAC_INIT_PRES_FLAG) >> 1)
#define AL_GET_PPS_DBF_OVR_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_DBF_OVR_EN_FLAG) >> 2)
#define AL_GET_PPS_SLICE_SEG_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_SLICE_SEG_EN_FLAG) >> 3)
#define AL_GET_PPS_OVERRIDE_LF(HlsParam) (((HlsParam) & AL_PPS_OVERRIDE_LF) >> 12)
#define AL_GET_PPS_DISABLE_LF(HlsParam) (((HlsParam) & AL_PPS_DISABLE_LF) >> 13)
#define AL_GET_PPS_SLICE_CHROMA_QP_OFFSET_PRES_FLAG(HlsParam) (((HlsParam) & AL_PPS_SLICE_CHROMA_QP_OFFSET_PRES_FLAG) >> 14)
#define AL_GET_PPS_CU_QP_DELTA_DEPTH_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_CU_QP_DELTA_EN_FLAG) >> 15)
#define AL_GET_PPS_CHROMA_OFFSET_TOOL_EN_FLAG(HlsParam) (((HlsParam) & AL_PPS_CHROMA_TOOL_OFFSET_EN_FLAG) >> 16)

static inline uint32_t AL_GET_PPS_NUM_ACT_REF_L0(uint32_t HlsParam)
{
  uint32_t uNumRefL0Minus1 = (HlsParam & AL_PPS_NUM_ACT_REF_L0) >> 4;

  if(uNumRefL0Minus1 > 0)
    --uNumRefL0Minus1;
  return uNumRefL0Minus1;
}

static inline uint32_t AL_GET_PPS_NUM_ACT_REF_L1(uint32_t HlsParam)
{
  uint32_t uNumRefL1Minus1 = (HlsParam & AL_PPS_NUM_ACT_REF_L1) >> 8;

  if(uNumRefL1Minus1 > 0)
    --uNumRefL1Minus1;
  return uNumRefL1Minus1;
}

static inline uint32_t AL_GetNumberOfRef(uint32_t HlsParam)
{
  /* this takes advantage of the fact that the number of L0 ref is always
   * bigger than the number of L1 refs */
  return (HlsParam & AL_PPS_NUM_ACT_REF_L0) >> 4;
}

#define AL_SET_PPS_NUM_ACT_REF_L0(HlsParam, Num) (HlsParam) = ((HlsParam) & ~AL_PPS_NUM_ACT_REF_L0) | ((Num) << 4)
#define AL_SET_PPS_NUM_ACT_REF_L1(HlsParam, Num) (HlsParam) = ((HlsParam) & ~AL_PPS_NUM_ACT_REF_L1) | ((Num) << 8)

/*****************************************************************************
   \brief Encoding option enum
*****************************************************************************/
typedef enum AL_EChEncOption
{
  AL_OPT_NONE = 0x00000000,
  AL_OPT_QP_TAB_RELATIVE = 0x00000001, /*!< External QP tables provide relative delta-QPs to add for each block on top of the frame-QP */
  AL_OPT_FIX_PREDICTOR = 0x00000002, /*!< Validation option: always centers the motion estimation window on the current LCU position */
  AL_OPT_CUSTOM_LDA = 0x00000004, /*!< INTERNAL PARAMETER - Do not tune */
  AL_OPT_ENABLE_AUTO_QP = 0x00000008, /*!< On each block, adapt the block-QP according to the block complexity, using static complexity thresholds */
  AL_OPT_ADAPT_AUTO_QP = 0x00000010, /*!< Complexity thresholds of Auto-QP are adjusted during stream encoding, depending on past frame complexities */
  AL_OPT_COMPRESS = 0x00000020, /*!< Reference YUV buffers are stored in compressed format */
  AL_OPT_FORCE_REC = 0x00000040, /*!< Force reconstructed buffers to be outputted by HW even if not used as a reference later. Necessary to get the reconstructed YUV stream. */
  AL_OPT_FORCE_MV_OUT = 0x00000080, /*!< Force motion vector buffers to be outputted by HW */
  AL_OPT_LOWLAT_SYNC = 0x00000100, /*!< Special synchronization mode for AVC low latency encoding */
  AL_OPT_LOWLAT_INT = 0x00000200, /*!< Special mode for sub-frame latency encoding. You get an interrupt on each slice instead of on each frame. */
  AL_OPT_L2_CACHE = 0x00000800, /*!< Enables L2 cache usage */
  AL_OPT_HIGH_FREQ = 0x00002000,  /*!< DEPRECATED */
  AL_OPT_SCENE_CHANGE_DETECTION = 0x00004000, /*!< Scene change detection based on a lookahead encoding */
  AL_OPT_FORCE_MV_CLIP = 0x00020000, /*!< Forces motion vector clipping in ranges specified in channel parameters */
  AL_OPT_RDO_COST_MODE = 0x00040000, /*!< Reinforces the influence of the chrominance in the RDO choice */
}AL_EChEncOption;

/*****************************************************************************
   \brief Encoding tools enum
*****************************************************************************/
typedef enum AL_EChEncTool
{
  AL_OPT_WPP = 0x00000001, /*!< DEPRECATED */
  AL_OPT_TILE = 0x00000002, /*!< INTERNAL PARAMETER - Do not tune */
  AL_OPT_LF = 0x00000004, /*!< Enables loop filter */
  AL_OPT_LF_X_SLICE = 0x00000008, /*!< Enables loop filter across slices */
  AL_OPT_LF_X_TILE = 0x00000010, /*!< Enables loop filter across tiles */
  AL_OPT_SCL_LST = 0x00000020, /*!< INTERNAL PARAMETER - Do not tune */
  AL_OPT_CONST_INTRA_PRED = 0x00000040, /*!< Specifies the value of constrained_intra_pred_flag syntax element */
  AL_OPT_SAO_Y = 0x00000200, /*!< Enable the Sample Adaptive Offset filter for luma only */
  AL_OPT_SAO_C = 0x00000400, /*!< Enable the Sample Adaptive Offset filter for chroma only */
  AL_OPT_SAO = 0x00000200, /*!< Enable the Sample Adaptive Offset filter */
  AL_OPT_PCM = 0x00000800, /*!< Enable PCM encoding (raw bloc encoding) */
  AL_OPT_DIRECT_SPATIAL = 0x00004000, /*!< AVC direct spatial motion vector candidate */

}AL_EChEncTool;

/*****************************************************************************
   \brief Rate Control Mode
*****************************************************************************/
typedef enum AL_ERateCtrlMode
{
  AL_RC_CONST_QP = 0x00,
  AL_RC_CBR = 0x01,
  AL_RC_VBR = 0x02,
  AL_RC_LOW_LATENCY = 0x03,
  AL_RC_CAPPED_VBR = 0x04,
  AL_RC_PROXY = 0x10,
  AL_RC_BYPASS = 0x3F,
  AL_RC_PLUGIN = 0x40,
  AL_RC_MAX_ENUM,
}AL_ERateCtrlMode;

/*****************************************************************************
   \brief Rate Control Options
*****************************************************************************/
typedef enum AL_ERateCtrlOption
{
  AL_RC_OPT_NONE = 0x00000000, /*!< No Option */
  AL_RC_OPT_SCN_CHG_RES = 0x00000001, /* internal */
  AL_RC_OPT_DELAYED = 0x00000002, /*!< The rate control update is delayed by one frame (This happens in Gen1 AVC multicore). This means another frame will already have started before we get the size of the first one. */
  AL_RC_OPT_STATIC_SCENE = 0x00000004, /* internal */
  AL_RC_OPT_ENABLE_SKIP = 0x00000008, /*!< Show if pictures can be skipped or not */
  AL_RC_OPT_SC_PREVENTION = 0x00000010, /* internal */
  AL_RC_OPT_MAX_ENUM,
}AL_ERateCtrlOption;

/*****************************************************************************
    \brief Rate Control parameters.
    Contains the user defined constraints on the stream in term of quality and bandwidth.
    Also contains the hardware constraints that will affect the rate control (See AL_RC_OPT_DELAYED)
*****************************************************************************/
typedef AL_INTROSPECT (category = "debug") struct __AL_ALIGNED__ (4) AL_TRCParam
{
  AL_ERateCtrlMode eRCMode;
  uint32_t uInitialRemDelay; /*!< Initial removal delay */
  uint32_t uCPBSize; /*!< Size of the Codec Picture Buffer */
  uint16_t uFrameRate; /*!< Number of frame per second */
  uint16_t uClkRatio; /*!< Clock ratio (1000 or 1001). Typical formula to obtain the final framerate is uFrameRate * 1000 / uClkRatio */
  uint32_t uTargetBitRate; /*!< The bitrate targeted by the user */
  uint32_t uMaxBitRate; /*!< The maximum bitrate allowed by the user */
  uint32_t uMaxConsecSkip; /*!< The maximum number of consecutive skip picture allowed */
  int16_t iInitialQP; /*!< Quality parameter of the first frame (in the absence of more information) */
  int16_t iMinQP[AL_MAX_FRAME_TYPE]; /*!< Minimum QP that can be used by the rate control implementation */
  int16_t iMaxQP[AL_MAX_FRAME_TYPE]; /*!< Maximum QP that can be used by the rate control implementation */
  int16_t uIPDelta; /*!< QP Delta that should be applied between I and P frames */
  int16_t uPBDelta; /*!< QP Delta that should be applied between P and B frames */
  bool bUseGoldenRef;
  int16_t uPGoldenDelta;
  int16_t uGoldenRefFrequency;
  AL_ERateCtrlOption eOptions; /*!< Options bitfield. \see AL_ERateCtrlOption for the available flags*/
  uint32_t uNumPel;
  uint16_t uMaxPSNR;
  uint16_t uMaxPelVal;
  uint32_t pMaxPictureSize[AL_MAX_FRAME_TYPE];
} AL_TRCParam;

static inline bool AL_IS_ENC_HW_RATE_CTRL_ENABLED(AL_TRCParam const* pRCParam)
{
  return (pRCParam->eRCMode == AL_RC_LOW_LATENCY)
         || (pRCParam->pMaxPictureSize[AL_SLICE_I] > 0)
         || (pRCParam->pMaxPictureSize[AL_SLICE_P] > 0)
         || (pRCParam->pMaxPictureSize[AL_SLICE_B] > 0);
}

/*****************************************************************************
   \brief GOP Control Mode
*****************************************************************************/
#define AL_GOP_FLAG_B_ONLY 0x01
#define AL_GOP_FLAG_DEFAULT 0x02
#define AL_GOP_FLAG_PYRAMIDAL 0x04
#define AL_GOP_FLAG_LOW_DELAY 0x08
typedef enum AL_EGopCtrlMode
{
  AL_GOP_MODE_DEFAULT = AL_GOP_FLAG_DEFAULT,
  AL_GOP_MODE_PYRAMIDAL = AL_GOP_FLAG_PYRAMIDAL,

  AL_GOP_MODE_DEFAULT_B = AL_GOP_FLAG_DEFAULT | AL_GOP_FLAG_B_ONLY,
  AL_GOP_MODE_PYRAMIDAL_B = AL_GOP_FLAG_PYRAMIDAL | AL_GOP_FLAG_B_ONLY,

  AL_GOP_MODE_LOW_DELAY_P = AL_GOP_FLAG_LOW_DELAY,
  AL_GOP_MODE_LOW_DELAY_B = AL_GOP_FLAG_LOW_DELAY | AL_GOP_FLAG_B_ONLY,

  AL_GOP_MODE_ADAPTIVE = 0x10,

  AL_GOP_MODE_BYPASS = 0x20,

  AL_GOP_MODE_MAX_ENUM,
}AL_EGopCtrlMode;

/*****************************************************************************
   \brief Group of Picture parameters.
*****************************************************************************/
typedef AL_INTROSPECT (category = "debug") struct __AL_ALIGNED__ (4) AL_TGopParam
{
  AL_EGopCtrlMode eMode;
  uint16_t uGopLength; /*!< Length of the Group Of Picture in the encoded stream */
  uint8_t uNumB; /*!< Number of B frames per Group of Picture in the encoded stream */
  uint8_t uFreqGoldenRef;
  uint32_t uFreqIDR; /*!< Frequency of the Instantaneous Decoding Refresh Picture. This is also used to determine the GDR frequency */
  bool bEnableLT;
  bool bWriteAvcHdrSvcExt;
  bool bDoubleRef;
  uint32_t uFreqLT;
  AL_EGdrMode eGdrMode;
  uint32_t uFreqRP;
  int8_t tempDQP[4];
} AL_TGopParam;

/*****************************************************************************
   \brief First Pass infos parameters
*****************************************************************************/
typedef struct AL_TLookAheadParam
{
  int32_t iSCPictureSize;
  int32_t iSCIPRatio;
  int16_t iComplexity;
  int16_t iTargetLevel;
}AL_TLookAheadParam;

/*****************************************************************************
   \brief Max burst size
*****************************************************************************/
typedef enum AL_EMaxBurstSize
{
  AL_BURST_256 = 0,
  AL_BURST_128 = 1,
  AL_BURST_64 = 2,
  AL_BURST_512 = 3,
}AL_EMaxBurstSize;

/*****************************************************************************
   \brief Source compression type
*****************************************************************************/
// [0] : CompMode | [3:1] : SourceFormat
typedef enum AL_ESrcMode
{
  AL_SRC_RASTER = 0x0,
  AL_SRC_TILE_64x4 = 0x4,
  AL_SRC_COMP_64x4 = 0x5,
  AL_SRC_TILE_32x4 = 0x6,
  AL_SRC_COMP_32x4 = 0x7,
  AL_SRC_RASTER_MSB = 0x8,
  AL_SRC_MAX_ENUM,
}AL_ESrcMode;

AL_DEPRECATED_ENUM_VALUE(AL_ESrcMode, AL_SRC_NVX, AL_SRC_RASTER, "Renamed. Use AL_SRC_RASTER.");

#define MASK_SRC_COMP 0x01
#define AL_GET_COMP_MODE(SrcConvFmt) ((SrcConvFmt) & MASK_SRC_COMP)
#define AL_SET_COMP_MODE(SrcConvFmt, CompMode) (SrcConvFmt) = ((SrcConvFmt) & ~MASK_SRC_COMP) | ((CompMode) & MASK_SRC_COMP)

/*****************************************************************************
   \brief AOM interpolation filter
*****************************************************************************/
typedef enum AL_EInterPFilter
{
  AL_INTERP_REGULAR,
  AL_INTERP_SMOOTH,
  AL_INTERP_SHARP,
  AL_INTERP_BILINEAR,
  AL_INTERP_SWITCHABLE,
  AL_INTERP_MAX_ENUM, /* sentinel */
}AL_EInterPFilter;

/*****************************************************************************
   \brief Extended merge candidates for VVC
*****************************************************************************/

/***************************************************************************/

#define AL_QP_CTRL_MAX_NUM_THRESHOLDS 6
#define AL_QP_CTRL_MAX_NUM_DELTA_QPS (AL_QP_CTRL_MAX_NUM_THRESHOLDS + 1)

typedef struct AL_TAutoQPCtrl
{
  uint32_t thresholdQP[AL_QP_CTRL_MAX_NUM_THRESHOLDS];
  int8_t deltaQP[AL_QP_CTRL_MAX_NUM_DELTA_QPS];
}AL_TAutoQPCtrl;

/*****************************************************************************
   \brief Channel parameters structure
*****************************************************************************/
typedef AL_INTROSPECT (category = "debug") struct __AL_ALIGNED__ (4) AL_TEncChanParam
{
  int iLayerID;

  /* Encoding resolution */
  uint16_t uEncWidth;
  uint16_t uEncHeight;

  /* Input resolution */
  uint16_t uSrcWidth;
  uint16_t uSrcHeight;

  bool bEnableSrcCrop;
  uint16_t uSrcCropWidth;
  uint16_t uSrcCropHeight;
  uint16_t uSrcCropPosX;
  uint16_t uSrcCropPosY;

  AL_EVideoMode eVideoMode;
  /* Encoding picture format */
  AL_EPicFormat ePicFormat;
  bool bVideoFullRange;
  AL_ESrcMode eSrcMode;
  /* Input picture bitdepth */
  uint8_t uSrcBitDepth;

  /* encoding profile/level */
  AL_EProfile eProfile;
  uint8_t uLevel;
  uint8_t uTier;

  uint32_t uSpsParam;
  uint32_t uPpsParam;

  bool bForcePpsIdToZero;

  /* Encoding tools parameters */
  AL_EChEncOption eEncOptions;
  AL_EChEncTool eEncTools;
  int8_t iBetaOffset;
  int8_t iTcOffset;

  int8_t iCbSliceQpOffset;
  int8_t iCrSliceQpOffset;
  int8_t iCbPicQpOffset;
  int8_t iCrPicQpOffset;

  uint8_t WeightedPred; // unused for encoder yet
  bool Direct8x8Infer;

  uint8_t uCuQPDeltaDepth;
  uint8_t uCabacInitIdc;

  uint8_t uNumCore;
  uint16_t uSliceSize;
  uint16_t uNumSlices;

  uint16_t uClipHrzRange;
  uint16_t uClipVrtRange;
  int8_t iL2CacheTolerance;

  AL_TMultiChipParam tMCParam;

  int iQPTableDepth;

  /* MV range */
  int16_t pMeRange[2][2];  /*!< Allowed range for motion estimation */

  /* encoding block size */
  uint8_t uLog2MaxCuSize;
  uint8_t uLog2MinCuSize;
  uint8_t uLog2MaxTuSize;
  uint8_t uLog2MaxTuSkipSize;
  uint8_t uLog2MinTuSize;
  uint8_t uMaxTransfoDepthIntra;
  uint8_t uMaxTransfoDepthInter;
  bool StrongIntraSmooth; // HEVC only

  AL_EEntropyMode eEntropyMode;
  AL_EWPMode eWPMode;

  bool bUseGMV;

  AL_TRCParam tRCParam; /*!< Rate control parameters */
  AL_TGopParam tGopParam; /*!< Group of Pictures parameters */
  bool bNonRealtime; /*!< Specify non-realtime encoding */
  bool bSubframeLatency;
  AL_ELdaCtrlMode eLdaCtrlMode;
  int LdaFactors[6];

  uint16_t uMVVRange;

  int8_t MaxNumMergeCand;

  uint32_t zRcPluginDmaSize; /*!< Size of the rate control plugin dma buffer (user defined data can be given using this buffer) */
  AL_64U pRcPluginDmaContext; /*!< Physical address of the rate control plugin dma buffer (This is filled by the library, see AL_TEncSettings.hRcPluginDmaContext for the handle you need to allocate in dma) */

  bool bEnableOutputCrop;
  uint16_t uOutputCropWidth;
  uint16_t uOutputCropHeight;
  uint16_t uOutputCropPosX;
  uint16_t uOutputCropPosY;
  uint8_t uSrcSyncChanID;
  bool bSrcSync;
  bool bUseUniformSliceType;
  AL_EStartCodeBytesAlignedMode eStartCodeBytesAligned;

  AL_TAutoQPCtrl sUserAutoQPValues;
  bool bUserAutoQP;
} AL_TEncChanParam;

/***************************************************************************/
#define ROUND_POWER_OF_TWO(value, n) (((value) + (1 << ((n) - 1))) >> (n))
#define ROUND_UP_POWER_OF_TWO(value, n) (((value) + (1 << (n)) - 1) >> (n))
#define AL_GetWidthInLCU(tChParam) (ROUND_UP_POWER_OF_TWO((tChParam).uEncWidth, (tChParam).uLog2MaxCuSize))
#define AL_GetHeightInLCU(tChParam) (ROUND_UP_POWER_OF_TWO((tChParam).uEncHeight, (tChParam).uLog2MaxCuSize))

#define AL_ENTCOMP(tChParam) true

#define AL_GetSrcWidth(tChParam) ((tChParam).uSrcWidth)
#define AL_GetSrcHeight(tChParam) ((tChParam).uSrcHeight)

#define AL_RC_FIRSTPASS_QP 20

/****************************************************************************/
static inline bool AL_IS_CBR(AL_ERateCtrlMode eRcMode)
{
  bool bIsCbr = eRcMode == AL_RC_CBR;
  return bIsCbr;
}

/*!@}*/
