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

/*
Drive motor control thread
This guy runs once in a while just to make sure BOB is moving
(or attempting to). The priority doesn't need to be too high
because  worse case you just pull the power (or one of the few
fuses or relays pop).
*/
uint8_t thread0(void) {
    pwm1A(led);
    #if DEBUG_KERNEL
        uart_sendint(THREAD0_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x20 - THREAD0 is up...");
        #endif
    #endif
    #if !KERNEL_COOP
        kernel_stack.task_lock[0] = 0;
    #endif
    kernel_stack.task_status[0] = 1;
    return 1;
}

/*
Turn motor control thread
This guy takes care of controlling the turning motor and it's
dirrection switching relay. If the ultrasound thread sets the
turn bit (which may end up being this threads flag) then he
is ran immediatly because that means BOB needs to turn, and
that should perferably happen sooner than later.
*/
uint8_t thread1(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD1_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x21 - THREAD1 is up...");
        #endif
    #endif
    #if !KERNEL_COOP
        kernel_stack.task_lock[1] = 0;
    #endif
    kernel_stack.task_status[1] = 1;
    return 1;
}

/*
This guy is the ultrasound thread. He'll get most of the
attention because he's an important thread to run, making sure
BOB doesn't run into anything.
*/
uint8_t thread2(void) {
    while(1) {
        NULL;
    }
    #if DEBUG_KERNEL
        uart_sendint(THREAD2_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x22 - THREAD2 is up...");
        #endif
    #endif
    #if !KERNEL_COOP
        kernel_stack.task_lock[2] = 0;
    #endif
    kernel_stack.task_status[2] = 1;
    return 1;
}

/*
Temperature control thread. This guy monitors the resistance
of a thermocoupler on the back motor MOSFETs and converts it to
degrees. In robot.h you can define what the temperature is for
when the fan turns on to keep the MOSFETs cool. (In C, not F or K)
*/
uint8_t thread3(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD3_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x23 - THREAD3 is up...");
        #endif
    #endif
    #if !KERNEL_COOP
        kernel_stack.task_lock[3] = 0;
    #endif
    kernel_stack.task_status[3] = 1;
    return 1;
}


/*
NULL thread, also known as the idle thread. Basically it
removes its lock then runs a null loop for the processor
until another task is ran
*/
uint8_t thread4(void) {
    #if !KERNEL_COOP
        kernel_stack.task_lock[4] = 0;
    #endif
    while(1) {
        NULL;
    }
    #if DEBUG_KERNEL
        uart_sendint(THREAD4_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x23 - THREAD3 is up...");
        #endif
    #endif
    kernel_stack.task_status[4] = 1;
    return 1;
}
