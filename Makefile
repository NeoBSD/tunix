ARCH ?= x86
QEMU=qemu-system-i386

BIN_DIR=bin

.PHONY: all
all: kernel

${BIN_DIR}:
	@mkdir -p ${BIN_DIR}

.PHONY: kernel
kernel: ${BIN_DIR}
	@ARCH=${ARCH} QEMU=${QEMU} ${MAKE} -C sys all
	@mv sys/tunix-image.bin sys/tunix.bin sys/tunix.elf ${BIN_DIR}

.PHONY: run
run:
	${QEMU} -fda ${BIN_DIR}/tunix-image.bin

.PHONY: debug
debug:
	${QEMU} -s -fda ${BIN_DIR}/tunix-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file ${BIN_DIR}/tunix.elf"

.PHONY: clean
clean:
	ARCH=${ARCH} QEMU=${QEMU} ${MAKE} -C sys clean
	rm -rf ${BIN_DIR}

.PHONY: format
format:
	find sys -iname '*.h' -o -iname '*.c' -o -iname '*.cc' | xargs clang-format -i

.PHONY: info
info:
	ARCH=${ARCH} QEMU=${QEMU} ${MAKE} -C sys info

