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

#include "sys/copyright.h"
#include "sys/kernel_mem.h"
#include "sys/param.h"
#include "sys/stdint.h"
#include "sys/string.h"
#include "sys/systm.h"

#include "machine/isr.h"

#include "driver/screen.h"

void kernel_main()
{
  isr_install();
  irq_install();

  clear_screen();
  printf("Tunix 0.1.0\n%s\n", TUNIX_COPYRIGHT);
  kprint("> ");
}

namespace
{
typedef void (*kshell_handle_t)(char const*);

struct kshell_handler
{
  char const* token       = nullptr;
  char const* help        = nullptr;
  kshell_handle_t handler = nullptr;
};

void ls_handler(char const*);
void man_handler(char const*);

constexpr kshell_handler handlers[] = {
    kshell_handler {
        .token   = "CLEAR",
        .help    = "clear dusplay",
        .handler = [](char const*) { clear_screen(); },
    },
    kshell_handler {
        .token   = "COPYRIGHT",
        .help    = "print copyright",
        .handler = [](char const*) { kprint(TUNIX_COPYRIGHT); },
    },
    kshell_handler {
        .token   = "ECHO",
        .help    = "print input to console",
        .handler = [](char const* input) { printf("%s\n", input + 5); },
    },
    kshell_handler {
        .token = "EXIT",
        .help  = "shutdown the system",
        .handler =
            [](char const*) {
              kprint("Stopping the CPU. Bye!\n");
              __asm__ __volatile__("hlt");
            },
    },
    kshell_handler {
        .token   = "FALSE",
        .help    = "test kernel assertions",
        .handler = [](char const*) { TNX_KASSERT(1 == 2); },
    },
    kshell_handler {
        .token   = "LS",
        .help    = "list programs",
        .handler = ls_handler,
    },
    kshell_handler {
        .token   = "MAN",
        .help    = "show program help",
        .handler = man_handler,
    },
    kshell_handler {
        .token = "PAGE",
        .help  = "request page from kmalloc",
        .handler =
            [](char const*) {
              auto const size = uint32_t {1000};
              auto phys_addr  = uint32_t {0};
              auto const page = kmalloc(size, 1, &phys_addr);
              printf("page: %X, size: %u, physical: %X\n", page, size,
                     phys_addr);
            },
    },
    kshell_handler {
        .token   = "UNAME",
        .help    = "print os name",
        .handler = [](char const*) { kprint("tunix\n"); },
    },
    kshell_handler {
        .token   = "TRUE",
        .help    = "test kernel assertions.",
        .handler = [](char const*) { TNX_KASSERT(true); },
    },
    kshell_handler {
        .token   = "VERSION",
        .help    = "print os version",
        .handler = [](char const*) { printf("%s\n", TNX_VERSION_STRING); },
    },
};

TNX_NODISCARD bool starts_with(char const* str, char const* pre)
{
  auto const lenpre = strlen(pre);
  auto const lenstr = strlen(str);
  return lenstr < lenpre ? false : memcmp(pre, str, lenpre) == 0;
}

void ls_handler(char const*)
{
  for (auto const& hnd : handlers) { printf("%s\n", hnd.token); }
}

void man_handler(char const* input)
{
  for (auto const& hnd : handlers)
  {
    auto const* token = hnd.token;
    auto const* help  = hnd.help;
    if (starts_with(input + 4, token)) { printf("%s: %s\n", token, help); }
  }
}

}  // namespace

void user_input(char const* input)
{
  for (auto const& hnd : handlers)
  {
    if (starts_with(input, hnd.token))
    {
      if (hnd.handler != nullptr) { hnd.handler(input); }
      break;
    }
  }

  kprint("> ");
}
