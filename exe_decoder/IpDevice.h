// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once
#include <functional>
#include <set>
#include <string>
#include "lib_app/utils.h"
#include "IpDeviceCommon.h"

extern "C"
{
#include "lib_decode/lib_decode.h"
#include "lib_common_dec/DecChanParam.h"
}

typedef struct AL_IDecScheduler AL_IDecScheduler;

/*****************************************************************************/
class CIpDevice : public I_IpDevice
{
public:
  CIpDevice(CIpDeviceParam const& param, AL_EDeviceType eDeviceType, std::set<std::string> tDevices);
  ~CIpDevice();

  AL_EDeviceType GetDeviceType();
  void* GetScheduler() override;
  AL_RiscV_Ctx GetCtx();
  AL_TAllocator* GetAllocator() override;
  AL_ITimer* GetTimer() override;

  CIpDevice(CIpDevice const &) = delete;
  CIpDevice & operator = (CIpDevice const &) = delete;

private:
  std::set<std::string> const m_tDevices;
  std::string m_tSelectedDevice;
  AL_EDeviceType m_eDeviceType;
  AL_IDecScheduler* m_pScheduler = nullptr;
  AL_TAllocator* m_pAllocator = nullptr;
  AL_RiscV_Ctx m_ctx = nullptr;
  AL_ITimer* m_pTimer = nullptr;

  void ConfigureRiscv();
};

inline void* CIpDevice::GetScheduler()
{
  return m_pScheduler;
}

inline AL_RiscV_Ctx CIpDevice::GetCtx()
{
  return m_ctx;
}

inline AL_TAllocator* CIpDevice::GetAllocator()
{
  return m_pAllocator;
}

inline AL_ITimer* CIpDevice::GetTimer()
{
  return m_pTimer;
}

