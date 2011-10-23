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
What it does is runs one task at a time. This way code can be
broken up into single blocks (which don't block, and only need
to be ran once). It allows for a bit more organization I think,
and allows you to make programs which do not need to run in total
sequential order.

Task killing and
*/

void init_kernel(void) {
    //first we have to get the timer up and running, it'll run at 2MHz and the ISR
    //will happen everytime it overflows
    TCNT0 = 0; //set the inital timer value to 0
    TCCR0B |= (1<<CS02) | (1<<CS01); //system clock speed
    TIMSK0 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on

    #if DEBUG
        uart_sendint(KERNEL_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x15 - KERNEL is up...");
        #endif
    #endif

    /*
    This is where you declare new threads

    simply copy the style below and increment the number
    and replace threadX with the name of your new thread
    */
    #if KERNEL_COOP
        kernel_stack.task_list[0] = &thread0;
        kernel_stack.task_list[1] = &thread1;
        kernel_stack.task_list[2] = &thread2;
        kernel_stack.task_list[3] = &thread3;
        kernel_stack.task_list[4] = &thread4;
    #endif
    //If we're not in linear kernel mode, order the tasks by priority so we can just run down the array
    //when we need to and pick out the flagged tasks.
//    #if !KERNEL_COOP
//        kernel_stack.task_list[0] = &thread0;
//        kernel_stack.task_list[1] = &thread1;
//        kernel_stack.task_list[2] = &thread2;
//        kernel_stack.task_list[3] = &thread3;
//        kernel_stack.task_list[4] = &thread4;
//    #endif

    //bootstrap the process and start the first thread
    kernel_stack.task_number = 0;
    goto *kernel_stack.task_list[0];
}

/*
Everytime the timer overflows we need to go through the list of threads
and see which ones haven't ran yet. The next one in line to run is ran,
and the global counter is increased. If all the task have completed, loop
back to the begining by clearing the status array.
*/
void kernel_core(void) {
    cli();
    #if KERNEL_COOP
        uint8_t task;
        task = kernel_stack.task_number;
        if(task >= NUMBER_OF_THREADS) {
            for(task = 0; task <= NUMBER_OF_THREADS; task++) {
                kernel_stack.task_status[task] = 0;
            }
            task = 0;
            kernel_stack.task_number = task;
            goto *kernel_stack.task_list[task];
        }
        if(kernel_stack.task_status[task]) {
            task += 1;
            kernel_stack.task_number = task;
            goto *kernel_stack.task_list[task];
        } else {
            kernel_stack.task_timer++;
            if(kernel_stack.task_timer >= THREAD_COUNT) {
                kernel_stack.task_status[task] = 1;
                task += 1;
                kernel_stack.task_timer = 0;
                kernel_stack.task_number = task;
                goto *kernel_stack.task_list[task];
            }
            return;
        }
    #endif

    #if DEBUG_KERNEL
        uart_sendint(KERNEL_CORE_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x16 - KERNEL is up...");
        #endif
    #endif
    sei();
    return;
}

/*
Every time there is an overflow of the timer, the kernel core is called
which will go through and switch tasks or "threads" if the current one is complete.
If it's not done, nothing is done. This means that currently one
can't write blocking code, or else it'll block the whole thread system
(which is a super bad no-no)
*/
ISR(TIMER0_OVF_vect) {
    kernel_core();
    return;
}
