# Locations of things.
OSTREE=${HOME}/tunix/root	# Root directory to install into.
WORKDIR=${TOP}/build		# Top of tree to build into.
BUILDSYMLINKS=yes		# yes => link build -> ${BUILDTOP}/${HERE}.

############################################################
# Get defs.mk to get the real configuration for this tree.
# If it doesn't exist, we'll go with the defaults.

.-include "${TOP}/defs.mk"

############################################################
# Make sure we have a supported PLATFORM and MACHINE.
# x86 elf support only currently
SUPPORTED_TARGETS=elf x86

_OK_=0
.for _P_ _M_ in ${SUPPORTED_TARGETS}
.if "${PLATFORM}" == "${_P_}" && "${MACHINE}" == "${_M_}"
_OK_=1
.endif
.endfor

.if "${_OK_}" != "1"
.init:
	@echo "Platform ${PLATFORM} and machine ${MACHINE} not supported"
	@false
.endif

############################################################
# Get any machine-dependent flags or makefile definitions
.-include "${TOP}/mk/os161.config-${MACHINE}.mk"