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
//sub section
//========================


//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t kernel_count;
uint8_t thread_status;
int task_num;
_Bool kernel_run;

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------
typedef uint8_t (*thread)(void);
typedef struct {
    uint8_t task_status;
    uint8_t task_num;
    thread task_list[4];
} stack;

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void kernel(char what_to_do);
uint8_t thread0(void);
uint8_t thread1(void);
uint8_t thread2(void);
uint8_t thread3(void);

#endif
