// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "lib_log/TimerSoftware.h"
#include "lib_rtos/lib_rtos.h"

static AL_64U getSoftwareTime(AL_ITimer* timer)
{
  (void)timer;
  return Rtos_GetTime();
}

static void deinit(AL_ITimer* timer)
{
  (void)timer;
}

static const AL_ITimerVtable SoftwareTimerVtable =
{
  getSoftwareTime,
  deinit,
};

AL_ITimer* AL_SoftwareTimerInit(AL_SoftwareTimer* timer)
{
  timer->vtable = &SoftwareTimerVtable;
  return (AL_ITimer*)timer;
}

AL_SoftwareTimer g_SoftwareTimer;
