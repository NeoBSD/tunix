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

#include "sys/kshell.h"

#include "sys/copyright.h"
#include "sys/kernel_mem.h"
#include "sys/param.h"
#include "sys/string.h"
#include "sys/systm.h"

#include "driver/screen.h"

namespace
{
void ls_entry_point(char const*);
void man_entry_point(char const*);

constexpr kshell_command entry_points[] = {
    kshell_command {
        "CLEAR",
        "clear dusplay",
        [](char const*) { clear_screen(); },
    },
    kshell_command {
        "COPYRIGHT",
        "print copyright",
        [](char const*) { kprint(TUNIX_COPYRIGHT); },
    },
    kshell_command {
        "ECHO",
        "print input to console",
        [](char const* input) { printf("%s\n", input + 5); },
    },
    kshell_command {
        "EXIT",
        "shutdown the system",
        [](char const*) {
          kprint("Stopping the CPU. Bye!\n");
          __asm__ __volatile__("hlt");
        },
    },
    kshell_command {
        "FALSE",
        "test kernel assertions",
        [](char const*) { TNX_KASSERT(1 == 2); },
    },
    kshell_command {
        "LS",
        "list programs",
        ls_entry_point,
    },
    kshell_command {
        "MAN",
        "show program help",
        man_entry_point,
    },
    kshell_command {
        "PAGE",
        "request page from kmalloc",
        [](char const*) {
          auto const size = uint32_t {1000};
          auto phys_addr  = uint32_t {0};
          auto const page = kmalloc(size, 1, &phys_addr);
          printf("page: %X, size: %u, physical: %X\n", page, size, phys_addr);
        },
    },
    kshell_command {
        "UNAME",
        "print os name",
        [](char const*) { kprint("tunix\n"); },
    },
    kshell_command {
        "TRUE",
        "test kernel assertions.",
        [](char const*) { TNX_KASSERT(true); },
    },
    kshell_command {
        "VERSION",
        "print os version",
        [](char const*) { printf("%s\n", TNX_VERSION_STRING); },
    },
};

void ls_entry_point(char const*)
{
  for (auto const& hnd : entry_points) { printf("%s\n", hnd.token); }
}

void man_entry_point(char const* input)
{
  for (auto const& hnd : entry_points)
  {
    auto const* token = hnd.token;
    auto const* help  = hnd.help;
    if (starts_with(input + 4, token)) { printf("%s: %s\n", token, help); }
  }
}

}  // namespace

void kshell_process_input(char const* input)
{
  for (auto const& hnd : entry_points)
  {
    if (starts_with(input, hnd.token))
    {
      if (hnd.entry_point != nullptr) { hnd.entry_point(input); }
      break;
    }
  }

  kprint("> ");
}