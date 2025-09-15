#include "vga.h"
#include "stdint.h"
#include "util.h"

uint16_t column = 0; //column the cursor is on
uint16_t line = 0; //line the cursor is on

uint16_t* const vga = (uint16_t* const)(0xb8000); //pointer to vga buffer in memory

const uint16_t default_color = (COLOR8_LIGHT_GREY << 8) | (COLOR8_BLACK << 12); //flags for this font color/background color

uint16_t current_color = default_color; //we can add different color constants and change the current color in other use cases

//this is for using the backspace key, so that when we reach the beginning of the line, it does not go to the end of the previous line, instead if goes to the
//last character on the previous line
uint8_t last_cursor[HEIGHT];

//resets the screen
void Reset(){

    line  = 0;
    column = 0;
    current_color = default_color;

    //reset last_cursor data
    memset(&last_cursor, WIDTH, HEIGHT);

    uint16_t y;
    uint16_t x;

    //iterate through the pixels, reset to blank character
    for (y = 0;y < HEIGHT; y++){
        for(x = 0;x < WIDTH; x++){

            vga[y*WIDTH + x] = ' ' | default_color;
        }

    }

}



void newLine(){

    //store the cursor position
    last_cursor[line] = column;

    //go to new line if we are not tat the bottom
    if (line < HEIGHT -1){
        line ++;
        column = 0;
    }else{
        //move screen up
        scrollUp();
        column = 0;
    }

}


//moves the screen up
void scrollUp(){
    uint16_t y;
    uint16_t x;

    for (y = 0;y < HEIGHT - 1; y++){ //for all rows
        for(x = 0;x < WIDTH; x++){

            //sets each entry in a row to the entry right below it
            vga[y*WIDTH + x] = vga[(y+1)*WIDTH +x];
        }
        //scrolls the last_cursor data also, moving it all up one
        last_cursor[y] = last_cursor[y + 1];
    }
    last_cursor[y] = WIDTH;

    //makes last row blank
    for(x = 0; x<WIDTH; x++){
        vga[(HEIGHT-1)*WIDTH + x] = ' ' | current_color;

    }
}

void putc(const char c){

    switch (c){
        case '\b'://backspace
            if (line > 0){//if we are at the first character on any line that is not the first line, go up a line
                if (column == 0){
                    line --;
                    column = last_cursor[line];
                }
            }
            //if we are on the first character, do nothing, since we cant go behind the screen off limits
            
            if (column > 0){ //move back one space, make the previous cursor spot empty, and upate the entry in last_cursor
                column --;
                vga[line*WIDTH + column] = ' ' | current_color;
                last_cursor[line] = column;
            }
            break;
        case '\n':
                newLine(); //simple enough, just make a new line
                break;
            case '\r': //carraige return
                column = 0;
                break;
            case '\t': //tab, moves to the nearest multple of 4 spaces, aligns, instead of just putting 4 spaces
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
                //normal text characters
                if(column == WIDTH)
                    newLine(); //newline if at the end of line
                vga[line*WIDTH + column] = c | current_color; // set current cursor to the character, increment column val
                column ++;
                break;


    }

}


void print(const char* s){//print each character in the string
    while (*s){
        putc(*s);
        s++;
    }

}

