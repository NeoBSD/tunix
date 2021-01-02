CC=clang
CXX=clang++
LD=ld.lld

ASFLAGS += -x assembler-with-cpp
CFLAGS += -Wno-empty-body
CXXFLAGS += -Wno-deprecated-volatile
