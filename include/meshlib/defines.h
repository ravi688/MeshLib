
#pragma once

#include <meshlib/api_defines.h>

#include <stdint.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

#if !defined(MESHLIB_RELEASE) && !defined(MESHLIB_DEBUG)
#	warning "None of MESHLIB_RELEASE && MESHLIB_DEBUG is defined; using MESHLIB_DEBUG"
#	define MESHLIB_DEBUG
#endif
