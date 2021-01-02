include make/common.mk

ifndef CLANG
        include make/gcc.mk
else
        include make/clang.mk
endif

include arch/${ARCH}/arch.mk

CC_SRC += $(wildcard kernel/*.c driver/*.c)
CXX_SRC += $(wildcard kernel/*.cc driver/*.cc)
HEADERS += $(wildcard kernel/*.h driver/*.h)

OBJ += ${CC_SRC:.c=.o}
OBJ += ${CXX_SRC:.cc=.o}


.PHONY: all
all: info ${IMAGE}.bin ${KERNEL}.bin ${KERNEL}.elf

${IMAGE}.bin: arch/${ARCH}/bootsect.bin ${KERNEL}.bin
	cat $^ > ${IMAGE}.bin

${KERNEL}.bin: arch/${ARCH}/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^ --oformat binary

${KERNEL}.elf: arch/${ARCH}/kernel_entry.o ${OBJ}
	${LD} -o $@ -Ttext 0x1000 $^

%.o: %.c ${HEADERS}
	${CC} ${ARCHFLAGS} ${CFLAGS} -c $< -o $@

%.o: %.cc ${HEADERS}
	${CXX} ${ARCHFLAGS} ${CXXFLAGS} -c $< -o $@

%.o: %.asm
	${ASM} $< -f elf -o $@

%.bin: %.asm
	${ASM} $< -f bin -o $@

.PHONY: clean
clean:
	rm -rf *.bin *.dis *.o ${IMAGE}.bin *.elf
	rm -rf kernel/*.o driver/*.o arch/${ARCH}/*.o arch/${ARCH}/*.bin

.PHONY: info
info:
	@echo "ARCH=${ARCH}"
	@echo "CC=${CC}"
	@echo "CXX=${CXX}"
	@echo "LD=${LD}"
	@echo "QEMU=${QEMU}"