ASM=nasm

ifdef DEBUG
COMMON += -Og
COMMON += -g
else
COMMON += -O2
endif

COMMON += -static
COMMON += -fno-pie

COMMON += -Werror
COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

FREESTANDING += -ffreestanding
FREESTANDING += -ffunction-sections
FREESTANDING += -fdata-sections
FREESTANDING += -fno-builtin
FREESTANDING += -fno-strict-aliasing
FREESTANDING += -fno-stack-protector
FREESTANDING += -nostdinc
FREESTANDING += -nostdinc++

DEFINES += -DTUNIX
DEFINES += $(addprefix -DTUNIX_ENABLE_, ${OPTIONS})

INCLUDES += -I${TOP}/sys

ASMFLAGS += -x assembler-with-cpp

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

LDFLAGS += -nostdlib
LDFLAGS += -nostartfiles
LDFLAGS += -nodefaultlibs
LDFLAGS += -Wl,--no-undefined
LDFLAGS += -Wl,--nmagic
LDFLAGS += -Wl,--gc-sections
