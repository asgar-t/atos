#pragma once
#include "util.h"

void initKeyboard();
void keyboard_handler(interrupt_registers* regs);
uint32_t read_char_from_buffer();
