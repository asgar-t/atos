BITS 32


section .text

    ALIGN 4
    DD 0x1badb002
    dd 0x00000000
    DD -(0x1badb002 + 0x00000000)


global start
extern kmain


start:
    cli
    mov esp, stack_space
    call kmain

    hlt

halt_kernel:
    cli
    hlt
    jmp halt_kernel



section .bss
RESB 8192
stack_space:
