TOP=.
.include "${TOP}/mk/tunix.config.mk"

all:;

MKDIRS=${OSTREE}

.include "${TOP}/mk/tunix.mkdirs.mk"

.PHONY: all
all: tools .WAIT #includes .WAIT build

.PHONY: rebuild
rebuild:
	${MAKE} clean
	${MAKE} all

.PHONY: fullrebuild
fullrebuild:
	${MAKE} distclean
	${MAKE} all

.PHONY: tools
tools:
	@true

build:
	(cd user && ${MAKE} build)
	(cd man && ${MAKE} install-staging)

includes tags depend:
	(cd kern && ${MAKE} $@)
	(cd user && ${MAKE} $@)

clean:
	(cd kern && ${MAKE} $@)
	(cd user && ${MAKE} $@)
	rm -rf ${INSTALLTOP}

distclean: clean
	rm -rf ${WORKDIR}

.PHONY: info
info:
	@echo ${TOP}
	@echo ${WORKDIR}