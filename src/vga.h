#pragma once
#include "stdint.h"

#define COLOR8_BLACK 0
#define COLOR8_LIGHT_GREY 7

#define WIDTH 80
#define HEIGHT 25


void print(const char*s);
void putc(const char c);
void scrollUp();
void newLine();
void Reset();
