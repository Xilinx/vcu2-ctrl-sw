// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/**************************************************************************//*!
   \addtogroup Decoder_API
   @{
   \file
 *****************************************************************************/
#pragma once

#include "lib_common/Allocator.h"
#include "lib_common/Context.h"
/*************************************************************************//*!
    \brief Opens the RiscV decoding driver and creates an AL_RiscV_Ctx that will
    be used to create a decoder.
    \param[in] deviceName The name of the RiscV device used for decoding.
*****************************************************************************/
AL_RiscV_Ctx AL_Riscv_Decode_CreateCtx(const char* deviceName);

/*************************************************************************//*!
    \brief Destroys the context previously created and closes the driver.
    \param[in] ctx The AL_RiscV_Ctx that contains the infos about the riscv driver.
*****************************************************************************/
void AL_Riscv_Decode_DestroyCtx(AL_RiscV_Ctx ctx);

/*************************************************************************//*!
    \brief Creates an allocator supporting dma allocations with the RiscV
    driver. Dma buffers are required for all the buffers used by the hardware ip.
    \param[in] ctx The AL_RiscV_Ctx that contains the infos about the riscv driver.
*****************************************************************************/
AL_TAllocator* AL_Riscv_Decode_DmaAlloc_Create(AL_RiscV_Ctx ctx);

/*@}*/
