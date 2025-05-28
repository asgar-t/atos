ASM = nasm
CC = gcc
CCFLAGS = -m32 -fno-stack-protector -fno-builtin -c
ASM_FLAGS = -f elf32
src_dir = src
build_dir = build
target_dir = atos/boot
LINKER = ld
LINKER_FILE = linker.ld
LINKER_FLAGS = -m elf_i386 -T $(LINKER_FILE)

.PHONY: all

all: $(build_dir)/atos.iso

$(build_dir)/atos.iso: $(build_dir)/boot.o $(build_dir)/main.o $(build_dir)/vga.o $(build_dir)/gdt.o  $(build_dir)/gdts.o $(build_dir)/utils.o $(build_dir)/idt.o $(build_dir)/idts.o
	$(LINKER) $(LINKER_FLAGS) -o $(target_dir)/kernel $^
	grub-mkrescue -o $(build_dir)/atos.iso atos/

$(build_dir)/boot.o: $(src_dir)/boot.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

$(build_dir)/gdts.o: $(src_dir)/gdt.asm
	$(ASM) $(ASM_FLAGS) $< -o $@

$(build_dir)/main.o: $(src_dir)/kernel.c
	$(CC) $(CCFLAGS) $< -o $@

$(build_dir)/vga.o: $(src_dir)/vga.c
	$(CC) $(CCFLAGS) $< -o $@

$(build_dir)/gdt.o: $(src_dir)/gdt.c
	$(CC) $(CCFLAGS) $< -o $@

$(build_dir)/utils.o: $(src_dir)/util.c
	$(CC) $(CCFLAGS) $< -o $@

$(build_dir)/idt.o: $(src_dir)/idt/idt.c
	$(CC) $(CCFLAGS) $< -o $@

$(build_dir)/idts.o: $(src_dir)/idt/idt.asm
	$(ASM) $(ASM_FLAGS) $< -o $@


run:
	qemu-system-i386 $(build_dir)/atos.iso

