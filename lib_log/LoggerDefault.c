// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <string.h>
#include "lib_log/LoggerDefault.h"
#include "lib_rtos/lib_rtos.h"

AL_TDefaultLogger g_DefaultLogger;

static void store(AL_TDefaultLogger* l, const char* label, AL_64U timestamp)
{
  strcpy(l->events[l->count].label, label);
  l->events[l->count].timestamp = timestamp;
  l->count++;
}

static bool hasLooped(AL_TDefaultLogger* l, AL_64U time)
{
  return l->count > 0 && l->events[l->count - 1].timestamp > time;
}

static void defaultLog(AL_ILogger* logger, char const label[MAX_LOG_LABEL_SIZE])
{
  AL_TDefaultLogger* l = (AL_TDefaultLogger*)logger;

  Rtos_GetMutex(l->mutex);

  if(l->count >= l->maxCount)
  {
    Rtos_ReleaseMutex(l->mutex);
    return;
  }

  AL_64U time = AL_ITimer_GetTime(l->timer);

  while(hasLooped(l, time))
    time += UINT32_MAX;

  store(l, label, time);

  Rtos_ReleaseMutex(l->mutex);
}

static void defaultDeinit(AL_ILogger* logger)
{
  AL_TDefaultLogger* l = (AL_TDefaultLogger*)logger;
  Rtos_DeleteMutex(l->mutex);
}

static AL_ILoggerVtable const DefaultLoggerVtable =
{
  defaultLog,
  defaultDeinit,
};

AL_ILogger* AL_DefaultLogger_Init(AL_TDefaultLogger* logger, AL_ITimer* timer, LogEvent* buffer, int maxCount)
{
  logger->mutex = Rtos_CreateMutex();

  if(NULL == logger->mutex)
  {
    Rtos_Free(logger);
    return NULL;
  }

  logger->vtable = &DefaultLoggerVtable;
  logger->timer = timer;
  logger->count = 0;
  logger->events = buffer;
  logger->maxCount = maxCount;

  return (AL_ILogger*)logger;
}
