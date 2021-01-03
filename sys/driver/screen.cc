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
#include "ports.h"

/* Declaration of private functions */
void set_cursor_offset(int offset);
int get_cursor_offset();
int print_char(char c, int col, int row, char attr);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void kprint_at(char const* message, int col, int row)
{
  /* Set cursor if col/row are negative */
  int offset;
  if (col >= 0 && row >= 0)
    offset = get_offset(col, row);
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

/**********************************************************
 * Private kernel functions                               *
 **********************************************************/

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
  unsigned char* vidmem = VIDEO_ADDRESS;
  if (!attr) attr = WHITE_ON_BLACK;

  /* Error control: print a red 'E' if the coords aren't right */
  if (col >= MAX_COLS || row >= MAX_ROWS)
  {
    vidmem[2 * (MAX_COLS) * (MAX_ROWS)-2] = 'E';
    vidmem[2 * (MAX_COLS) * (MAX_ROWS)-1] = RED_ON_WHITE;
    return get_offset(col, row);
  }

  int offset;
  if (col >= 0 && row >= 0)
    offset = get_offset(col, row);
  else
    offset = get_cursor_offset();

  if (c == '\n')
  {
    row    = get_offset_row(offset);
    offset = get_offset(0, row + 1);
  }
  else
  {
    vidmem[offset]     = c;
    vidmem[offset + 1] = attr;
    offset += 2;
  }
  set_cursor_offset(offset);
  return offset;
}

int get_cursor_offset()
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
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
  port_byte_out(REG_SCREEN_CTRL, 15);
  port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
  int screen_size = MAX_COLS * MAX_ROWS;
  int i;
  unsigned char* screen = VIDEO_ADDRESS;

  for (i = 0; i < screen_size; i++)
  {
    screen[i * 2]     = ' ';
    screen[i * 2 + 1] = WHITE_ON_BLACK;
  }
  set_cursor_offset(get_offset(0, 0));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset)
{
  return (offset - (get_offset_row(offset) * 2 * MAX_COLS)) / 2;
}
