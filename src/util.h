#pragma once
#include "stdint.h"

//useful functions

void memset(void* dest, char val, uint32_t count); //sets a chunk of memory

//controls ports, write a byte to a port, or read from a port
void outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port);

//struct containing all the registers, used for interrupts
typedef struct interrupt_registers{
    uint32_t cr2, ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, int_no, err_code, eip, csm, eflags, useresp, ss;

}interrupt_registers;
