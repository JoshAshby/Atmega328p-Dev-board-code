//-------------------------------------------
/*
MAIN.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

int main(void) { //Main loop, runs once but can have an infinit loop in it

    /*
    First we need to set the hardaware up, this is a macro in global.h which takes care of calling the various funtions that
    setup the registers to the proper seting, and also pulls the CPU_POW pin high
    if debug in GLOBAL.h is set, then debug keys will be sent out through the serial port
    when this function is called
    */
    bios();

    //if we're in debug mode, make sure you send stuff saying we got to the main code
    #if DEBUG
        uart_sendint(MAIN_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x6 - Main code checkpoint...");
        #endif
    #endif

    //button code, not called by the bios because the use oif this may vary
    DDRD |= (0<<button_one);
    init_debounce();

    //start the kernel and thread system. After this is going nothing else should happen in this
    //file because everything should be in the threads... hopefully.
    init_kernel();

    //infinit loop that doesn't stop running. (always true since 1 is always 1
    while(1) {
    };
    return 0; //never reached since 1 is always true
}
