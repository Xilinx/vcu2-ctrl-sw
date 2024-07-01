// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include "exe_encoder/CfgParser.h"

#include <string>

extern "C"
{
#include "lib_encode/lib_encoder.h"
#include "lib_log/LoggerInterface.h"
#include "lib_log/TimerInterface.h"
}

typedef struct AL_TAllocator AL_TAllocator;
typedef struct AL_TIpCtrl AL_TIpCtrl;

/*****************************************************************************/
struct CIpDeviceParam
{
  int iDeviceType;
  int iSchedulerType;
  ConfigFile* pCfgFile;
  bool bTrackDma = false;
};

/*****************************************************************************/
static int constexpr NUM_SRC_SYNC_CHANNEL = 4;

class CIpDevice
{
public:
  CIpDevice() = default;
  ~CIpDevice();

  void Configure(CIpDeviceParam& param);
  AL_IEncScheduler* GetScheduler();
  AL_RiscV_Ctx GetCtx();
  AL_TAllocator* GetAllocator();
  AL_ITimer* GetTimer();

  CIpDevice(CIpDevice const &) = delete;
  CIpDevice & operator = (CIpDevice const &) = delete;

private:
  AL_IEncScheduler* m_pScheduler = nullptr;
  AL_TAllocator* m_pAllocator = nullptr;
  AL_RiscV_Ctx m_ctx = nullptr;
  AL_ITimer* m_pTimer = nullptr;

  void ConfigureRiscv(CIpDeviceParam& param);

};

inline AL_IEncScheduler* CIpDevice::GetScheduler(void)
{
  return m_pScheduler;
}

inline AL_RiscV_Ctx CIpDevice::GetCtx(void)
{
  return m_ctx;
}

inline AL_TAllocator* CIpDevice::GetAllocator(void)
{
  return m_pAllocator;
}

inline AL_ITimer* CIpDevice::GetTimer(void)
{
  return m_pTimer;
}

