#ifndef TYPE_H
#define TYPE_H

#include "sys/stdint.h"

TUNIX_BEGIN_EXTERN_C

#define low_16(address) (uint16_t)((address)&0xFFFF)
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

TUNIX_END_EXTERN_C

#endif
