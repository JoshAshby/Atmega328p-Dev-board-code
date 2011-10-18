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
This bit-o-code is a basic thread style system, without threads.
What it does is runs one task at a time. This way code ban be
broken up into single b

*/

void kernel_init(void) {
    //first we have to get the timer up and running, it'll run at 16MHz and the ISR
    //will happen everytime it overflows
    TCNT0 = 0; //set the inital timer value to 0
    TCCR0B |= (1<<CS00); //system clock speed
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
    
    simply copy the style below and increment the number
    and replace threadX with the name of your new thread
    */
    kernel_stack.task_list[0] = &thread0;
    kernel_stack.task_list[1] = &thread1;
    kernel_stack.task_list[2] = &thread2;
    kernel_stack.task_list[3] = &thread3;

    //bootstrap the process and start the first thread
    kernel_stack.task_number = 0;
    kernel_stack.task_status[0] = kernel_stack.task_list[0]();
}

/*
Everytime the timer overflows we need to go through the list of threads
and see which ones haven't ran yet. The next one in line to run is ran,
and the global counter is increased. If all the task have completed, loop
back to the begining by clearing the status array.
*/
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
can't write blocking code, or else it'll block the whole thread system
(which is a super bad no-no)
*/
ISR(TIMER0_OVF_vect) {
    kernel();
}

