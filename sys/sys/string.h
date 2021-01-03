#ifndef STRINGS_H
#define STRINGS_H

#include "sys/cdefs.h"
TUNIX_BEGIN_EXTERN_C

void int_to_ascii(int n, char* str);
void hex_to_ascii(int n, char* str);
void reverse(char* s);
int strlen(char const* s);
void backspace(char* s);
void append(char* s, char n);
int strcmp(char const* s1, char const* s2);

TUNIX_END_EXTERN_C

#endif
