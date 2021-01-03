#ifndef PORTS_H
#define PORTS_H

#include "sys/stdint.h"

TUNIX_BEGIN_EXTERN_C

unsigned char port_byte_in(uint16_t port);
void port_byte_out(uint16_t port, uint8_t data);
unsigned short port_word_in(uint16_t port);
void port_word_out(uint16_t port, uint16_t data);

TUNIX_END_EXTERN_C

#endif
