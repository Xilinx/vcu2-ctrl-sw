// SPDX-FileCopyrightText: © 2024 Allegro DVT <github-ip@allegrodvt.com>
// SPDX-License-Identifier: MIT

/**************************************************************************//*!
   \addtogroup lib_rtos
   @{
   \file
******************************************************************************/
#pragma once

#include <stddef.h> // for NULL and size_t
#include <stdint.h>
#include <stdbool.h>

#define AL_INTROSPECT(...)

#ifdef __GNUC__
#include <stdalign.h>

#define _CRT_SECURE_NO_WARNINGS
#define AL_DEPRECATED(msg) __attribute__((deprecated(msg)))
#define __AL_ALIGNED__(x) __attribute__((__aligned__(x)))

#ifndef __cplusplus
#define static_assert _Static_assert
#endif

#else // _MSC_VER

#define __attribute__(x)
#define __AL_ALIGNED__(x) __declspec(align(x))
#define AL_DEPRECATED(msg) __declspec(deprecated(msg))

#ifndef __cplusplus
#define static_assert(assertion, ...) _STATIC_ASSERT(assertion)
#endif

#endif

#define AL_DEPRECATED_ENUM_VALUE(eType, name, val, msg) AL_DEPRECATED(msg) static const eType name = val

typedef uint64_t __AL_ALIGNED__ (8) AL_64U; // Ensure that 64bits has same alignment on all platforms (especially 32bits platforms)
typedef int64_t __AL_ALIGNED__ (8) AL_64S; // Ensure that 64bits has same alignment on all platforms (especially 32bits platforms)
typedef uint8_t* AL_VADDR; /*!< Virtual address. byte pointer */

typedef uint64_t AL_PADDR; /*!< Physical address, 64-bit address registers */

typedef AL_64U AL_PTR64;
typedef void* AL_HANDLE;
typedef void const* AL_CONST_HANDLE;

/*@}*/