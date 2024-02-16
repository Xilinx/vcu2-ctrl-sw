// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#include "IpDevice.h"

#include <stdexcept>
#include <memory>
#include <set>
#include <cassert>
#include <iostream>
#include <string>

#include "IpDevice.h"
#include "IpDeviceCommon.h"
#include "lib_app/console.h"
#include "lib_app/utils.h"

extern "C"
{
#include "lib_common/Allocator.h"
#include "lib_fpga/DmaAlloc.h"
#include "lib_log/LoggerInterface.h"
#include "lib_log/TimerSoftware.h"
}

using namespace std;

AL_TAllocator* createDmaAllocator(const char* deviceName)
{
  auto h = AL_DmaAlloc_Create(deviceName);

  if(h == nullptr)
    throw runtime_error("Can't find dma allocator (trying to use " + string(deviceName) + ")");
  return h;
}

extern "C"
{
#include "lib_decode/LibDecoderRiscv.h"
}

void CIpDevice::ConfigureRiscv()
{
  m_pScheduler = nullptr;
  m_ctx = AL_Riscv_Decode_CreateCtx(this->m_tSelectedDevice.c_str());

  if(!m_ctx)
    throw std::runtime_error("Failed to create context (trying to use " + this->m_tSelectedDevice + ")");

  m_pAllocator = AL_Riscv_Decode_DmaAlloc_Create(m_ctx);
  m_pTimer = nullptr;

  if(!m_pAllocator)
    throw runtime_error("Can't find dma allocator");
}

CIpDevice::~CIpDevice()
{
  if(m_pScheduler)
    AL_IDecScheduler_Destroy(m_pScheduler);

  if(m_pTimer)
    AL_ITimer_Deinit(m_pTimer);

  if(m_ctx)
    AL_Riscv_Decode_DestroyCtx(m_ctx);

  if(m_pAllocator)
    AL_Allocator_Destroy(m_pAllocator);
}

CIpDevice::CIpDevice(CIpDeviceParam const& param, AL_EDeviceType eDeviceType, std::set<std::string> tDevices) :
  m_tDevices(tDevices)
{
  (void)param;
  this->m_eDeviceType = eDeviceType;

  if(m_eDeviceType == AL_DEVICE_TYPE_EMBEDDED)
  {
    if(this->m_tDevices.size() != 1)
      throw runtime_error("Embedded device doesn't support multi devices");
    this->m_tSelectedDevice = *m_tDevices.begin();
    ConfigureRiscv();
    return;
  }

  throw runtime_error("No support for this scheduling type");
}

AL_EDeviceType CIpDevice::GetDeviceType()
{
  return this->m_eDeviceType;
}
