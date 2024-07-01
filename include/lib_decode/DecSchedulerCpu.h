// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/**************************************************************************//*!
   \addtogroup Decoder_API
   @{
   \file
 *****************************************************************************/
#pragma once

typedef struct AL_IDecScheduler AL_IDecScheduler;

#include "lib_common/Allocator.h"
#include "lib_ip_ctrl/IpCtrl.h"
#include "lib_log/LoggerInterface.h"

/*************************************************************************//*!
    \brief Interfaces with a scheduler that runs on the same process.
    Its main usage is to interface with the scheduler if everything is running in the same process
   \param[in] pIpCtrl The interface the scheduler will use to read and write the IP registers
   \param[in] pDmaAllocator The Direct Memory Access allocator that will be used to create work buffers and to map some of the buffer that are sent to the scheduler.
   \param[in] pLogger An optional logger
   \return Pointer to the decoder scheduler interface
*****************************************************************************/
AL_IDecScheduler* AL_DecSchedulerCpu_Create(AL_TIpCtrl* pIpCtrl, AL_TAllocator* pDmaAllocator, AL_ILogger* pLogger);

/*@}*/
