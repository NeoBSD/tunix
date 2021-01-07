KERNEL=tunix-${ARCH}
IMAGE=${KERNEL}.img

# Info about the host building tunix
include ${TOP}/mk/tunix.host.mk

# Include user config from project root directory
include ${TOP}/config.mk

# Convert config to compiler defines and flags
include ${TOP}/mk/tunix.options.mk

ARCH_DIR=${TOP}/sys/arch/${ARCH}
include ${ARCH_DIR}/mk/arch.mk


ASMFLAGS 	+= ${COMMON}
CFLAGS 		+= ${COMMON}
CXXFLAGS 	+= ${COMMON}
LDFLAGS 	+= ${COMMON}

