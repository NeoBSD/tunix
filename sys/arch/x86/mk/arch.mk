COMMON 	+= -m32

LDFLAGS += -Wl,-melf_i386
LDFLAGS += -Wl,-Ttext=0x1000

