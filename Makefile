BIN_DIR=bin
QEMU_X64=qemu-system-x86_64

.PHONY: all
all: kernel

${BIN_DIR}:
	mkdir -p ${BIN_DIR}

.PHONY: kernel
kernel: ${BIN_DIR}
	${MAKE} -C sys os-image.bin kernel.bin kernel.elf
	mv sys/os-image.bin ${BIN_DIR}
	mv sys/kernel.bin ${BIN_DIR}
	mv sys/kernel.elf ${BIN_DIR}

.PHONY: run
run:
	${QEMU_X64} -fda ${BIN_DIR}/os-image.bin

.PHONY: debug
debug:
	${QEMU_X64} -s -fda ${BIN_DIR}/os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file ${BIN_DIR}/kernel.elf"

.PHONY: clean
clean:
	${MAKE} -C sys clean
	rm -rf ${BIN_DIR}

.PHONY: info
info:
	${MAKE} -C sys info