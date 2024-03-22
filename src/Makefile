#
# Author : Mayank Manohare <mayankmanohare7@gmail.com>
#

TOOLCHAIN_PREFIX ?= arm-none-eabi-
OBJCOPY           = $(TOOLCHAIN_PREFIX)objcopy
LD 				  = $(TOOLCHAIN_PREFIX)ld
AS 				  = $(TOOLCHAIN_PREFIX)as
GCC 			  = $(TOOLCHAIN_PREFIX)gcc

MACH = cortex-m4

CFLAGS = -O0 -ggdb -nostdlib -mcpu=$(MACH)
LDFLAGS = -T main.ld -Map=main.map
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
OUTPUT = main.elf

all: $(SRCS)
	$(GCC) $(CFLAGS) -c $^
	$(LD) $(LDFLAGS) $(OBJS) -o $(OUTPUT)
	$(OBJCOPY) -O binary $(OUTPUT) main.bin


debug: 
	qemu-system-arm -cpu cortex-m4 -machine netduinoplus2 -nographic -s -S -kernel main.elf

gdb: 
	gdb-multiarch main.elf -ex "target remote localhost:1234"

.PHONY: clean
clean:
	rm -rf *.o *.elf *.bin *.out .gdb_history *.map
