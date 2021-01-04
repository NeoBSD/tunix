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

#include "keyboard.h"

#include "screen.h"

#include "sys/function.h"
#include "sys/kernel.h"
#include "sys/stdint.h"
#include "sys/string.h"

#include "arch/x86/include/isr.h"
#include "arch/x86/include/ports.h"

namespace
{
constexpr auto SC_MAX    = 57;
constexpr auto BACKSPACE = uint8_t {0x0E};
constexpr auto ENTER     = uint8_t {0x1C};

constexpr char const* sc_name[] = {
    "ERROR",     "Esc",      "1", "2", "3", "4",      "5",
    "6",         "7",        "8", "9", "0", "-",      "=",
    "Backspace", "Tab",      "Q", "W", "E", "R",      "T",
    "Y",         "U",        "I", "O", "P", "[",      "]",
    "Enter",     "Lctrl",    "A", "S", "D", "F",      "G",
    "H",         "J",        "K", "L", ";", "'",      "`",
    "LShift",    "\\",       "Z", "X", "C", "V",      "B",
    "N",         "M",        ",", ".", "/", "RShift", "Keypad *",
    "LAlt",      "Spacebar",
};

constexpr char const sc_ascii[] = {
    '?', '?', '1', '2', '3', '4', '5', '6', '7', '8', '9',  '0', '-', '=',  '?',
    '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',  '[', ']', '?',  '?',
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z',
    'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '?', '?',  '?', ' ',
};

char key_buffer[256];
}  // namespace

static void keyboard_callback(registers_t* regs)
{
  TNX_UNUSED(regs);
  TNX_UNUSED(sc_name);

  /* The PIC leaves us the scancode in port 0x60 */
  uint8_t scancode = port_byte_in(0x60);
  if (scancode > SC_MAX) { return; }

  if (scancode == BACKSPACE)
  {
    backspace(key_buffer);
    kprint_backspace();
    return;
  }

  if (scancode == ENTER)
  {
    kprint("\n");
    user_input(key_buffer);
    key_buffer[0] = '\0';
    return;
  }

  auto const letter = sc_ascii[scancode];
  char const str[2] = {letter, '\0'};
  append(key_buffer, letter);
  kprint(str);
}

void init_keyboard() { register_interrupt_handler(IRQ1, keyboard_callback); }
