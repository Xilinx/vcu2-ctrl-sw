// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \defgroup Encoder_Settings Settings
   \ingroup Encoder

   !@{
   \file
******************************************************************************/
#pragma once

#include <stdio.h>
#include "lib_rtos/types.h"
#include "lib_common/SliceConsts.h"
#include "lib_common/FourCC.h"
#include "EncChanParam.h"
#include "lib_common/HDR.h"

/*****************************************************************************
   \brief Aspect Ratio identifier
*****************************************************************************/
typedef enum AL_EAspectRatio
{
  AL_ASPECT_RATIO_AUTO,
  AL_ASPECT_RATIO_1_1,
  AL_ASPECT_RATIO_4_3,
  AL_ASPECT_RATIO_16_9,
  AL_ASPECT_RATIO_NONE,
  AL_ASPECT_RATIO_MAX_ENUM, /* sentinel */
}AL_EAspectRatio;

/*****************************************************************************
   \brief QP Control Mode
*****************************************************************************/
typedef enum AL_EQpCtrlMode
{
  AL_QP_CTRL_NONE,
  AL_QP_CTRL_AUTO,
  AL_QP_CTRL_ADAPTIVE_AUTO,
  AL_QP_CTRL_MAX_ENUM,
}AL_EQpCtrlMode;

static inline bool AL_IS_AUTO_OR_ADAPTIVE_QP_CTRL(AL_EQpCtrlMode eMode)
{
  return (eMode == AL_QP_CTRL_AUTO) || (eMode == AL_QP_CTRL_ADAPTIVE_AUTO);
}

/*****************************************************************************
   \brief QP Table Mode
*****************************************************************************/
typedef enum AL_EQpTableMode
{
  AL_QP_TABLE_NONE,
  AL_QP_TABLE_RELATIVE,
  AL_QP_TABLE_ABSOLUTE,
  AL_QP_TABLE_MAX_ENUM,
}AL_EQpTableMode;

static inline bool AL_IS_QP_TABLE_REQUIRED(AL_EQpTableMode eMode)
{
  return (eMode == AL_QP_TABLE_RELATIVE) || (eMode == AL_QP_TABLE_ABSOLUTE);
}

/*****************************************************************************
   \brief Scaling List identifier
*****************************************************************************/
typedef enum AL_EScalingList
{
  AL_SCL_FLAT, /*!< All matrices coefficients set to 16 */
  AL_SCL_DEFAULT, /*!< Use default matrices coefficients as defined in the codec specification */
  AL_SCL_CUSTOM, /*!< Use custom matrices coefficients */
  AL_SCL_MAX_ENUM, /* sentinel */
}AL_EScalingList;

typedef struct AL_TColorConfig
{
  AL_EColourDescription eColourDescription; /*!< Indicates the chromaticity coordinates of the source primaries in terms of the CIE 1931 definition. */
  AL_ETransferCharacteristics eTransferCharacteristics; /*!< Specifies the reference opto-electronic transfer characteristic function */
  AL_EColourMatrixCoefficients eColourMatrixCoeffs; /*!< Specifies the matrix coefficients used in deriving luma and chroma signals from RGB */
}AL_TColorConfig;

/*****************************************************************************
   \brief Encoder Parameters
*****************************************************************************/
typedef AL_INTROSPECT (category = "debug") struct AL_TEncSettings
{
  AL_TEncChanParam tChParam[MAX_NUM_LAYER]; /*!< Specifies the Channel parameters of the correspondong layer. Except for SHVC encoding (when supported) only layer 0 is used.*/
  bool bEnableAUD; /*!< Enable Access Unit Delimiter nal unit in the stream */
  AL_EFillerCtrlMode eEnableFillerData; /*!< Allows Filler Data Nal unit insertion when needed (CBR) */
  uint32_t uEnableSEI; /*!< Bit-field specifying which SEI message have to be inserted. see AL_SeiFlag for a list of the supported SEI messages */

  AL_TColorConfig tColorConfig;
  AL_EAspectRatio eAspectRatio; /*!< Specifies the sample aspect ratio of the luma samples. */
  AL_EScalingList eScalingList; /*!< Specifies which kind of scaling matrices is used for encoding. When set to AL_SCL_CUSTOM, the customized value shall be provided int the ScalingList and DCcoeff parameters below*/
  bool bDependentSlice; /*!< Enable the dependent slice mode */

  bool bDisIntra; /*!< Disable Intra preiction Mode in P or B slice (validation purpose only) */
  bool bForceLoad; /*!< Specifies if the work buffers are reloaded each time by the IP, recommended value : true */
  uint16_t uClipHrzRange; /*!< Specifies the Horizontal motion vector range. Note: this range can be further reduce by the encoder according to various constraints*/
  uint16_t uClipVrtRange; /*!< Specifies the Vertical motion vector range. Note: this range can be further reduce by the encoder according to various constraints*/
  AL_EQpCtrlMode eQpCtrlMode; /*!< Specifies the QP control mode inside a frame; see AL_EQpCtrlMode for available modes */
  AL_EQpTableMode eQpTableMode; /*!< Specifies the QP table mode. See AL_EQpTableMode for available modes */
  int NumView; /*!< Specifies the number of view when multi-view encoding is supported. */
  int NumLayer; /*!< Specifies the number of layer (1 or 2) when SHVC is supported. */
  uint8_t ScalingList[4][6][64]; /*!< The scaling matrix coeffecients [S][M][C] where S=0 for 4x4, S=1 for 8x8, S=2 for 16x16 and S=3 for 32x32; M=0 for Intra Y, M=1 for Intra U, M=2 for intra V, M=3 for inter Y, M=4 for inter U and M=5 for interV; and where C is the coeffecient index. Note1 in 4x4 only the 16 first coeffecient are used; Note2 in 32x32 only intra Y inter Y matrices are used */
  uint8_t SclFlag[4][6]; /*!< Specifies whether the corresponding ScalingList is valid or not */
  uint8_t DcCoeff[8]; /*!< The DC coeffidients for matrices 16x16 intra Y, 16x16 intra U, 16x16 intra V, 16x16 inter Y, 16x16 inter U, 16x16 inter V, 32x32 intra Y and 32x32 inter Y in that order*/
  uint8_t DcCoeffFlag; /*!< Specifies whether the corresponding DcCoeff is valid or not */
  bool bEnableWatchdog; /*!< Enable the watchdog interrupt. This parameter should be set to 'false' until further advise */
  int LookAhead; /*!< Enables the lookahead encoding mode (not zero) and specifies the number of frame ahead. This option is exclusive with TwoPass and bEnableFirstPassSceneChangeDetection. */
  int TwoPass; /*!< Enables the dual-pass encoding mode (not zero) and specifies the current pass (1 or 2). This option is exclusive with LookAhead and bEnableFirstPassSceneChangeDetection. */
  bool bEnableFirstPassSceneChangeDetection; /*!< Enables the quick firstpass mode for scene change detection only. This option is exclusive with LookAhead and TwoPass. */
  AL_HANDLE hRcPluginDmaContext; /*!< Handle to the dma buffer given to the rate control plugin to pass user defined data to the plugin. This should be allocated with a dma allocator */
  bool bDiagnostic; /*!< Additional checks meant for debugging. Not to be used on default usecase. */
}AL_TEncSettings;

/*****************************************************************************
   \brief Retrieves the default settings
   \param[out] pSettings Pointer to TEncSettings structure that receives
   default Settings.
*****************************************************************************/
void AL_Settings_SetDefaults(AL_TEncSettings* pSettings);

void AL_Settings_SetDefaultParam(AL_TEncSettings* pSettings);

void AL_Settings_SetDefaultRCParam(AL_TRCParam* pRCParam);

/*****************************************************************************
   \brief Checks that all encoding parameters are valids
   \param[in] pSettings Pointer to TEncSettings to be checked
   \param[in] pChParam Pointer to the channel parameters to be checked
   \param[in] pOut Optional standard stream on which verbose messages are
   written.
   \return If pSettings point to valid parameters the function returns false
   If pSettings point to invalid parameters the function returns
   the number of invalid parameters found (true);
   and this Settings can not be used with IP encoder.
*****************************************************************************/
int AL_Settings_CheckValidity(AL_TEncSettings* pSettings, AL_TEncChanParam* pChParam, FILE* pOut);

/******************************************************************************
   \brief Checks that encoding parameters are coherent between them.
   When incoherent parameter are found, the function automatically correct them.
   \param[in] pSettings Pointer to TEncSettings to be checked
   \param[in] pChParam Pointer to the channel parameters to be checked
   \param[in] tFourCC Encoding tFourCC format
   \param[in] pOut Optional standard stream on which verbose messages are
   written.
   \return 0 if no incoherency
           the number of incoherency if incoherency were found
           -1 if a fatal incoherency was found
   Since the function automatically apply correction, the Settings can be then
   used with IP encoder.
 *****************************************************************************/
int AL_Settings_CheckCoherency(AL_TEncSettings* pSettings, AL_TEncChanParam* pChParam, TFourCC tFourCC, FILE* pOut);

/*!@}*/
