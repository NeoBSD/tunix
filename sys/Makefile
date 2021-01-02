include make/common.mk

ifndef CLANG
        include make/gcc.mk
else
        include make/clang.mk
endif

CC_SRC += $(wildcard kernel/*.c driver/*.c)
CXX_SRC += $(wildcard kernel/*.cc driver/*.cc)
HEADERS += $(wildcard kernel/*.h driver/*.h)

OBJ += ${CC_SRC:.c=.o}
OBJ += ${CXX_SRC:.cc=.o}

ARCHFLAGS += -target i386-pc-none-elf
ARCHFLAGS += -ffreestanding

# First rule is run by default
os-image.bin: arch/x86/bootsect.bin kernel.bin
	cat $^ > os-image.bin

# '--oformat binary' deletes all symbols as a collateral, so we don't need
# to 'strip' them manually on this case
kernel.bin: arch/x86/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

# Used for debugging purposes
kernel.elf: arch/x86/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

%.o: %.c ${HEADERS}
	${CC} ${ARCHFLAGS} ${CFLAGS} -c $< -o $@

%.o: %.cc ${HEADERS}
	${CXX} ${ARCHFLAGS} ${CXXFLAGS} -c $< -o $@


%.o: %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

.PHONY: clean
clean:
	rm -rf *.bin *.dis *.o os-image.bin *.elf
	rm -rf kernel/*.o driver/*.o arch/x86/*.o arch/x86/*.bin

.PHONY: info
info:
	@echo "CC=${CC}"
	@echo "CXX=${CXX}"
	@echo "LD=${LD}"
	@echo "QEMU=${QEMU_X64}"