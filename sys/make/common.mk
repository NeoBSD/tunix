ASM=nasm
LD=ld

KERNEL=tunix
IMAGE=${KERNEL}-image

COMMON += -O2
COMMON += -ffreestanding
COMMON += -fno-pie
COMMON += -fno-strict-aliasing
COMMON += -mno-red-zone

COMMON += -nostdlib
COMMON += -nostartfiles
COMMON += -nodefaultlibs

COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

DEFINES += -DTUNIX
INCLUDES += -I${shell pwd}

COMMON += ${DEFINES}
COMMON += ${INCLUDES}

CFLAGS += ${COMMON}
CFLAGS += -std=c99

CXXFLAGS += ${COMMON}
CXXFLAGS += -std=c++17
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fno-rtti
