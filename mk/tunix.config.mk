include $(TOP)/config.mk

ASM=nasm
LD=ld

KERNEL=tunix
IMAGE=$(KERNEL)-image

COMMON += -O2
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

INCLUDES += -nostdinc
INCLUDES += -I$(TOP)/sys
COMMON   += $(INCLUDES)


CFLAGS += $(COMMON)
CFLAGS += -std=c99

CXXFLAGS += $(COMMON)
CXXFLAGS += -std=c++17
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += -fno-threadsafe-statics

LDFLAGS += -nodefaultlibs
LDFLAGS += -nolibc
LDFLAGS += -nostdlib
LDFLAGS += -nostartfiles
LDFLAGS += --no-undefined

include $(TOP)/mk/tunix.sanitizer.mk

ifdef CLANG
include $(TOP)/mk/tunix.clang.mk
endif

ifndef CLANG
include $(TOP)/mk/tunix.gcc.mk
endif