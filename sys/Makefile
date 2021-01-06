ARCH_DIR=arch/${ARCH}
include ${ARCH_DIR}/mk/arch.mk

TOP=..
include ${TOP}/mk/tunix.config.mk

CC_SRC  += ${wildcard kernel/*.c sys/*.c driver/*.c ${ARCH_DIR}/${ARCH}/*.c}
CXX_SRC += ${wildcard kernel/*.cc sys/*.cc driver/*.cc ${ARCH_DIR}/${ARCH}/*.cc}
HEADERS += ${wildcard kernel/*.h sys/*.h driver/*.h ${ARCH_DIR}/${ARCH}/*.h}

OBJ += ${ARCH_DIR}/${ARCH}/interrupt.o
OBJ += ${CC_SRC:.c=.o}
OBJ += ${CXX_SRC:.cc=.o}

.PHONY: all
all: machine depend ${IMAGE}.bin

.PHONY: depend
depend:
	${CXX} ${CXXFLAGS} -E -MM ${CXX_SRC}  > .depend
	# ${CC} ${CFLAGS} -E -MM ${CC_SRC}  >> .depend

machine:
	ln -s ${ARCH_DIR}/include ${TOP}/sys/$@

${IMAGE}.bin: ${ARCH_DIR}/${ARCH}/bootsect.bin ${KERNEL}.bin
	cat $^ > ${IMAGE}.bin

${KERNEL}.bin: ${KERNEL}.elf
	objcopy -O binary $^ $@

${KERNEL}.elf: ${ARCH_DIR}/${ARCH}/kernel_entry.o ${OBJ}
	${CXX} ${LDFLAGS} -o $@ $^

include ${TOP}/mk/tunix.compile.mk

.PHONY: clean
clean:
	rm -f machine
	rm -rf .depend *.bin *.dis *.o ${IMAGE}.bin *.elf
	rm -rf kernel/*.o sys/*.o driver/*.o ${ARCH_DIR}/${ARCH}/*.o ${ARCH_DIR}/${ARCH}/*.bin
