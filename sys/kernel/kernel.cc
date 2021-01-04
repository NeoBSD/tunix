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
#include "sys/sysm.h"

#include "machine/isr.h"

#include "driver/screen.h"

void kernel_main()
{
  isr_install();
  irq_install();

  clear_screen();
  printf("Tunix v0.1.0\n");
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
    auto const size = uint32_t {1000};
    auto phys_addr  = uint32_t {0};
    auto const page = kmalloc(size, 1, &phys_addr);
    printf("page: %X, size: %u, physical: %X\n", page, size, phys_addr);
    kprint("> ");
    return;
  }

  printf("you said: %s\n", input);
  kprint("> ");
}
