#include "printf.h"
#include "vga.h"


//sign is 0 for unsigned int, 1 for signed int
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

static void print_hex(uint32_t num){
    char digits[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

    print("0x");
    int i;
    for (i = 7; i >= 0; i--){

        uint8_t index = (num >> (4*i)) & 0xf;
        putc(digits[index]);


    }





}


void __attribute__((cdecl)) printf(const char* fmt, ...){

    uint32_t* arg = (uint32_t*)&fmt;
    arg ++;

    while (*fmt){
        switch (*fmt){

            case '%':
                fmt ++;
                switch (*fmt){
                    case 'u':
                        print_unsigned(*arg);
                        arg ++;
                    break;

                    case 'd':
                        print_signed((int32_t)*arg);
                        arg ++;
                    break;

                    case 's':
                        print((const char*)*arg);
                        arg ++;
                    break;

                    case 'c':
                        putc((char)(*arg));
                        arg ++;
                    break;

                    case 'x':
                        print_hex(*arg);
                        arg++;
                    break;
            }
            break;
            default:
                putc(*fmt);

        }

        fmt ++;

    }

}
