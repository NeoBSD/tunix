include $(TOP)/config.mk

ASM=nasm
LD=ld

KERNEL=tunix
IMAGE=$(KERNEL)-image

COMMON += -O2
COMMON += -ffreestanding
COMMON += -fno-pie
COMMON += -fno-strict-aliasing
COMMON += -mno-red-zone
COMMON += -nostdlib
COMMON += -static

COMMON += -Werror
COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

DEFINES += -DTUNIX
INCLUDES += -I$(TOP)/sys

COMMON += $(DEFINES)
COMMON += $(INCLUDES)

CFLAGS += $(COMMON)
CFLAGS += -std=c99

CXXFLAGS += $(COMMON)
CXXFLAGS += -std=c++17
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti

LDFLAGS += -nodefaultlibs
LDFLAGS += --no-undefined

include $(TOP)/mk/tunix.sanitizer.mk

ifdef CLANG
include $(TOP)/mk/tunix.clang.mk
endif

ifndef CLANG
include $(TOP)/mk/tunix.gcc.mk
endif