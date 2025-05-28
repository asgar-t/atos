#include "vga.h"
#include "gdt.h"
#include "idt/idt.h"
void kmain(void);


void kmain(void){
    Reset();
    print("HELLdiwau90duaw90du90a\n");
    print("yo\n");

    gdt_init();

    print("worked!!\n");

    idt_init();

    print("IDT INITIALIZED\n\n testing divide by 0\n\n");

    int x = 5/0;




}
