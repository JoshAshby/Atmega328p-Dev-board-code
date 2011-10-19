//-------------------------------------------
/*
THREAD.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

uint8_t thread0(void) {
    pwm1A(ADCH);
    #if DEBUG_KERNEL
        uart_sendint(THREAD0_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x20 - THREAD0 is up...");
        #endif
    #endif
    return 1;
}

uint8_t thread1(void) {
    if((PINB  & 0b00000001)) {
        out('B', OUT1, 0);
    } else {
        out('B', OUT1, 1);
    }
    #if DEBUG_KERNEL
        uart_sendint(THREAD1_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x21 - THREAD1 is up...");
        #endif
    #endif
    return 1;
}

uint8_t thread2(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD2_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x22 - THREAD2 is up...");
        #endif
    #endif
    return 1;
}

uint8_t thread3(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD3_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x23 - THREAD3 is up...");
        #endif
    #endif
    return 1;
}
