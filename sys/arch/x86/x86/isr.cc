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

#include "isr.h"
#include "idt.h"

#include "driver/screen.h"

#include "sys/libkern.h"

/* Can't do this with a loop because we need the address
 * of the function names */
void isr_install()
{
  set_idt_gate(0, (u32)isr0);
  set_idt_gate(1, (u32)isr1);
  set_idt_gate(2, (u32)isr2);
  set_idt_gate(3, (u32)isr3);
  set_idt_gate(4, (u32)isr4);
  set_idt_gate(5, (u32)isr5);
  set_idt_gate(6, (u32)isr6);
  set_idt_gate(7, (u32)isr7);
  set_idt_gate(8, (u32)isr8);
  set_idt_gate(9, (u32)isr9);
  set_idt_gate(10, (u32)isr10);
  set_idt_gate(11, (u32)isr11);
  set_idt_gate(12, (u32)isr12);
  set_idt_gate(13, (u32)isr13);
  set_idt_gate(14, (u32)isr14);
  set_idt_gate(15, (u32)isr15);
  set_idt_gate(16, (u32)isr16);
  set_idt_gate(17, (u32)isr17);
  set_idt_gate(18, (u32)isr18);
  set_idt_gate(19, (u32)isr19);
  set_idt_gate(20, (u32)isr20);
  set_idt_gate(21, (u32)isr21);
  set_idt_gate(22, (u32)isr22);
  set_idt_gate(23, (u32)isr23);
  set_idt_gate(24, (u32)isr24);
  set_idt_gate(25, (u32)isr25);
  set_idt_gate(26, (u32)isr26);
  set_idt_gate(27, (u32)isr27);
  set_idt_gate(28, (u32)isr28);
  set_idt_gate(29, (u32)isr29);
  set_idt_gate(30, (u32)isr30);
  set_idt_gate(31, (u32)isr31);

  set_idt();  // Load with ASM
}

/* To print the message which defines every exception */
constexpr char const* exception_messages[] = {"Division By Zero",
                                              "Debug",
                                              "Non Maskable Interrupt",
                                              "Breakpoint",
                                              "Into Detected Overflow",
                                              "Out of Bounds",
                                              "Invalid Opcode",
                                              "No Coprocessor",

                                              "Double Fault",
                                              "Coprocessor Segment Overrun",
                                              "Bad TSS",
                                              "Segment Not Present",
                                              "Stack Fault",
                                              "General Protection Fault",
                                              "Page Fault",
                                              "Unknown Interrupt",

                                              "Coprocessor Fault",
                                              "Alignment Check",
                                              "Machine Check",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",

                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved",
                                              "Reserved"};

void isr_handler(registers_t r)
{
  kprint("received interrupt: ");
  char s[3];
  kitoa(r.int_no, s);
  kprint(s);
  kprint("\n");
  kprint(exception_messages[r.int_no]);
  kprint("\n");
}
