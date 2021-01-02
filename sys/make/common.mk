COMMON += -O2

COMMON += -Wall
COMMON += -Wextra
COMMON += -Wpedantic

DEFINES += -DTUNIX
INCLUDES += -I${shell pwd}

COMMON += ${DEFINES}
COMMON += ${INCLUDES}

CFLAGS += -std=c99
CFLAGS += ${COMMON}

CXXFLAGS += -std=c++17
CXXFLAGS += ${COMMON}
