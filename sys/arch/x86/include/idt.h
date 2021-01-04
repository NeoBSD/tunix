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

#ifndef TUNIX_ARCH_X86_IDT_H
#define TUNIX_ARCH_X86_IDT_H

#include "sys/stdint.h"

TUNIX_BEGIN_EXTERN_C

/* Segment selectors */
#define KERNEL_CS 0x08

/* How every interrupt gate (handler) is defined */
typedef struct
{
  uint16_t low_offset; /* Lower 16 bits of handler function address */
  uint16_t sel;        /* Kernel segment selector */
  uint8_t always0;
  /* First byte
   * Bit 7: "Interrupt is present"
   * Bits 6-5: Privilege level of caller (0=kernel..3=user)
   * Bit 4: Set to 0 for interrupt gates
   * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
  uint8_t flags;
  uint16_t high_offset; /* Higher 16 bits of handler function address */
} __attribute__((packed)) idt_gate_t;

/* A pointer to the array of interrupt handlers.
 * Assembly instruction 'lidt' will read it */
typedef struct
{
  uint16_t limit;
  uint32_t base;
} __attribute__((packed)) idt_register_t;

/* Functions implemented in idt.c */
void set_idt_gate(int n, uint32_t handler);
void set_idt();

TUNIX_END_EXTERN_C

#endif
