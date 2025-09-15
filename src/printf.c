#include "printf.h"
#include "vga.h"


//helper function for printf, will print an unsigned number in decimanl
static void print_unsigned(uint32_t num){
    //max number is 10 digits long
    char number_to_print[] = "0000000000";
    uint8_t pos = 10;

    while (num && pos){
        number_to_print[pos -1] = '0' + (num % 10);
        num /= 10;
        pos --;
    }

    print(number_to_print);
}


//same as above, prints signed numbers thouh
static void print_signed(int32_t num){

    if (num < 0){
        num *= -1;
        putc('-');
    }
    char number_to_print[] = "0000000000";
    uint8_t pos = 10;

    while (num && pos){
        number_to_print[pos -1] = '0' + (num % 10);
        num /= 10;
        pos --;
    }

    print(number_to_print);

}


//prints a hex number
static void print_hex(uint32_t num){
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    print("0x");
    int i;
    for (i = 7; i >= 0; i--){

        uint8_t index = (num >> (4*i)) & 0xf;
        putc(digits[index]);


    }





}


//main printf function
void __attribute__((cdecl)) printf(const char* fmt, ...){

    //this is the pointer to the argument on the stack, this was super cool to do, I had no idea you could do this until 
    //writing this function. Very cool how it makes use of the location of where this argument is in memory, we can just increment it
    //to get the next arguemnts!!
    uint32_t* arg = (uint32_t*)&fmt;
    arg ++; //increment to get first argument

    while (*fmt){ //iterate through string
        switch (*fmt){

            case '%': //we know we are going to have some format thing, so we increment to see what it is
                fmt ++;
                switch (*fmt){
                    case 'u': //unsigned number, so we just print it and go to the next argument
                        print_unsigned(*arg);
                        arg ++;
                    break;

                    case 'd': //same as above but for signed
                        print_signed((int32_t)*arg);
                        arg ++;
                    break;

                    case 's': //string, use print function in vga.h to print the argument.
                        //arg points to memory on the stack, the memory is the pointer to the string, so we need to pass *arg to print
                        print((const char*)*arg);
                        arg ++;
                    break;

                    case 'c': //simple enough, same as above but for char
                        putc((char)(*arg));
                        arg ++;
                    break;

                    case 'x': //hex! same as integers and whatnot but in hex
                        print_hex(*arg);
                        arg++;
                    break;
            }
            break;
            default:
                putc(*fmt); //put a normal character since there is no '%', so it is just part of the string

        }

        fmt ++; //next char

    }

}
