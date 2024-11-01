// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/******************************************************************************
   \addtogroup lib_decode_hls
   !@{
   \file
 *****************************************************************************/

#pragma once

#include "I_PictMngr.h"
#include "lib_common_dec/DecPicParam.h"

/*****************************************************************************
   \brief This function updates the reconstructed resolution information
   \param[in] pCtx Pointer to a Picture manager context object
   \param[in] pCropInfo Pointer to Cropping information
   \param[in] ePicStruct Picture structure (frame/field, top/Bottom) of the current frame buffer
*****************************************************************************/
void AL_HEVC_PictMngr_UpdateRecInfo(AL_TPictMngrCtx* pCtx, AL_TCropInfo const* pCropInfo, AL_EPicStruct ePicStruct);

/*****************************************************************************
   \brief Remove from the DPB all unused pictures(non-reference and not needed for output
   \param[in] pCtx           Pointer to a Picture manager context object
   \param[in] pSPS           Pointer to the Sequence Parameter Set structure holding info on picture dpb latency
   \param[in] bClearRef      Specifies if the reference pool picture is cleared
   \param[in] bNoOutputPrior Specifies if the pictures still stored in the DPB will whether be output or discarded when bClearRef = true
*****************************************************************************/
void AL_HEVC_PictMngr_ClearDPB(AL_TPictMngrCtx* pCtx, AL_THevcSps const* pSPS, bool bClearRef, bool bNoOutputPrior);

/*****************************************************************************
   \brief This function updates the Picture Manager context each time a picture have been decoded.
   \param[in] pCtx            Pointer to a Picture manager context object
   \param[in] uPocLsb         Value used to identify long term reference picture
   \param[in] eNUT            NalUnitType of the current decoded picture
   \param[in] pSlice          Pointer to the last slice header current's frame
   \param[in] pic_output_flag Specifies whether the current picture is displayed or not
*****************************************************************************/
void AL_HEVC_PictMngr_EndFrame(AL_TPictMngrCtx* pCtx, uint32_t uPocLsb, AL_ENut eNUT, AL_THevcSliceHdr const* pSlice, uint8_t pic_output_flag);

/*****************************************************************************
   \brief This function remove from the DPB the oldest picture if it is full.
   \param[in] pCtx            Pointer to a Picture manager context object
*****************************************************************************/
void AL_HEVC_PictMngr_RemoveHeadFrame(AL_TPictMngrCtx* pCtx);

/*****************************************************************************
   \brief This function return true if the DPB has reference..
   \param[in] pCtx   Pointer to a Picture manager context object
*****************************************************************************/
bool AL_HEVC_PictMngr_HasPictInDPB(AL_TPictMngrCtx const* pCtx);

/*****************************************************************************
   \brief Retrieves all buffers (input and output) required to decode the current slice
   \param[in]  pCtx          Pointer to a Picture manager context object
   \param[in]  pPP           Pointer to the current picture parameters
   \param[in]  pSP           Pointer to the current slice parameters
   \param[out] pListVirtAddr used for traces
   \param[out] pListAddr     Pointer to the buffer that will receive the references, colocated POC and colocated motion vectors address list
   \param[out] pPOC         Receives pointer to the POC buffer where
                          reference Pictures order count are stored.
   \param[out] pMV          Receives pointer to the MV buffer where
                          Motion Vectors should be stored.
   \param[out] pRecs         Receives pointer to the frame buffers where reconstructed pictures should be stored.
   \return If the function succeeds the return value is nonzero (true)
        If the function fails the return value is zero (false)
*****************************************************************************/
bool AL_HEVC_PictMngr_GetBuffers(AL_TPictMngrCtx* pCtx, AL_TDecSliceParam const* pSP, TBuffer* pListVirtAddr, TBuffer* pListAddr, TBufferPOC* pPOC, TBufferMV* pMV, AL_TRecBuffers* pRecs);

/*****************************************************************************
   \brief Prepares the reference picture set for the current slice reference picture list construction
   \param[in]  pCtx       Pointer to a Picture manager context object
   \param[in]  pSlice     Pointer to the slice header of the current slice
*****************************************************************************/
void AL_HEVC_PictMngr_InitRefPictSet(AL_TPictMngrCtx* pCtx, AL_THevcSliceHdr const* pSlice);

/*****************************************************************************
   \brief Builds the reference picture list of the current slice
   \param[in]  pCtx     Pointer to a Picture manager context object
   \param[in]  pSlice   Pointer to the slice header of the current slice
   \param[out] pListRef Pointer to the current reference list
*****************************************************************************/
bool AL_HEVC_PictMngr_BuildPictureList(AL_TPictMngrCtx* pCtx, AL_THevcSliceHdr const* pSlice, TBufferListRef* pListRef);

/*!@}*/
