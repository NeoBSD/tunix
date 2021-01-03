include make/common.mk

ifndef CLANG
        include make/gcc.mk
else
        include make/clang.mk
endif

include arch/${ARCH}/make/arch.mk

CC_SRC += $(wildcard kernel/*.c sys/*.c driver/*.c arch/${ARCH}/${ARCH}/*.c)
CXX_SRC += $(wildcard kernel/*.cc sys/*.cc driver/*.cc arch/${ARCH}/${ARCH}/*.cc)
HEADERS += $(wildcard kernel/*.h sys/*.h driver/*.h arch/${ARCH}/${ARCH}/*.h)

OBJ += arch/${ARCH}/${ARCH}/interrupt.o
OBJ += ${CC_SRC:.c=.o}
OBJ += ${CXX_SRC:.cc=.o}


.PHONY: all
all: info ${IMAGE}.bin ${KERNEL}.bin ${KERNEL}.elf

${IMAGE}.bin: arch/${ARCH}/${ARCH}/bootsect.bin ${KERNEL}.bin
	cat $^ > ${IMAGE}.bin

${KERNEL}.bin: arch/${ARCH}/${ARCH}/kernel_entry.o ${OBJ}
	${LD} ${LDFLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

${KERNEL}.elf: arch/${ARCH}/${ARCH}/kernel_entry.o ${OBJ}
	${LD} ${LDFLAGS} -o $@ -Ttext 0x1000 $^

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
	rm -rf kernel/*.o driver/*.o arch/${ARCH}/${ARCH}/*.o arch/${ARCH}/${ARCH}/*.bin

.PHONY: info
info:
	@echo "ARCH=${ARCH}"
	@echo "CC=${CC}"
	@echo "CXX=${CXX}"
	@echo "LD=${LD}"
	@echo "QEMU=${QEMU}"