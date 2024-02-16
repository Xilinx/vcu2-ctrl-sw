// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/**************************************************************************//*!
   \addtogroup Encoder_API
   @{
   \file
 *****************************************************************************/
#pragma once

typedef struct AL_IEncScheduler AL_IEncScheduler;

#include "lib_common/Allocator.h"
#include "lib_ip_ctrl/IpCtrl.h"

/*************************************************************************//*!
    \brief Interfaces with a scheduler that runs on the same process.
    Its main usage is to interface with the scheduler if everything is running in the same process
   \param[in] pIpCtrl The interface the scheduler will use to read and write the IP registers
   \param[in] pDmaAllocator a dma allocator that will be used to create work buffers and to map some of the buffer that are sent to the scheduler.
*****************************************************************************/
AL_IEncScheduler* AL_SchedulerCpu_Create(AL_TIpCtrl* pIpCtrl, AL_TAllocator* pDmaAllocator);

/*@}*/
