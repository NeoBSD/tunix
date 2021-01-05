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

#ifndef TNX_SYS_CDEFS_H
#define TNX_SYS_CDEFS_H

/**
 * @brief Sometimes we want to keep parameters to a function for later use and
 * this is a solution to avoid the 'unused parameter' compiler warning
 */
#define TNX_UNUSED(x) (void)(x)

/**
 * @brief Convert macro argument to string literal.
 */
#define TNX_STRINGIFY(x) TNX_STRINGIFY_IMPL(x)
#define TNX_STRINGIFY_IMPL(x) #x

/**
 * @brief Check if C++ is enabled. i.e. Is the current translation unit a .cc
 * file
 */
#if defined(__cplusplus)
#define TNX_CPP
#endif

/**
 * @brief All headers should use this. Forces C linkage.
 */
#if defined(TNX_CPP)
#define TNX_BEGIN_EXTERN_C                                                     \
  extern "C"                                                                   \
  {
#define TNX_END_EXTERN_C }
#else
#define TNX_BEGIN_EXTERN_C
#define TNX_END_EXTERN_C
#endif

/**
 * @brief Build-time assertion. Doesn't generate any code. The error message on
 * failure is less than ideal, but you can't have everything.
 */
#if defined(TNX_CPP)
#define TNX_STATIC_ASSERT(x) static_assert((x))
#else
#define TNX_STATIC_ASSERT(x)                                                   \
  ((void)sizeof(struct { unsigned : ((x) ? 1 : -1); }))
#endif

/**
 * @brief Warn if a return value is not used.
 */
#if defined(TNX_CPP)
#define TNX_NODISCARD [[nodiscard]]
#else
#define TNX_NODISCARD __attribute__((warn_unused_result))
#endif

/**
 * @brief Disable padding in structures.
 */
#define TNX_PACKED __attribute__((packed))

/**
 * @brief Code must be emitted for the function even if it appears that the
 * function is not referenced.
 */
#define TNX_USED __attribute__((used))

/**
 * @brief Tell the compiler how to check printf formats.
 */
#if defined(__GNUC__)
#define TNX_PRINTF_FUNC(a, b) __attribute__((__format__(__printf__, a, b)))
#else
#define TNX_PRINTF_FUNC(a, b)
#endif

#endif
