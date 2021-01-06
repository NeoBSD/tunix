include ${TOP}/config.mk

ASM=nasm

KERNEL=tunix-${ARCH}
IMAGE=${KERNEL}.img

ifdef DEBUG
COMMON += -Og
COMMON += -g
else
COMMON += -O2
# COMMON += -flto
endif

COMMON += -static
COMMON += -fno-pie

COMMON += -Werror
COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

FREESTANDING += -ffreestanding
FREESTANDING += -fno-builtin
FREESTANDING += -fno-strict-aliasing
FREESTANDING += -mno-red-zone
FREESTANDING += -nostdinc

DEFINES += -DTUNIX
INCLUDES += -I${TOP}/sys

CFLAGS += -std=c99
CFLAGS += ${FREESTANDING}
CFLAGS += ${DEFINES}
CFLAGS += ${INCLUDES}

CXXFLAGS += -std=c++17
CXXFLAGS += ${FREESTANDING}
CXXFLAGS += ${DEFINES}
CXXFLAGS += ${INCLUDES}
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
CXXFLAGS += -fno-threadsafe-statics

LDFLAGS += -nodefaultlibs
LDFLAGS += -nostdlib
LDFLAGS += -nostartfiles
LDFLAGS += -Wl,--no-undefined

ARCH_DIR=${TOP}/sys/arch/${ARCH}
include ${ARCH_DIR}/mk/arch.mk

ASMFLAGS 	+= ${COMMON}
CFLAGS 		+= ${COMMON}
CXXFLAGS 	+= ${COMMON}
LDFLAGS 	+= ${COMMON}

