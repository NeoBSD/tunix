#ifndef TIMER_H
#define TIMER_H

#include "isr.h"

#include "sys/stdint.h"

TUNIX_BEGIN_EXTERN_C

void timer_callback(registers_t* regs);
void init_timer(uint32_t freq);

TUNIX_END_EXTERN_C

#endif
