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

#ifndef TNX_ARCH_X86_IDT_H
#define TNX_ARCH_X86_IDT_H

#include "sys/stdint.h"

TNX_BEGIN_EXTERN_C

/**
 * @brief Segment selectors
 */
#define KERNEL_CS 0x08

/**
 * @brief How every interrupt gate (handler) is defined.
 */
struct idt_gate_t
{
  /**
   * @brief Lower 16 bits of handler function address
   */
  uint16_t low_offset;

  /**
   * @brief Kernel segment selector
   */
  uint16_t sel;

  /**
   * @brief Always set to zero.
   */
  uint8_t always0;

  /**
   * @details Bit 7: "Interrupt is present"
   * Bits 6-5: Privilege level of caller (0=kernel..3=user)
   * Bit 4: Set to 0 for interrupt gates
   * Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate"
   */
  uint8_t flags;

  /**
   * @brief Higher 16 bits of handler function address.
   */
  uint16_t high_offset;
} TNX_PACKED;

/**
 * @brief A pointer to the array of interrupt handlers. Assembly instruction
 * 'lidt' will read it.
 */
struct idt_register_t
{
  uint16_t limit;
  uint32_t base;
} TNX_PACKED;

/**
 * @brief
 */
void set_idt_gate(int n, uint32_t handler);

/**
 * @brief
 */
void set_idt();

TNX_END_EXTERN_C

#endif
