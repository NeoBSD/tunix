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

#ifndef TNX_SYS_STRING_H
#define TNX_SYS_STRING_H

#include "sys/cdefs.h"

TNX_BEGIN_EXTERN_C

/**
 * @brief Returns the length of the given byte string, that is, the number of
 * characters in a character array whose first element is pointed to by
 * \param str up to and not including the first null character.
 *
 * @details The behavior is undefined if there is no null character in the
 * character array pointed to by str.
 */
TNX_NODISCARD int strlen(char const* str);

/**
 * @brief Appends a copy of the character string pointed to by \param src to the
 * end of the character string pointed to by \param dest. The character src[0]
 * replaces the null terminator at the end of dest. The resulting byte string is
 * null-terminated.
 *
 * @details The behavior is undefined if the destination array is not large
 * enough for the contents of both \param src and \param dest and the
 * terminating null character. The behavior is undefined if the strings overlap.
 *
 */
char* strcat(char* dest, char const* src);

/**
 * @brief Compares two null-terminated byte strings lexicographically.
 *
 * @details The sign of the result is the sign of the difference between the
 * values of the first pair of characters (both interpreted as unsigned char)
 * that differ in the strings being compared. The behavior is undefined if
 * \param lhs or \param rhs are not pointers to null-terminated strings.
 */
TNX_NODISCARD int strcmp(char const* lhs, char const* rhs);

/**
 * @brief Returns true, if the given string \param str begins
 * the the prefix \param pre.
 */
TNX_NODISCARD bool starts_with(char const* str, char const* pre);

/**
 * @brief
 */
void int_to_ascii(int n, char* str);

/**
 * @brief
 */
void hex_to_ascii(int n, char* str);

/**
 * @brief
 */
void reverse(char* s);

/**
 * @brief
 */
void backspace(char* s);

/**
 * @brief
 */
void append(char* s, char n);

TNX_END_EXTERN_C

#endif
