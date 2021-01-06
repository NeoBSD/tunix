include $(TOP)/config.mk

ASM=nasm

KERNEL=tunix
IMAGE=$(KERNEL)-image

COMMON += -O0
COMMON += -static
COMMON += -ffreestanding
COMMON += -fno-builtin
COMMON += -fno-pie
COMMON += -fno-strict-aliasing
COMMON += -mno-red-zone

COMMON += -Werror
COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

DEFINES += -DTUNIX
COMMON  += $(DEFINES)

INCLUDES += -I$(TOP)/sys
COMMON   += $(INCLUDES)

CFLAGS += -std=c99
CFLAGS += -nostdinc

CXXFLAGS += -std=c++17
CXXFLAGS += -nostdinc
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += -fno-threadsafe-statics

LDFLAGS += -nodefaultlibs
LDFLAGS += -nostdlib
LDFLAGS += -nostartfiles
LDFLAGS += -Wl,--no-undefined

