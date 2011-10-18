//-------------------------------------------
/*
KERNEL.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

/*
This bit code (that will be written) will be like a basic RTOS
and threads. It will keep track of several tasks, only letting
them complete one instruction at a time, and rotates through each task
In a way making the chip appear to multitask.

First we need to get timer one going, it will use the overflow interrupt to
run a bit of code that determins if a task is finished and if a new one should be started.

*/

void kernel_init(void) {
    //first we have to get the timer up and running, it'll run at 16MHz and the ISR
    //will happen everytime it overflows
    TCNT0 = 0; //set the inital timer value to 0
    TCCR0B |= (1<<CS00);
    TIMSK0 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on
    sei();

    #if DEBUG
        uart_sendint(KERNEL_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x15 - KERNEL is setup...");
        #endif
    #endif

    /*
    This is where you declare new threads
    
    simply copy the 
    */
    kernel_stack.task_list[0] = &thread0;
    kernel_stack.task_list[1] = &thread1;
    kernel_stack.task_list[2] = &thread2;
    kernel_stack.task_list[3] = &thread3;

    kernel_stack.task_number = 0;
    kernel_stack.task_status[0] = kernel_stack.task_list[0]();
}

void kernel(void) {
    uint8_t task;
    task = kernel_stack.task_number;
    if(task >= NUMBER_OF_THREADS) {
        task = 0;
        uint8_t tmp;
        for(tmp; tmp >= NUMBER_OF_THREADS; tmp++) {
            kernel_stack.task_status[tmp] = 0;
        }
    }
    if(kernel_stack.task_status[task]) {
        task = task + 1;
        kernel_stack.task_status[task] = kernel_stack.task_list[task]();
    }
    kernel_stack.task_number = task;
}

/*
Every time there is an overflow of the timer, the kernel core is called
which will go through and switch tasks or "threads" if the current one is complete.
If it's not done, nothing is done. This means that currently one
can't write blocking code, or else it'll block the whole thread system (which is a super bad no-no)
*/
ISR(TIMER0_OVF_vect) {
    kernel();
}

