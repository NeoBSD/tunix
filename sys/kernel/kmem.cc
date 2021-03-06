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

#include "sys/kmem.h"
#include "sys/systm.h"

void kmemcpy(uint8_t const* source, uint8_t* dest, int nbytes)
{
  for (int i = 0; i < nbytes; i++) { *(dest + i) = *(source + i); }
}

void kmemset(uint8_t* dest, uint8_t val, uint32_t len)
{
  auto* temp = (uint8_t*)dest;
  for (; len != 0; len--) { *temp++ = val; }
}

int kmemcmp(void const* s1, void const* s2, size_t n)
{
  if (n != 0)
  {
    auto const* p1 = reinterpret_cast<uint8_t const*>(s1);
    auto const* p2 = reinterpret_cast<uint8_t const*>(s2);
    do {
      if (*p1++ != *p2++) { return (*--p1) - (*--p2); }
    } while (--n != 0);
  }
  return 0;
}

/**
 * @brief This should be computed at link time, but a hardcoded
 * value is fine for now. Remember that our kernel starts
 * at 0x1000 as defined on the Makefile
 */
auto free_mem_addr = uintptr_t {0x10000};

/**
 * @brief Implementation is just a pointer to some free memory which keeps
 * growing
 */
void* kmalloc(size_t size, int align, uintptr_t* phys_addr)
{
  // Pages are aligned to 4K, or 0x1000
  if (align == 1 && ((free_mem_addr & 0xFFFFF000) != 0u))
  {
    free_mem_addr &= 0xFFFFF000;
    free_mem_addr += 0x1000;
  }

  // Save also the physical address
  if (phys_addr != nullptr) { *phys_addr = free_mem_addr; }

  // Remember to increment the pointer
  auto const ret = free_mem_addr;
  free_mem_addr += size;
  return reinterpret_cast<void*>(ret);
}
