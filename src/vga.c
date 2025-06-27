#include "vga.h"
#include "stdint.h"
#include "util.h"

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const)(0xb8000);
const uint16_t default_color = (COLOR8_LIGHT_GREY << 8) | (COLOR8_BLACK << 12);
uint16_t current_color = default_color;
uint8_t last_cursor[HEIGHT];

void Reset(){

    line  = 0;
    column = 0;
    current_color = default_color;
    memset(&last_cursor, WIDTH, HEIGHT);

    uint16_t y;
    uint16_t x;

    for (y = 0;y < HEIGHT; y++){
        for(x = 0;x < WIDTH; x++){

            vga[y*WIDTH + x] = ' ' | default_color;
        }

    }

}


void newLine(){

    last_cursor[line] = column;

    if (line < HEIGHT -1){
        line ++;
        column = 0;
    }else{
        scrollUp();
        column = 0;
    }

}

void scrollUp(){
    uint16_t y;
    uint16_t x;

    for (y = 0;y < HEIGHT - 1; y++){
        for(x = 0;x < WIDTH; x++){

            vga[y*WIDTH + x] = vga[(y+1)*WIDTH +x];
        }
        last_cursor[y] = last_cursor[y + 1];
    }
    last_cursor[y] = WIDTH;

    for(x = 0; x<WIDTH; x++){
        vga[(HEIGHT-1)*WIDTH + x] = ' ' | current_color;

    }
}
void putc(const char c){

    switch (c){
        case '\b':
            if (line > 0){
                if (column == 0){
                    line --;
                    column = last_cursor[line];
                }
            }
            if (column > 0){
                column --;
                vga[line*WIDTH + column] = ' ' | current_color;
                last_cursor[line] = column;
            }
            break;
        case '\n':
                newLine();
                break;
            case '\r':
                column = 0;
                break;
            case '\t':
                if (column == WIDTH)
                    newLine();
                uint16_t tabLen = 4 - (column % 4);
                while (tabLen!= 0){
                    vga[line*WIDTH + column] = ' ' | current_color;
                    column ++;
                    tabLen --;
                }
                break;
            default:
                if(column == WIDTH)
                    newLine();
                vga[line*WIDTH + column] = c | current_color;
                column ++;
                break;


    }

}


void print(const char* s){
    while (*s){
        putc(*s);
        s++;
    }

}

