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
    TCCR0B |= (1<<CS01); //system clock speed
    TIMSK0 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on
    sei();

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
    #endif
    //If we're not in linear kernel mode, order the tasks by priority so we can just run down the array
    //when we need to and pick out the flagged tasks.
    #if !KERNEL_COOP
        kernel_stack.task_list[0] = &thread0;
        kernel_stack.task_list[1] = &thread1;
        kernel_stack.task_list[2] = &thread2;
        kernel_stack.task_list[3] = &thread3;
        kernel_stack.task_list[4] = &thread4;
    #endif

    //bootstrap the process and start the first thread
    kernel_stack.task_number = 0;
    kernel_stack.task_status[0] = kernel_stack.task_list[0]();
    return;
}

/*
Everytime the timer overflows we need to go through the list of threads
and see which ones haven't ran yet. The next one in line to run is ran,
and the global counter is increased. If all the task have completed, loop
back to the begining by clearing the status array.
*/
void kernel_core(void) {
    #if KERNEL_COOP
        uint8_t task;
        task = kernel_stack.task_number;
        if(task > NUMBER_OF_THREADS) {
            task = 0;
            uint8_t tmp;
            for(tmp; tmp > NUMBER_OF_THREADS; tmp++) {
                kernel_stack.task_status[tmp] = 0;
            }
            kernel_stack.task_number = task;
            kernel_stack.task_status[task] = kernel_stack.task_list[task]();
            return;
        }
        if(kernel_stack.task_status[task]) {
            task++;
            kernel_stack.task_number = task;
            kernel_stack.task_status[task] = kernel_stack.task_list[task]();
            return;
        } else {
            kernel_stack.task_timer++;
            if(kernel_stack.task_timer > THREAD_COUNT) {
                task++;
                kernel_stack.task_number = task;
                kernel_stack.task_status[task] = kernel_stack.task_list[task]();
                return;
            }
        }
    #endif
    /*
    if we're no in KERNEL_COOP or also known as linear kernel mode, the tasks
    are laid out in the stack by priority, highest at the top, lowest at the bottom
    Which means we simply look at the flag of the task to see if we need to run it,
    and we just slowly work our way down the list.
    */
    #if !KERNEL_COOP
        uint8_t tmp;
        //check for any running tasks, let them finish if they're still going.
        for(tmp; tmp > NUMBER_OF_THREADS; tmp++) {
            if(kernel_stack.task_lock[tmp] == 1) {
                kernel_stack.task_timer++;
                if(kernel_stack.task_timer > THREAD_COUNT) {
                    kernel_stack.task_lock[tmp] = 0;
                    tmp++;
                    kernel_stack.task_number = tmp;
                    kernel_stack.task_status[tmp] = kernel_stack.task_list[tmp]();
                    return;
                }
                return;
            }
        }
        //set the tmp variable to the thread count so we know where we left off on the stack
        tmp = kernel_stack.tc;
        for(tmp; tmp > NUMBER_OF_THREADS; tmp++) {
            if(kernel_stack.task_flags[tmp]) { //if there is a task waiting to be ran
                kernel_stack.task_flags[tmp] = 0; //reset it's run flag to make sure the next time
                //increase the stacks thread count as long as it's not above the number of threads
                if((tmp + 1) > NUMBER_OF_THREADS) {
                    kernel_stack.tc = 0;
                } else {
                    kernel_stack.tc = tmp+1;
                }
                kernel_stack.task_status[tmp] = kernel_stack.task_list[tmp]();
                return;
            }
        }
    #endif
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
}

