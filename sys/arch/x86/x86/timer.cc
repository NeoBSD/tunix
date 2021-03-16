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

#include "arch/x86/include/timer.h"
#include "arch/x86/include/ports.h"

namespace
{
uint32_t tick = 0;

void timer_callback(registers_t* regs)
{
  tick++;
  TNX_UNUSED(regs);
}
}  // namespace

void tnx_timer_init(uint32_t freq)
{
  /* Install the function we just wrote */
  register_interrupt_handler(IRQ0, timer_callback);

  /* Get the PIT value: hardware clock at 1193180 Hz */
  uint32_t divisor = 1193180 / freq;
  auto low         = (uint8_t)(divisor & 0xFF);
  auto high        = (uint8_t)((divisor >> 8) & 0xFF);
  /* Send the command */
  port_byte_out(0x43, 0x36); /* Command port */
  port_byte_out(0x40, low);
  port_byte_out(0x40, high);
}

uint32_t tnx_timer_ticks() { return tick; }