BITS 32
MBOOT_PAGE_ALIGN EQU 1
MBOOT_MEM_INFO EQU 1 << 1
MBOOT_USE_GFX EQU 0

MBOOT_MAGIC EQU 0x1badb002
MBOOT_FLAGS EQU MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_USE_GFX
MBOOT_CHECKSUM EQU -(MBOOT_MAGIC + MBOOT_FLAGS)

section .multiboot

ALIGN 4
    dd MBOOT_MAGIC
    dd MBOOT_FLAGS
    dd MBOOT_CHECKSUM
    dd 0, 0, 0, 0, 0

    dd 0
    dd 800
    dd 600
    dd 32


section .bss
ALIGN 16
stack_bottom:
    RESB 16384 * 8
stack_top:

section .boot

global _start
_start:

    mov ecx, (initial_page_dir - 0xc0000000)
    mov cr3, ecx

    mov ecx, cr4
    or ecx, 0x10
    mov cr4, ecx

    mov ecx, cr0
    or ecx, 0x80000000
    mov cr0, ecx

    jmp higher_half

section .text
higher_half:
    mov esp, stack_top
    push ebx
    push eax
    xor ebp, ebp
    extern kmain
    call kmain

halt:
    hlt
    jmp halt



section .data
ALIGN 4096
global initial_page_dir
initial_page_dir:
    dd 10000011b
    times 767 dd 0

    dd (0 << 22) | 10000011b
    dd (1 << 22) | 10000011b
    dd (2 << 22) | 10000011b
    dd (3 << 22) | 10000011b

    times 252 dd 0






