/**
 * Copyright (c) 2021, Tobias Hienzsch
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#ifndef TNX_SYS_STDINT_H
#define TNX_SYS_STDINT_H

#include "sys/cdefs.h"

TNX_BEGIN_EXTERN_C

#ifndef __UINTPTR_TYPE__
#error Your compiler does not provide fixed width type macros.
#endif

typedef __INT8_TYPE__ int8_t;
typedef __INT16_TYPE__ int16_t;
typedef __INT32_TYPE__ int32_t;
typedef __INT64_TYPE__ int64_t;

typedef __UINT8_TYPE__ uint8_t;
typedef __UINT16_TYPE__ uint16_t;
typedef __UINT32_TYPE__ uint32_t;
typedef __UINT64_TYPE__ uint64_t;

typedef __INTPTR_TYPE__ intptr_t;
typedef __UINTPTR_TYPE__ uintptr_t;
typedef __INTMAX_TYPE__ intmax_t;
typedef __UINTMAX_TYPE__ uintmax_t;

TNX_STATIC_ASSERT(sizeof(int8_t) == 1);
TNX_STATIC_ASSERT(sizeof(uint8_t) == 1);

TNX_STATIC_ASSERT(sizeof(int16_t) == 2);
TNX_STATIC_ASSERT(sizeof(uint16_t) == 2);

TNX_STATIC_ASSERT(sizeof(int32_t) == 4);
TNX_STATIC_ASSERT(sizeof(uint32_t) == 4);

TNX_STATIC_ASSERT(sizeof(int64_t) == 8);
TNX_STATIC_ASSERT(sizeof(uint64_t) == 8);

TNX_STATIC_ASSERT(sizeof(intmax_t) == 8);
TNX_STATIC_ASSERT(sizeof(uintmax_t) == 8);

TNX_STATIC_ASSERT(sizeof(intptr_t) == sizeof(nullptr));
TNX_STATIC_ASSERT(sizeof(uintptr_t) == sizeof(nullptr));

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

TNX_END_EXTERN_C

#endif
