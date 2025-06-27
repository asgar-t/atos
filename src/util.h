#pragma once
#include "stdint.h"

void memset(void* dest, char val, uint32_t count);
void outPortB(uint16_t port, uint8_t value);
char inPortB(uint16_t port);

typedef struct interrupt_registers{
    uint32_t cr2, ds, edi, esi, ebp, esp, ebx, edx, ecx, eax, int_no, err_code, eip, csm, eflags, useresp, ss;

}interrupt_registers;
