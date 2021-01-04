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

#include "sys/kernel.h"
#include "sys/kernel_mem.h"
#include "sys/null.h"
#include "sys/stdint.h"
#include "sys/string.h"

#include "machine/isr.h"

#include "driver/screen.h"

void kernel_main()
{
  isr_install();
  irq_install();

  clear_screen();
  kprint("Tunix v0.1.0\n");
  kprint("END to halt the CPU\n");
  kprint("PAGE to request a kmalloc()\n");
  kprint("\n> ");
}

void user_input(char const* input)
{
  if (strcmp(input, "END") == 0)
  {
    kprint("Stopping the CPU. Bye!\n");
    __asm__ __volatile__("hlt");
  }

  if (strcmp(input, "PAGE") == 0)
  {
    /* Lesson 22: Code to test kmalloc, the rest is unchanged */
    uint32_t const size = 1000;
    char size_str[16]   = "";
    int_to_ascii(size, &size_str[0]);
    uint32_t phys_addr = 0;
    uint32_t page      = kmalloc(size, 1, &phys_addr);
    char page_str[16]  = "";
    hex_to_ascii(page, page_str);
    char phys_str[16] = "";
    hex_to_ascii(phys_addr, phys_str);
    kprint("page: ");
    kprint(page_str);
    kprint(", size: ");
    kprint(size_str);
    kprint(", physical address: ");
    kprint(phys_str);
    kprint("\n> ");
    return;
  }

  kprint("You said: ");
  kprint(input);
  kprint("\n> ");
}
