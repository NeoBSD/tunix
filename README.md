# tunix

Unix like toy operating system.

|                                                              License                                                               |                              x86 Clang                              |                             x86 GCC                             |
| :--------------------------------------------------------------------------------------------------------------------------------: | :-----------------------------------------------------------------: | :-------------------------------------------------------------: |
| [![License](https://img.shields.io/badge/License-BSD%202--Clause-orange.svg)](https://github.com/neoBSD/tunix/blob/master/LICENSE) | ![Clang](https://github.com/NeoBSD/tunix/workflows/Clang/badge.svg) | ![GCC](https://github.com/NeoBSD/tunix/workflows/GCC/badge.svg) |

## Quick Start

The build-system (Makefile) expects either `gcc`, `g++` or `clang`, `clang++` to be present in `$PATH`. They can be changed in `mk/tunix.clang.mk` or `mk/tunix.gcc.mk`. `nasm` and `ld` are always required.

### Dependencies

```sh
# Debian/Ubuntu
sudo apt install nasm clang lld build-essential

# FreeBSD
sudo pkg install gmake nasm
```

### Steps

```sh
# Replace make with gmake when compiling on BSD systems

# clang
CLANG=1 make all        # Build kernal & image
CLANG=1 make clean      # Clean all build artifacts
CLANG=1 make info       # Print env & config variables
CLANG=1 make run        # Run image in qemu

# gcc
make all        # Build kernal & image
make clean      # Clean all build artifacts
make info       # Print env & config variables
make run        # Run image in qemu
```

## Code Layout

```sh
.                           # Project root
├── mk                      # Makefile config
└── sys                     # Source code root
    ├── arch                # Platform specific boot & init
    │   ├── template        # Example for new platforms
    │   └── x86             # x86 implementation
    ├── driver              # Drivers
    ├── kernel              # Kernel source
    └── sys                 # System headers
```

See [sys/arch/template](sys/arch/template) for details on platforms specific code.

## Languages

- commit: **37d42af** 05.01.2021

```sh
-------------------------------------------------------------------------------
Language                     files          blank        comment           code
-------------------------------------------------------------------------------
C++                             10            195            451           1359
Assembly                         9            142            270            461
C/C++ Header                    18            133            599            322
make                             9             36              3            112
Markdown                         2             25              0             65
-------------------------------------------------------------------------------
SUM:                            48            531           1323           2319
-------------------------------------------------------------------------------
```

## Resources

- [github.com/cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [Writing a Simple Operating System from Scratch](https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf)
- [Harvard: OS161 Kernel (good Makefile build-system)](https://github.com/haisano/OS161-kernel)

### YouTube

- [FreeBSD Kernel Internals, Dr. Marshall Kirk McKusick](https://www.youtube.com/watch?v=nwbqBdghh6E)
- [Fast IPC: L4 and Fast Interprocess Communication](https://www.youtube.com/watch?v=mRr1lCJse_I)
- [Preemptive Scheduling: How to Share a Processor](https://www.youtube.com/watch?v=1hDCouuvers)
- [Virtual Memory in the x86](https://www.youtube.com/watch?v=jkGZDb3100Q)
- [Modern Page Tables: Multi-Level Paging](https://www.youtube.com/watch?v=pCgw4Pe-5jo)

### BSD Source Code

- [OpenBSD](https://github.com/openbsd/src)
- [FreeBSD](https://github.com/freebsd/freebsd-src)
- [NetBSD](https://github.com/NetBSD/src)
- [Minix (3.1.8 latest without NetBSD userland)](https://github.com/Stichting-MINIX-Research-Foundation/minix/tree/R3.1.8)

### RISCV

- [Boot sequence: riscv-linux-boot](https://github.com/ultraembedded/riscv-linux-boot)
