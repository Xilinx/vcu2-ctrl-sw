// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/****************************************************************************
   -----------------------------------------------------------------------------
 **************************************************************************//*!
   \addtogroup lib_encode
   @{
   \file
 *****************************************************************************/

#pragma once

#include "lib_rtos/types.h"
#include "lib_common_enc/EncPicInfo.h"
#include "lib_common_enc/EncRecBuffer.h"
#include "lib_common/BufferAPI.h"
#include "lib_common/MemDesc.h"
#include "lib_encode/I_EncSchedulerInfo.h"

/****************************************************************************/
static const AL_HANDLE AL_INVALID_CHANNEL = (AL_HANDLE)(NULL);

/*************************************************************************//*!
   \brief Scheduler callbacks structure
*****************************************************************************/
typedef struct
{
  void (* func)(void* pUserParam, AL_TEncPicStatus* pPicStatus, AL_64U streamUserPtr);
  void* userParam;
}AL_TEncScheduler_CB_EndEncoding;

/****************************************************************************/
typedef struct AL_IEncSchedulerVtable AL_IEncSchedulerVtable;

typedef struct AL_IEncScheduler
{
  const AL_IEncSchedulerVtable* vtable;
}AL_IEncScheduler;

typedef struct AL_IEncSchedulerVtable
{
  void (* destroy)(AL_IEncScheduler* pScheduler);
  AL_ERR (* createChannel)(AL_HANDLE* hChannel, AL_IEncScheduler* pScheduler, TMemDesc* pMDChParam, TMemDesc* pEP1, AL_HANDLE hRcPluginDmaCtx, AL_TEncScheduler_CB_EndEncoding* pCBs);
  bool (* destroyChannel)(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel);
  bool (* encodeOneFrame)(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TEncInfo* pEncInfo, AL_TEncRequestInfo* pReqInfo, AL_TEncPicBufAddrs* pBufferAddrs);
  void (* putStreamBuffer)(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TBuffer* pStream, AL_64U streamUserPtr, uint32_t uOffset);
  bool (* getRecPicture)(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TRecPic* pRecPic);
  bool (* releaseRecPicture)(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TRecPic* pRecPic);
  void (* get)(AL_IEncScheduler const* pScheduler, AL_EIEncSchedulerInfo info, void* pParam);
  void (* set)(AL_IEncScheduler* pScheduler, AL_EIEncSchedulerInfo info, void const* pParam);
}AL_IEncSchedulerVtable;

/*************************************************************************//*!
   \brief De-initializes the scheduler
*****************************************************************************/
void AL_IEncScheduler_Destroy(AL_IEncScheduler* pScheduler);

/*************************************************************************//*!
   \brief Scheduler getter
*****************************************************************************/
void AL_IEncScheduler_Get(AL_IEncScheduler const* pScheduler, AL_EIEncSchedulerInfo eInfo, void* pParam);

/*************************************************************************//*!
   \brief Scheduler setter
*****************************************************************************/
void AL_IEncScheduler_Set(AL_IEncScheduler* pScheduler, AL_EIEncSchedulerInfo eInfo, void const* pParam);

/*************************************************************************//*!
   \brief Channel creation
   \param[out] opaque valid handle on success, AL_INVALID_CHANNEL otherwise
   \param[in] pMDChParam Pointer to the memory descriptor containing the channel
   parameters
   \param[in] pCBs Pointer to the callbacks (See Scheduler callbacks)
   \return errorcode explaining why the channel creation failed
*****************************************************************************/
static inline
AL_ERR AL_IEncScheduler_CreateChannel(AL_HANDLE* hChannel, AL_IEncScheduler* pScheduler, TMemDesc* pMDChParam, TMemDesc* pEP1, AL_HANDLE hRcPluginDmaCtx, AL_TEncScheduler_CB_EndEncoding* pCBs)
{
  return pScheduler->vtable->createChannel(hChannel, pScheduler, pMDChParam, pEP1, hRcPluginDmaCtx, pCBs);
}

/*************************************************************************//*!
   \brief Destroys a channel
   \param[in] hChannel Channel Identifier
   \return return true
*****************************************************************************/
static inline
bool AL_IEncScheduler_DestroyChannel(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel)
{
  return pScheduler->vtable->destroyChannel(pScheduler, hChannel);
}

/*************************************************************************//*!
   \brief Asks the scheduler to process a frame encoding
   \param[in] hChannel Channel identifier
   \param[in] pEncInfo Pointer to the encoding parameters structure
   \param[in] pBufferAddrs Pointer to the input buffer structure
   \return return true if the decoding launch is successful
   false otherwise
*****************************************************************************/
static inline
bool AL_IEncScheduler_EncodeOneFrame(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TEncInfo* pEncInfo, AL_TEncRequestInfo* pReqInfo, AL_TEncPicBufAddrs* pBufferAddrs)
{
  return pScheduler->vtable->encodeOneFrame(pScheduler, hChannel, pEncInfo, pReqInfo, pBufferAddrs);
}

/*************************************************************************//*!
   \brief Give a stream buffer. It will be filled with the bitstream generated
   while encoding a frame given with the EncodeOneFrame function.
   \param[in] hChannel Channel identifier
   \param[in] pStream stream buffer given for the scheduler to fill
   \param[in] uOffset offset in the stream buffer data
   \return return true if the buffer could be pushed in the scheduler
   false otherwise
*****************************************************************************/
static inline
void AL_IEncScheduler_PutStreamBuffer(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TBuffer* pStream, AL_64U streamUserPtr, uint32_t uOffset)
{
  pScheduler->vtable->putStreamBuffer(pScheduler, hChannel, pStream, streamUserPtr, uOffset);
}

/*************************************************************************//*!
   \brief Asks for a reconstructed picture
   \param[in] hChannel Channel identifier
   \param[out] pRecPic contains the reconstructed buffer if one was available
   \return return true if a reconstructed buffer was available
   false otherwise
*****************************************************************************/
static inline
bool AL_IEncScheduler_GetRecPicture(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TRecPic* pRecPic)
{
  return pScheduler->vtable->getRecPicture(pScheduler, hChannel, pRecPic);
}

/*************************************************************************//*!
   \brief Give the reconstructed picture back to the scheduler
   \param[in] hChannel Channel identifier
   \param[in] pRecPic reconstructed buffer given back to the scheduler
   \return return true if the reconstructed buffer could be released
   false if the buffer is not known in the scheduler
*****************************************************************************/
static inline
bool AL_IEncScheduler_ReleaseRecPicture(AL_IEncScheduler* pScheduler, AL_HANDLE hChannel, AL_TRecPic* pRecPic)
{
  return pScheduler->vtable->releaseRecPicture(pScheduler, hChannel, pRecPic);
}

/*@}*/
