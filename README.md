# tunix

Unix like toy operating system.

## Quick Start

Currently only building with clang is supported. The build-system expects `clang`, `clang++` and `ld.lld` to be present in `$PATH`. They can be changed in `sys/make/clang.mk`.

### Dependencies

```sh
# Debian/Ubuntu
sudo apt install nasm clang build-essential

# FreeBSD
sudo pkg install gmake nasm
```

### Steps

```sh
# Replace make with gmake when compiling in BSD systems

CLANG=1 make all        # Build kernal & image
CLANG=1 make clean      # Clean all build artifacts
CLANG=1 make info       # Print env & config variables
CLANG=1 make run        # Run image in qemu
```

## Code Layout

```sh
sys                     # Root for all source code
├── arch                # Platform specific boot & init
│   ├── template        # Example for new platforms
│   └── x86             # x86 implementation
├── driver              # drivers
├── kernel              # kernel
├── make                # Makefile config
└── sys                 # System headers
```

See [sys/arch/template](sys/arch/template) for details on platforms specific code.

## Resources

- [github.com/cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [FreeBSD Kernel Internals, Dr. Marshall Kirk McKusick](https://www.youtube.com/watch?v=nwbqBdghh6E)
- [Writing a Simple Operating System from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [Fast IPC: L4 and Fast Interprocess Communication](https://www.youtube.com/watch?v=mRr1lCJse_I)
- [Preemptive Scheduling: How to Share a Processor](https://www.youtube.com/watch?v=1hDCouuvers)
