#include "gdt.h"
#include "util.h"

extern void gdt_flush(uint32_t);
extern void tss_flush();

gdt_entry gdt_entries[6];
gdt_ptr pgdt;
tss_entry_struct tss_entry;

void gdt_init(){
    pgdt.limit = (sizeof(gdt_entry)*6) -1;
    pgdt.base = (unsigned int)&gdt_entries;

    set_gdt_gate(0,0,0,0,0); //null
    set_gdt_gate(1,0,0xffffffff,0x9a,0xcf); //kernel code segment
    set_gdt_gate(2,0,0xffffffff,0x92,0xcf); //kernel data segment
    set_gdt_gate(3,0,0xffffffff,0xfa,0xcf); //user code segment
    set_gdt_gate(4,0,0xffffffff,0xf2,0xcf); //user data segment

    writeTSS(5, 0x10, 0x0);
    gdt_flush((unsigned int)&pgdt);
    tss_flush();
}

void set_gdt_gate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran){

    gdt_entries[num].base_low = (base & 0xffff);
    gdt_entries[num].base_middle = ((base >> 16 )& 0xff);
    gdt_entries[num].base_high = ((base >> 24)  & 0xff);

    gdt_entries[num].limit = (limit & 0xffff);
    gdt_entries[num].flags = ((limit >> 16) & 0x0f);
    gdt_entries[num].flags |= (gran & 0xf0);

    gdt_entries[num].access = access;


}

void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0){

    uint32_t base = (uint32_t)(&tss_entry);
    uint32_t limit = base + sizeof(tss_entry);


    set_gdt_gate(num, base, limit, 0xe9, 0x00);

    memset((void*)&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;
    tss_entry.cs = 0x08 | 0x03;
    tss_entry.cs = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x03;


}
