// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/**************************************************************************//*!
   \addtogroup Context

   AL_Ctx type is an opaque object that will embedded necessary information
   needed by AL_Encoder_CreateWithCtx and AL_Decoder_CreateWithCtx to create
   instance of encoder and decoder, respectively.
   @{
   \file
 *****************************************************************************/

#pragma once

/*************************************************************************//*!
   \brief Opaque object that will embed necessary information needed by
   AL_Encoder_CreateWithCtx and AL_Decoder_CreateWithCtx to create instances
   of encoder and decoder, respectively.
*****************************************************************************/
typedef void* AL_RiscV_Ctx;

/*@}*/
