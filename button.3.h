//-------------------------------------------
/*
THREAD.h
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef THREAD_H
#define THREAD_H
#include "global.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------

//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t dig_count[1];

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------
typedef void (*button_ptr)(void);
button_ptr button_array[1];

//-----------------------------------------------
//Prototypes
//-----------------------------------------------

void init_debounce(void);

#endif

