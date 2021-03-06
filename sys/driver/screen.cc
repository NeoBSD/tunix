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

#include "screen.h"

#include "sys/kmem.h"
#include "sys/stdint.h"

#include "machine/ports.h"

namespace
{
constexpr auto VIDEO_ADDRESS = 0xb8000;
constexpr auto MAX_ROWS      = 25;
constexpr auto MAX_COLS      = 80;

/* Screen i/o ports */
constexpr auto REG_SCREEN_CTRL = 0x3d4;
constexpr auto REG_SCREEN_DATA = 0x3d5;

[[nodiscard]] int get_offset(int col, int row)
{
  return 2 * (row * MAX_COLS + col);
}

[[nodiscard]] int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }

[[nodiscard]] int get_offset_col(int offset)
{
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}

[[nodiscard]] int get_cursor_offset()
{
  /* Use the VGA ports to get the current cursor position
   * 1. Ask for high byte of the cursor offset (data 14)
   * 2. Ask for low byte (data 15)
   */
  port_byte_out(REG_SCREEN_CTRL, 14);
  int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
  port_byte_out(REG_SCREEN_CTRL, 15);
  offset += port_byte_in(REG_SCREEN_DATA);
  return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset)
{
  /* Similar to get_cursor_offset, but instead of reading we write data */
  offset /= 2;
  port_byte_out(REG_SCREEN_CTRL, 14);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}

}  // namespace

/**
 * Innermost print function for our kernel, directly accesses the video memory
 *
 * If 'col' and 'row' are negative, we will print at current cursor location
 * If 'attr' is zero it will use 'white on black' as default
 * Returns the offset of the next character
 * Sets the video cursor to the returned offset
 */
int print_char(char c, int col, int row, char attr)
{
  auto* vidmem = (uint8_t*)VIDEO_ADDRESS;
  if (attr == 0) { attr = WHITE_ON_BLACK; }

  /* Error control: print a red 'E' if the coords aren't right */
  if (col >= MAX_COLS || row >= MAX_ROWS)
  {
    vidmem[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
    vidmem[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
    return get_offset(col, row);
  }

  int offset;
  if (col >= 0 && row >= 0) { offset = get_offset(col, row); }
  else
  {
    offset = get_cursor_offset();
  }

  if (c == '\n')
  {
    row    = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  }
  else if (c == 0x08)
  { /* Backspace */
    vidmem[offset]     = ' ';
    vidmem[offset + 1] = attr;
  }
  else
  {
    vidmem[offset]     = c;
    vidmem[offset + 1] = attr;
    offset += 2;
  }

  /* Check if the offset is over screen size and scroll */
  if (offset >= MAX_ROWS * MAX_COLS * 2)
  {
    int i;
    for (i = 1; i < MAX_ROWS; i++)
    {
      kmemcpy((uint8_t*)(get_offset(0, i) + VIDEO_ADDRESS),
              (uint8_t*)(get_offset(0, i - 1) + VIDEO_ADDRESS), MAX_COLS * 2);
    }

    /* Blank last line */
    char* last_line
        = (char*)(get_offset(0, MAX_ROWS - 1) + (uint8_t*)VIDEO_ADDRESS);
    for (i = 0; i < MAX_COLS * 2; i++) { last_line[i] = 0; }

    offset -= 2 * MAX_COLS;
  }

  set_cursor_offset(offset);
  return offset;
}

void kprint_at(char const* message, int col, int row)
{
  /* Set cursor if col/row are negative */
  int offset;
  if (col >= 0 && row >= 0) { offset = get_offset(col, row); }
  else
  {
    offset = get_cursor_offset();
    row    = get_offset_row(offset);
    col    = get_offset_col(offset);
  }

  /* Loop through message and print it */
  int i = 0;
  while (message[i] != 0)
  {
    offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
    /* Compute row/col for next iteration */
    row = get_offset_row(offset);
    col = get_offset_col(offset);
  }
}

void kprint(char const* message) { kprint_at(message, -1, -1); }

void kprint_backspace()
{
  if (auto const off = get_cursor_offset(); get_offset_col(off) > 2)
  {
    int newOffset = off - 2;
    int row       = get_offset_row(newOffset);
    int col       = get_offset_col(newOffset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
  }
}

void clear_screen()
{
  auto const screen_size = MAX_COLS * MAX_ROWS;
  auto* const screen     = reinterpret_cast<uint8_t*>(VIDEO_ADDRESS);
  for (auto i = 0; i < screen_size; i++)
  {
    screen[i * 2]     = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_offset(0, 0));
}
