// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "lib_rtos/types.h"
#include "lib_log/LoggerInterface.h"

static uint8_t const PERF_VAL_X = 255;
static uint8_t const PERF_VAL_Z = 254;

typedef struct
{
  AL_ILogger* pLogger;
  bool bEnabled;
}AL_TLoggerCtx;

#define EventLogV(LoggerCtx, Signal, Value)
#define EventLog(LoggerCtx, Signal)
