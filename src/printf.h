#pragma once

//own printf function, this one was definitely fun to write as it was the first function
//i wrote that has unknown arguments so you have to make use of a pointer to the stack, which I will highlight in the
//documentation in printf.c

//only %d (signed), %u, %c, and %s
void __attribute__((cdecl)) printf(const char* fmt, ...);
