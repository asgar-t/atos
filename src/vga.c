#include "vga.h"
#include "stdint.h"

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const)(0xb8000);
const uint16_t default_color = (COLOR8_LIGHT_GREY << 8) | (COLOR8_BLACK << 12);
uint16_t current_color = default_color;


void Reset(){

    line  = 0;
    column = 0;
    current_color = default_color;

    uint16_t y;
    uint16_t x;

    for (y = 0;y < HEIGHT; y++){
        for(x = 0;x < WIDTH; x++){

            vga[y*WIDTH + x] = ' ' | default_color;
        }

    }

}


void newLine(){

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
    }

    for(x = 0; x<WIDTH; x++){
        vga[(HEIGHT-1)*WIDTH + x] = ' ' | current_color;

    }
}


void print(const char* s){
    while (*s){
        switch(*s){
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
                vga[line*WIDTH + column] = *s | current_color;
                column ++;
                break;
        }
        s++;
    }



}

