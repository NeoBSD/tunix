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

#include "string.h"
#include "sys/stdint.h"

/**
 * K&R implementation
 */
void int_to_ascii(int n, char* str)
{
  int i, sign;
  if ((sign = n) < 0) n = -n;
  i = 0;
  do {
    str[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) str[i++] = '-';
  str[i] = '\0';

  reverse(str);
}

void hex_to_ascii(int n, char* str)
{
  append(str, '0');
  append(str, 'x');
  char zeros = 0;

  int32_t tmp;
  int i;
  for (i = 28; i > 0; i -= 4)
  {
    tmp = (n >> i) & 0xF;
    if (tmp == 0 && zeros == 0) continue;
    zeros = 1;
    if (tmp > 0xA)
      append(str, tmp - 0xA + 'a');
    else
      append(str, tmp + '0');
  }

  tmp = n & 0xF;
  if (tmp >= 0xA)
    append(str, tmp - 0xA + 'a');
  else
    append(str, tmp + '0');
}

/* K&R */
void reverse(char* s)
{
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
  {
    c    = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

/* K&R */
int strlen(char const* s)
{
  int i = 0;
  while (s[i] != '\0') ++i;
  return i;
}

void append(char* s, char n)
{
  int len    = strlen(s);
  s[len]     = n;
  s[len + 1] = '\0';
}

void backspace(char s[])
{
  int len    = strlen(s);
  s[len - 1] = '\0';
}

/* K&R
 * Returns <0 if s1<s2, 0 if s1==s2, >0 if s1>s2 */
int strcmp(char const* s1, char const* s2)
{
  int i;
  for (i = 0; s1[i] == s2[i]; i++)
  {
    if (s1[i] == '\0') return 0;
  }
  return s1[i] - s2[i];
}
