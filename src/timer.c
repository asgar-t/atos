#include "timer.h"
#include "stdint.h"
#include "idt/idt.h"
#include "vga.h"

uint64_t ticks;
const uint32_t freq = 100;

void initTimer(){

    ticks = 0;
    irq_install_handler(0, onIRQ0);

    uint32_t divisor = 1193182/freq; //frequency in Hz (rounding)

    outPortB(0x43, 0x36);
    outPortB(0x40 , (uint8_t)(divisor & 0xff));
    outPortB(0x40, (uint8_t)((divisor >> 8) & 0xff));



}
void onIRQ0(interrupt_registers* regs){
    ticks ++;

    //print ("TIMER TICKED");


}
