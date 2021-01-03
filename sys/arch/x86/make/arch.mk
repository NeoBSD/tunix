LDFLAGS += -melf_i386
ARCHFLAGS += -m32

ifdef CLANG
	ARCHFLAGS += -target i386-pc-none-elf
endif
