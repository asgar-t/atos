#include "stdint.h"
#include "memory.h"
#include "printf.h"

#define  MMAP_ENTRY_SIZE sizeof(struct multiboot_mmap_entry)

void initMemory(multiboot_info* boot_info){

    int i;
    for (i = 0; i < boot_info->mmap_length; i+= MMAP_ENTRY_SIZE){

        struct multiboot_mmap_entry* cur_entry = (struct multiboot_mmap_entry*)(boot_info->mmap_addr + i);

        printf("low adr: %x | high adr: %x | low len: %x | high len: %x | size: %x | type: %d\n", cur_entry->addr_low, cur_entry->addr_high, cur_entry->len_low, cur_entry->len_high, cur_entry->size, cur_entry->type);




    }















}
