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
    cli();
    #if KERNEL_COOP
        uint8_t task;
        task = kernel_stack.task_number;
        if(task >= NUMBER_OF_THREADS) {
            for(task = 0; task >= NUMBER_OF_THREADS; task++) {
                kernel_stack.task_status[task] = 0;
            }
            task = 0;
            kernel_stack.task_number = task;
            kernel_stack.task_list[task]();
            return;
        }
        if(kernel_stack.task_status[task]) {
            task += 1;
            kernel_stack.task_number = task;
            kernel_stack.task_list[task]();
            return;
        } else {
            kernel_stack.task_timer++;
            if(kernel_stack.task_timer >= THREAD_COUNT) {
                kernel_stack.task_status[task] = 1;
                task += 1;
                kernel_stack.task_timer = 0;
                kernel_stack.task_number = task;
                kernel_stack.task_list[task]();
                return;
            }
            return;
        }
    #endif
    /*
    if we're not in KERNEL_COOP mode, then we are to act like a preemptive scheduler.
    this means we check for task that has a flag ubit set, meaning the task wants to run
    This flag is typically set from an outside source such as an interrupt.

    So what we need to do in order is this: look for a lock bit which means a task
    is still running, if there is a lock bit then let it task run and increase the
    kernel counter . if the counter excedes it's declared value (set by changing KERNEL_SECONDS
    for how many seconds a task has to run before it's declared dead) then the tasks
    ock bit is cleared, the task counter is increased by one, and the next task in
    the stack runs, setting it's lock bit.

    When all this is done and there isn't a running task with it's lock bit set
    then we run from where we left off in the stack last time through and work our way
    down the stack. During this time we check for any tasks with their flag bit set,
    if there is a flag bit set then we run it. if there isn't a task with a flag
    bit set, we drop into thread4 which is a null idle loop until the kernel runs again.
    */
    #if !KERNEL_COOP
        uint8_t task;
        uart_sendstr("count");
        if(kernel_stack.task_number == 0) {
            task = kernel_stack.task_number;
        } else {
            task = kernel_stack.task_number - 1;
        }
        uart_sendint(task);
        //look for a lock
        if(kernel_stack.task_lock[task]) {
            uart_sendstr("lock");
            kernel_stack.task_timer++; //if there is a lock then increase the timer
            //if the timer is over it's alloted time
            if(kernel_stack.task_timer >= THREAD_COUNT) {
               kernel_stack.task_lock[task] = 0; //remove the tasks lock
               kernel_stack.task_timer = 0; //reset the timer
               if((task+1) >= (NUMBER_OF_THREADS-1)) {
                    kernel_stack.task_number = 0;
                } else {
                    kernel_stack.task_number = task+1; //increase the task counter for next run through
                }
               uart_sendstr("NULL");
               //drop into the null loop until the next time the kernel runs
               kernel_stack.task_status[4] = kernel_stack.task_list[4]();
               return;
            }
        }
        //run through the task flags and check for
        for(task = kernel_stack.task_number; task >= (NUMBER_OF_THREADS-1); task++) {
            uart_sendint(task);
            //if there is a flag set
            if(kernel_stack.task_flags[task]) {
                uart_sendstr("flag");
                if((task+1) >= (NUMBER_OF_THREADS-1)) {
                    kernel_stack.task_number = 0;
                } else {
                    kernel_stack.task_number = task+1; //increase the task counter for next run through
                }
                uart_sendint(task);
                kernel_stack.task_lock[task] = 1; //set the new tasks lock
                kernel_stack.task_status[task] = kernel_stack.task_list[task]();
                return;
            } else {
                kernel_stack.task_number = 0;
                uart_sendstr("NULL2");
                //drop into the null loop until the next time the kernel runs
               kernel_stack.task_status[4] = kernel_stack.task_list[4]();
               return;
            }
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

