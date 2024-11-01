// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_common/PicFormat.h"
#include "lib_common/Planes.h"
#include "lib_common/FourCC.h"
#include "lib_common/BufferMeta.h"

/*****************************************************************************
   \brief Give the size of a reconstructed picture buffer
   Restriction: The strideHeight is supposed to be the minimum stride height
   \param[in] tDim dimensions of the picture
   \param[in] iPitch luma pitch in bytes of the picture
   \param[in] tPicFormat picture format of the frame buffer
   \return return the size of the reconstructed picture buffer
*****************************************************************************/
int AL_DecGetAllocSize_Frame(AL_TDimension tDim, int iPitch, AL_TPicFormat tPicFormat);

/*****************************************************************************
   \brief Give the size of one pixel component of a reconstructed picture buffer
   \param[in] pPicFormat picture format of the frame
   \param[in] tDim dimensions of the picture
   \param[in] iPitch component pitch in bytes of the picture
   \param[in] ePlaneId The pixel plane type. Must not be a map plane.
   \return return the size of the pixel component of the reconstructed buffer
*****************************************************************************/
int AL_DecGetAllocSize_Frame_PixPlane(AL_TPicFormat const* pPicFormat, AL_TDimension tDim, int iPitch, AL_EPlaneId ePlaneId);

/*****************************************************************************
   \brief Give the size of one map component of a reconstructed picture buffer
   \param[in] pPicFormat picture format of the frame
   \param[in] tDim dimensions of the picture
   \param[in] ePlaneId The map plane type. Must not be a pixel plane.
   \return return the size of the map component of the reconstructed buffer
*****************************************************************************/
int AL_DecGetAllocSize_Frame_MapPlane(AL_TPicFormat const* pPicFormat, AL_TDimension tDim, AL_EPlaneId ePlaneId);

/*****************************************************************************
   \brief Create the AL_TMetaData associated to the reconstruct buffers
   \param[in] tDim Frame dimension (width, height) in pixel
   \param[in] tFourCC FourCC of the frame buffer
   \param[in] iPitch Pitch of the frame buffer
   \return the AL_TMetaData
*****************************************************************************/
AL_TMetaData* AL_CreateRecBufMetaData(AL_TDimension tDim, int iPitch, TFourCC tFourCC);

AL_DEPRECATED("Use AL_DecGetAllocSize_Frame_PixPlane.")
int AL_DecGetAllocSize_Frame_Y(AL_EFbStorageMode eFbStorage, AL_TDimension tDim, int iPitch);
AL_DEPRECATED("Use AL_DecGetAllocSize_Frame_PixPlane.")
int AL_DecGetAllocSize_Frame_UV(AL_EFbStorageMode eFbStorage, AL_TDimension tDim, int iPitch, AL_EChromaMode eChromaMode);
AL_DEPRECATED("Use AL_DecGetAllocSize_Frame_MapPlane.")
int AL_DecGetAllocSize_Frame_MapY(AL_EFbStorageMode eFbStorage, bool bFrameBufferCompression, AL_TDimension tDim);
AL_DEPRECATED("Use AL_DecGetAllocSize_Frame_MapPlane.")
int AL_DecGetAllocSize_Frame_MapUV(AL_EFbStorageMode eFbStorage, bool bFrameBufferCompression, AL_TDimension tDim, AL_EChromaMode eChromaMode);
