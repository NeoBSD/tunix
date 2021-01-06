TOP=.
include ${TOP}/mk/tunix.config.mk

${BIN_DIR}:
	@mkdir -p ${BIN_DIR}

.PHONY: kernel
kernel: ${BIN_DIR}
	${MAKE} -C sys all
	@mv sys/${IMAGE} sys/${KERNEL}.bin sys/${KERNEL}.elf ${BIN_DIR}

.PHONY: run
run:
	${QEMU} -drive file=${BIN_DIR}/${IMAGE},format=raw

.PHONY: debug
debug:
	${QEMU} -s -drive file=${BIN_DIR}/${IMAGE},format=raw &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file ${BIN_DIR}/${KERNEL}.elf"

.PHONY: clean
clean:
	rm -rf ${BIN_DIR}
	${MAKE} -C sys clean

.PHONY: format
format:
	find sys -iname '*.h' -o -iname '*.c' -o -iname '*.cc' | xargs clang-format -i

.PHONY: info
info:
	@echo "VER      =	0.1.0"
	@echo "CC       =	${CC}"
	@echo "CXX      =	${CXX}"
	@echo "ARCH     =	${ARCH}"
	@echo "KERNEL   =	${KERNEL}"
	@echo "IMAGE    =	${IMAGE}"
	@echo "BIN      =	${BIN_DIR}"
	@echo "QEMU     =	${QEMU}"

