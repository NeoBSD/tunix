CC=gcc
CXX=g++
LD=ld.lld

ASFLAGS += -x assembler-with-cpp
CFLAGS += -Wno-empty-body
CXXFLAGS += -Wno-deprecated-volatile