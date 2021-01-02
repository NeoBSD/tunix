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

#include "kernel/kernel.h"

#include "driver/ports.h"

void kernel_main() {
  /* Screen cursor position: ask VGA control register (0x3d4) for bytes
   * 14 = high byte of cursor and 15 = low byte of cursor. */
  /* Requesting byte 14: high byte of cursor pos */
  port_byte_out(0x3d4, 14);

  /* Data is returned in VGA data register (0x3d5) */
  auto position = static_cast<int>(port_byte_in(0x3d5));
  position = position << 8; /* high byte */

  /* requesting low byte */
  port_byte_out(0x3d4, 15);
  position += port_byte_in(0x3d5);

  /* VGA 'cells' consist of the character and its control data
   * e.g. 'white on black background', 'red text on white bg', etc */
  auto const offsetFromVGA = position * 2;

  /* Now you can examine both variables using gdb, since we still
   * don't know how to print strings on screen. Run 'make debug' and
   * on the gdb console:
   * breakpoint kernel.c:21
   * continue
   * print position
   * print offsetFromVGA
   */

  // Let's write on the current cursor position, we already know how
  // to do that
  auto *vga = reinterpret_cast<char *>(0xb8000);
  vga[offsetFromVGA] = 'T';
  /* White text on black background */
  vga[offsetFromVGA + 1] = 0x0f;
}
