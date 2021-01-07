ASM=nasm

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
FREESTANDING += -fno-stack-protector
FREESTANDING += -nostdinc

DEFINES += -DTUNIX
DEFINES += $(addprefix -DTUNIX_ENABLE_, ${OPTIONS})

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

