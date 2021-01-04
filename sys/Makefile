TOP=..
include $(TOP)/mk/tunix.config.mk
include arch/$(ARCH)/make/arch.mk

CC_SRC  += $(wildcard kernel/*.c sys/*.c driver/*.c arch/$(ARCH)/$(ARCH)/*.c)
CXX_SRC += $(wildcard kernel/*.cc sys/*.cc driver/*.cc arch/$(ARCH)/$(ARCH)/*.cc)
HEADERS += $(wildcard kernel/*.h sys/*.h driver/*.h arch/$(ARCH)/$(ARCH)/*.h)

OBJ += arch/$(ARCH)/$(ARCH)/interrupt.o
OBJ += $(CC_SRC:.c=.o)
OBJ += $(CXX_SRC:.cc=.o)

.PHONY: all
all: machine $(IMAGE).bin $(KERNEL).bin $(KERNEL).elf

machine:
	ln -s arch/$(ARCH)/include $(TOP)/sys/$@

$(IMAGE).bin: arch/$(ARCH)/$(ARCH)/bootsect.bin $(KERNEL).bin
	cat $^ > $(IMAGE).bin

$(KERNEL).bin: arch/$(ARCH)/$(ARCH)/kernel_entry.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ -Ttext 0x1000 $^ --oformat binary

$(KERNEL).elf: arch/$(ARCH)/$(ARCH)/kernel_entry.o $(OBJ)
	$(LD) $(LDFLAGS) -o $@ -Ttext 0x1000 $^

include $(TOP)/mk/tunix.compile.mk

.PHONY: clean
clean:
	rm -f machine
	rm -rf *.bin *.dis *.o $(IMAGE).bin *.elf
	rm -rf kernel/*.o sys/*.o driver/*.o arch/$(ARCH)/$(ARCH)/*.o arch/$(ARCH)/$(ARCH)/*.bin
