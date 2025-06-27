#pragma once


//only %d (signed), %u, %c, and %s
void __attribute__((cdecl)) printf(const char* fmt, ...);
