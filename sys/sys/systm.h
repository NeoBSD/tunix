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

#ifndef TNX_SYS_SYSTM_H
#define TNX_SYS_SYSTM_H

#include "sys/cdefs.h"
#include "sys/stdarg.h"
#include "sys/stddef.h"
#include "sys/stdint.h"

TNX_BEGIN_EXTERN_C

/**
 * @brief Output a character to a custom device like UART, used by the printf()
 * function This function is declared here only.
 *
 * @details You have to write your custom implementation somewhere .
 * @param character Character to output
 */
void printf_internal_putchar(char character);

/**
 * @brief printf implementation
 *
 * @param format A string that specifies the format of the output
 * @return The number of characters that are written into the array, not
 * counting the terminating null character
 */
int printf(char const* format, ...) TNX_PRINTF_FUNC(1, 2);

/**
 * @brief sprintf implementation
 *
 * @details Due to security reasons you should consider using (v)snprintf
 * instead.
 * @param buffer A pointer to the buffer where to store the formatted string.
 * MUST be big enough to store the output!
 * @param format A string that specifies the format of the output
 * @return The number of characters that are WRITTEN into the buffer, not
 * counting the terminating null character
 */
int sprintf(char* buffer, char const* format, ...) TNX_PRINTF_FUNC(2, 3);

/**
 * @brief snprintf implementation
 *
 * @param buf A pointer to the buffer where to store the formatted string
 * @param num The maximum number of characters to store in the buffer,
 * including a terminating null character.
 * @param fmt A string that specifies the format of the output
 * @return The number of characters that COULD have been written into the
 * buffer, not counting the terminating null character. A value equal or larger
 * than num indicates truncation. Only when the returned value is non-negative
 * and less than num, the string has been completely written.
 */
int snprintf(char* buf, size_t num, char const* fmt, ...) TNX_PRINTF_FUNC(3, 4);

/**
 * @brief vsnprintf implementation
 *
 * @param buf A pointer to the buffer where to store the formatted string
 * @param num The maximum number of characters to store in the buffer,
 * including a terminating null character.
 * @param fmt A string that specifies the format of the output
 * @param va A value identifying a variable arguments list
 * @return The number of characters that COULD have been written into the
 * buffer, not counting the terminating null character. A value equal or larger
 * than num indicates truncation. Only when the returned value is non-negative
 * and less than num, the string has been completely written.
 */
int vsnprintf(char* buf, size_t num, char const* fmt, va_list va);

/**
 * @brief vprintf implementation
 *
 * @param format A string that specifies the format of the output
 * @param va A value identifying a variable arguments list
 * @return The number of characters that are WRITTEN into the buffer, not
 * counting the terminating null character
 */
int vprintf(char const* format, va_list va);

/**
 * @brief printf with output callback function
 *
 * @param out An output function which takes one character and an argument
 * pointer.
 * @param arg An argument pointer for user data passed to output function
 * @param format A string that specifies the format of the output
 * @return The number of characters that are sent to the output function, not
 * counting the terminating null character
 */
int fctprintf(void (*out)(char character, void* arg), void* arg,
              char const* format, ...) TNX_PRINTF_FUNC(3, 4);

/**
 * @brief Kernel mode assertion macro.
 */
#if defined(TUNIX_OPT_KERNEL_ASSERT)
#define TNX_KASSERT(pred)                                                      \
  do {                                                                         \
    if (!(pred))                                                               \
    { printf("%s:%d: %s - %s\n", __FILE__, __LINE__, __func__, #pred); }       \
  } while (0);
#else
#define TNX_KASSERT(pred) ((void)(pred))
#endif

TNX_END_EXTERN_C

#endif  // TNX_SYS_SYSTM_H
