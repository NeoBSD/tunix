TOP=.
include ${TOP}/mk/tunix.make.mk

.PHONY: all
all: info kernel

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
	@printf "%-10s = %s\n" "VER" "0.1.0"
	@printf "%-10s = %s\n" "ARCH" "${ARCH}"
	@printf "%-10s = %s\n" "KERNEL" "${KERNEL}"
	@printf "%-10s = %s\n" "IMAGE" "${IMAGE}"
	@printf "%-10s = %s\n" "BIN_DIR" "${BIN_DIR}"
	@printf "%-10s = %s\n" "HOST_OS" "${HOST_OS}"
	@printf "%-10s = %s\n" "HOST_ARCH" "${HOST_ARCH}"
	@printf "%-10s = %s\n" "CC" "${CC}"
	@printf "%-10s = %s\n" "CXX" "${CXX}"
	@printf "%-10s = %s\n" "QEMU" "${QEMU}"
	@printf "%-10s = %s\n" "OPTIONS" "${OPTIONS}"
	@printf "%-10s = %s\n" "DEFINES" "${DEFINES}"
	@printf "%-10s = %s\n" "ASMFLAGS" "${ASMFLAGS}"
	@printf "%-10s = %s\n" "CFLAGS" "${CFLAGS}"
	@printf "%-10s = %s\n" "CXXFLAGS" "${CXXFLAGS}"
	@printf "%-10s = %s\n" "LDFLAGS" "${LDFLAGS}"

