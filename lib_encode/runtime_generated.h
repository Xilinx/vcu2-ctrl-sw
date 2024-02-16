// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

#pragma once

#include <stdint.h>
#include "lib_common/FourCC.h"

#define IMPLEMENT_SIZE_TOR_TYPE(type, type_san) \
static int get_size_##type_san(void) \
{ \
  return sizeof(type); \
}

#define IMPLEMENT_MARSHALL_TOR_TYPE(type, type_san) \
static void marshall_##type_san(type *in, void (*write_cb)(int, void *, void *), void *arg) \
{ \
  write_cb(sizeof(*in), in, arg); \
}

#define IMPLEMENT_UNMARSHALL_TOR_TYPE(type, type_san) \
static void unmarshall_##type_san(type *in, void (*read_cb)(int, void *, void *), void *arg) \
{ \
  read_cb(sizeof(*in), in, arg); \
}

#define IMPLEMENT_ALL_FOR_TYPE(type, type_san) \
IMPLEMENT_SIZE_TOR_TYPE(type, type_san) \
IMPLEMENT_MARSHALL_TOR_TYPE(type, type_san) \
IMPLEMENT_UNMARSHALL_TOR_TYPE(type, type_san)

IMPLEMENT_ALL_FOR_TYPE(uint8_t, uint8_t)
IMPLEMENT_ALL_FOR_TYPE(int8_t, int8_t)
IMPLEMENT_ALL_FOR_TYPE(uint16_t, uint16_t)
IMPLEMENT_ALL_FOR_TYPE(int16_t, int16_t)
IMPLEMENT_ALL_FOR_TYPE(uint32_t, uint32_t)
IMPLEMENT_ALL_FOR_TYPE(int32_t, int32_t)
IMPLEMENT_ALL_FOR_TYPE(uint64_t, uint64_t)
IMPLEMENT_ALL_FOR_TYPE(int64_t, int64_t)
IMPLEMENT_ALL_FOR_TYPE(int, int)
IMPLEMENT_ALL_FOR_TYPE(long, long)
IMPLEMENT_ALL_FOR_TYPE(unsigned long, unsigned_long)

IMPLEMENT_ALL_FOR_TYPE(_Bool, _Bool)
IMPLEMENT_ALL_FOR_TYPE(TFourCC, TFourCC)

int get_size_AL_HANDLE(void)
{
  return sizeof(uint64_t);
}
void marshall_AL_HANDLE(AL_HANDLE *in, void (*write_cb)(int, void *, void *), void *arg)
{
  uint64_t res = (uint64_t)(uintptr_t)*in;
  write_cb(sizeof(res), &res, arg);
}
void unmarshall_AL_HANDLE(AL_HANDLE *in, void (*read_cb)(int, void *, void *), void *arg)
{
  uint64_t res;
  read_cb(sizeof(res), &res, arg);
  *in = (AL_HANDLE)(uintptr_t)res;
}

int get_size_AL_PADDR(void)
{
  return sizeof(uint64_t);
}
void marshall_AL_PADDR(AL_PADDR *in, void (*write_cb)(int, void *, void *), void *arg)
{
  uint64_t res = *in;
  write_cb(sizeof(res), &res, arg);
}
void unmarshall_AL_PADDR(AL_PADDR *in, void (*read_cb)(int, void *, void *), void *arg)
{
  uint64_t res;
  read_cb(sizeof(res), &res, arg);
  *in = res;
}

int get_size_AL_VADDR(void)
{
  return sizeof(uint64_t);
}
void marshall_AL_VADDR(AL_VADDR *in, void (*write_cb)(int, void *, void *), void *arg)
{
  uint64_t res = (uint64_t)(uintptr_t)*in;
  write_cb(sizeof(res), &res, arg);
}
void unmarshall_AL_VADDR(AL_VADDR *in, void (*read_cb)(int, void *, void *), void *arg)
{
  uint64_t res;
  read_cb(sizeof(res), &res, arg);
  *in = (AL_VADDR)(uintptr_t)res;
}

int get_size_AL_64U(void)
{
  return sizeof(uint64_t);
}
void marshall_AL_64U(AL_64U *in, void (*write_cb)(int, void *, void *), void *arg)
{
  uint64_t res = (uint64_t)(uintptr_t)*in;
  write_cb(sizeof(res), &res, arg);
}
void unmarshall_AL_64U(AL_64U *in, void (*read_cb)(int, void *, void *), void *arg)
{
  uint64_t res;
  read_cb(sizeof(res), &res, arg);
  *in = (AL_64U)(uintptr_t)res;
}
