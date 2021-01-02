# tunix

Unix like toy operating system.

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

See [sys/arch/template/README.md](sys/arch/template/README.md) for details on platforms specific code.

## Resources

- [github.com/cfenollosa/os-tutorial](https://github.com/cfenollosa/os-tutorial)
- [FreeBSD Kernel Internals, Dr. Marshall Kirk McKusick](https://www.youtube.com/watch?v=nwbqBdghh6E)
