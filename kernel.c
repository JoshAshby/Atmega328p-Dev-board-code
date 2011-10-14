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

void kernel(char what_to_do) {
    stack kernel_stack;

    kernel_stack.task_list[0] = &thread0;
    kernel_stack.task_list[1] = &thread1;
    kernel_stack.task_list[2] = &thread2;
    kernel_stack.task_list[3] = &thread3;

    void move(void) {
       thread_status = 0;
        task_num++;
        if (task_num > 3) {
            task_num = 0;
        }
        kernel_stack.task_list[task_num]();
        #if DEBUG_KERNEL
            uart_sendint(task_num);
        #endif
    }

    switch (what_to_do) {
        case 'i':
            //first we have to get the timer up and running, it'll run at 16MHz and the ISR
            //will happen everytime it overflows
            TCNT0 = 0; //set the inital timer value to 0
            TCCR0B |= (1<<CS00);
            TIMSK0 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on
            sei();

            #if DEBUG
                uart_sendint(KERNEL_KEY);
                #if DEBUG_BEG
                    uart_sendstr("0x15 - KERNEL is up...");
                #endif
            #endif

            thread_status = 1;
            task_num = 3;
            kernel_run = 1;

            break;
        case 'm':
            move();
            break;
    }
}

uint8_t thread0(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD0_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x20 - THREAD0 is up...");
        #endif
    #endif
    thread_status = 1;
    return 1;
}

uint8_t thread1(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD1_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x21 - THREAD1 is up...");
        #endif
    #endif
    thread_status = 1;
    return 1;
}

uint8_t thread2(void) {
    #if DEBUG_KERNEL
        uart_sendint(THREAD2_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x22 - THREAD2 is up...");
        #endif
    #endif
    thread_status = 1;
    return 1;
}

uint8_t thread3(void) {
    while (1) {
        thread_status = 0;
    }
    #if DEBUG_KERNEL
        uart_sendint(THREAD3_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x23 - THREAD3 is up...");
        #endif
    #endif
    thread_status = 1;
    return 1;
}

/*
Every time there is an overflow of the timer, this gets called. It'll go through
and look at the task struct to figure out if the task needs to be switched or not.
If the task is still running, let it run, unless it's count has gone over 50 then switch
if the task is done the kernel_stack.task_status will be == 0x00 if not it'll have
the current task's KEY: IE: 0x02
*/
ISR(TIMER0_OVF_vect) {
    if (kernel_run) {
        if (thread_status == 1) {
            kernel('m');
            kernel_count = 0;
        } else {
            kernel_count++;
            #if DEBUG
                uart_sendint(kernel_count);
            #endif
            if (kernel_count > 5) {
                kernel('m');
                #if DEBUG
                    uart_sendstr("bad thread... forcing move...");
                #endif
            }
        }
    }
}

