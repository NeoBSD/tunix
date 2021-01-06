# Copyright (c) 2021, Tobias Hienzsch
# All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:

#  * Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.

# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES, LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
# DAMAGE.

# Defined in isr.c
.global isr_handler
.global irq_handler

.section .text

# Common ISR code
isr_common_stub:
    # 1. Save CPU state
	pusha # Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax
	mov %ds, %ax # Lower 16-bits of eax = ds.
	push %eax # save the data segment descriptor
	mov $0x10, %ax # kernel data segment descriptor
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	push %esp # registers_t *r
    # 2. Call C handler
    cld # C code following the sysV ABI requires DF to be clear on function entry
	call isr_handler

    # 3. Restore state
	pop %eax
    pop %eax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %fs
	mov %ax, %gs
	popa
	add $8, %esp # Cleans up the pushed error code and pushed ISR number
	iret # pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP

# Common IRQ code. Identical to ISR code except for the 'call'
# and the 'pop ebx'
irq_common_stub:
    pusha
    mov %ds, %ax
    push %eax
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    push %esp
    cld
    call irq_handler # Different than the ISR code
    pop %ebx  # Different than the ISR code
    pop %ebx
    mov %bx, %ds
    mov %bx, %es
    mov %bx, %fs
    mov %bx, %gs
    popa
    add $8, %esp
    iret

# We don't get information about which interrupt was caller
# when the handler is run, so we will need to have a different handler
# for every interrupt.
# Furthermore, some interrupts push an error code onto the stack but others
# don't, so we will push a dummy error code for those which don't, so that
# we have a consistent stack for all of them.

# First make the ISRs global
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31
# IRQs
.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

# 0: Divide By Zero Exception
isr0:
    push $0
    push $0
    jmp isr_common_stub

# 1: Debug Exception
isr1:
    push $0
    push $1
    jmp isr_common_stub

# 2: Non Maskable Interrupt Exception
isr2:
    push $0
    push $2
    jmp isr_common_stub

# 3: Int 3 Exception
isr3:
    push $0
    push $3
    jmp isr_common_stub

# 4: INTO Exception
isr4:
    push $0
    push $4
    jmp isr_common_stub

# 5: Out of Bounds Exception
isr5:
    push $0
    push $5
    jmp isr_common_stub

# 6: Invalid Opcode Exception
isr6:
    push $0
    push $6
    jmp isr_common_stub

# 7: Coprocessor Not Available Exception
isr7:
    push $0
    push $7
    jmp isr_common_stub

# 8: Double Fault Exception (With Error Code!)
isr8:
    push $8
    jmp isr_common_stub

# 9: Coprocessor Segment Overrun Exception
isr9:
    push $0
    push $9
    jmp isr_common_stub

# 10: Bad TSS Exception (With Error Code!)
isr10:
    push $10
    jmp isr_common_stub

# 11: Segment Not Present Exception (With Error Code!)
isr11:
    push $11
    jmp isr_common_stub

# 12: Stack Fault Exception (With Error Code!)
isr12:
    push $12
    jmp isr_common_stub

# 13: General Protection Fault Exception (With Error Code!)
isr13:
    push $13
    jmp isr_common_stub

# 14: Page Fault Exception (With Error Code!)
isr14:
    push $14
    jmp isr_common_stub

# 15: Reserved Exception
isr15:
    push $0
    push $15
    jmp isr_common_stub

# 16: Floating Point Exception
isr16:
    push $0
    push $16
    jmp isr_common_stub

# 17: Alignment Check Exception
isr17:
    push $0
    push $17
    jmp isr_common_stub

# 18: Machine Check Exception
isr18:
    push $0
    push $18
    jmp isr_common_stub

# 19: Reserved
isr19:
    push $0
    push $19
    jmp isr_common_stub

# 20: Reserved
isr20:
    push $0
    push $20
    jmp isr_common_stub

# 21: Reserved
isr21:
    push $0
    push $21
    jmp isr_common_stub

# 22: Reserved
isr22:
    push $0
    push $22
    jmp isr_common_stub

# 23: Reserved
isr23:
    push $0
    push $23
    jmp isr_common_stub

# 24: Reserved
isr24:
    push $0
    push $24
    jmp isr_common_stub

# 25: Reserved
isr25:
    push $0
    push $25
    jmp isr_common_stub

# 26: Reserved
isr26:
    push $0
    push $26
    jmp isr_common_stub

# 27: Reserved
isr27:
    push $0
    push $27
    jmp isr_common_stub

# 28: Reserved
isr28:
    push $0
    push $28
    jmp isr_common_stub

# 29: Reserved
isr29:
    push $0
    push $29
    jmp isr_common_stub

# 30: Reserved
isr30:
    push $0
    push $30
    jmp isr_common_stub

# 31: Reserved
isr31:
    push $0
    push $31
    jmp isr_common_stub

# IRQ handlers
irq0:
	push $0
	push $32
	jmp irq_common_stub

irq1:
	push $1
	push $33
	jmp irq_common_stub

irq2:
	push $2
	push $34
	jmp irq_common_stub

irq3:
	push $3
	push $35
	jmp irq_common_stub

irq4:
	push $4
	push $36
	jmp irq_common_stub

irq5:
	push $5
	push $37
	jmp irq_common_stub

irq6:
	push $6
	push $38
	jmp irq_common_stub

irq7:
	push $7
	push $39
	jmp irq_common_stub

irq8:
	push $8
	push $40
	jmp irq_common_stub

irq9:
	push $9
	push $41
	jmp irq_common_stub

irq10:
	push $10
	push $42
	jmp irq_common_stub

irq11:
	push $11
	push $43
	jmp irq_common_stub

irq12:
	push $12
	push $44
	jmp irq_common_stub

irq13:
	push $13
	push $45
	jmp irq_common_stub

irq14:
	push $14
	push $46
	jmp irq_common_stub

irq15:
	push $15
	push $47
	jmp irq_common_stub

