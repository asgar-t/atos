#include "vga.h"
#include "gdt.h"
#include "idt/idt.h"
#include "timer.h"
#include "printf.h"
#include "keyboard.h"
#include "multiboot.h"
#include "memory.h"



void kmain(uint32_t magic, multiboot_info* boot_info){

    Reset();
    gdt_init();

    printf("GDT initialized \n");

    idt_init();

    printf("IDT INITIALIZED\n");

    initTimer();

	printf("%d\n %u", -100, -100);
    printf("%x\n", 31412);

    initKeyboard();

    //initMemory(boot_info);

    char c = 0;
    while (1){
        if(c = (char)read_char_from_buffer()){
            putc(c);
        }


    }



}
