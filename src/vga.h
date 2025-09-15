#pragma once
#include "stdint.h"

#define COLOR8_BLACK 0
#define COLOR8_LIGHT_GREY 7

#define WIDTH 80
#define HEIGHT 25


void print(const char*s); //prints a string
void putc(const char c); //prints a character
void scrollUp(); //moves screen up by one line
void newLine(); //new line when we reach the  end of the current one
void Reset(); //reset vga output to all black
