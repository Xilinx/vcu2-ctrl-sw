// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include <string.h>
#include "lib_log/LoggerDefault.h"
#include "lib_rtos/lib_rtos.h"

AL_TDefaultLogger g_DefaultLogger;

static void store(AL_TDefaultLogger* logger, const char* label, AL_64U timestamp)
{
  int count = logger->count;
  strcpy(logger->events[count].label, label);
  logger->events[count].timestamp = timestamp;
  logger->count++;
}

static bool hasLooped(AL_TDefaultLogger* logger, AL_64U time)
{
  int count = logger->count;
  return (count > 0) && (logger->events[count - 1].timestamp > time);
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
  &defaultLog,
  &defaultDeinit,
};

AL_ILogger* AL_DefaultLogger_Init(AL_TDefaultLogger* logger, AL_ITimer* timer, LogEvent* events, int maxCount)
{
  if(NULL == logger)
    return NULL;

  if(NULL == timer)
    return NULL;

  if(maxCount < 0)
    return NULL;

  if((maxCount > 0) && (NULL == events))
    return NULL;

  logger->mutex = Rtos_CreateMutex();

  if(NULL == logger->mutex)
    return NULL;

  logger->vtable = &DefaultLoggerVtable;
  logger->timer = timer;
  logger->count = 0;
  logger->events = events;
  logger->maxCount = maxCount;

  return (AL_ILogger*)logger;
}

AL_TDefaultLogger* AL_DefaultLogger_Get(void)
{
  return &g_DefaultLogger;
}
