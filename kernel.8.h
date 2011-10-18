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

//-----------------------------------------------
//Variables
//-----------------------------------------------

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------
typedef uint8_t (*thread)(void); //function pointer so we can store the function inside of the kernel_stack

struct {
    thread task_list[4];
    uint8_t task_status[4];
    uint8_t task_number;
} kernel_stack; //the kernel stack that holds the function pointers for each thread and the

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void init_kernel(void);
void kernel(void);
uint8_t thread0(void);
uint8_t thread1(void);
uint8_t thread2(void);
uint8_t thread3(void);

#endif
