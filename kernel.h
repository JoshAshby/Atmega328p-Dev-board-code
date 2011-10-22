//-------------------------------------------
/*
KERNEL.h
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef KERNEL_H
#define KERNEL_H
#include "global.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------
#define KERNEL_COOP 1

#if KERNEL_COOP
    #define NUMBER_OF_THREADS 4
#endif
#if !KERNEL_COOP
    #define NUMBER_OF_THREADS 5
#endif

#define THREAD_SECONDS 2
#define THREAD_COUNT (THREAD_SECONDS * 2000000)

//-----------------------------------------------
//Variables
//-----------------------------------------------

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------
typedef uint8_t (*thread_ptr)(void); //function pointer so we can store the function inside of the kernel_stack

struct kstack {
    thread_ptr task_list[NUMBER_OF_THREADS];
    uint8_t task_status[NUMBER_OF_THREADS];
    float task_timer;
    #if !KERNEL_COOP
        uint8_t task_flags[NUMBER_OF_THREADS];
        uint8_t task_lock[NUMBER_OF_THREADS];
    #endif
    uint8_t task_number;
} kernel_stack; //the kernel stack that holds the function pointers for each thread and the

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void init_kernel(void);
void kernel_core(void);

#endif
