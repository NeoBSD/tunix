# Template

Example directory for layout of an architecture port. See `x86` for a real implementation.

## Create new architecture port

- Copy `template` to `new_arch`
- Rename `template` files to `new_arch`
- Set `Makefile` variables in `make/arch.mk`
- Write boot assembly that calls `kernel_main`
