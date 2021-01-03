#ifndef MEM_H
#define MEM_H

#include "sys/stdint.h"
#include <stddef.h>

TUNIX_BEGIN_EXTERN_C

void memory_copy(uint8_t* source, uint8_t* dest, int nbytes);
void memory_set(uint8_t* dest, uint8_t val, uint32_t len);

/* At this stage there is no 'free' implemented. */
uint32_t kmalloc(size_t size, int align, uint32_t* phys_addr);

TUNIX_END_EXTERN_C
#endif
