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
#ifndef BUTTON_H
#define BUTTON_H
#include "global.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------

//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t dig_count[4];

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void button(char which, char what);
void check_buttons(void);
void init_buttons(void);

#endif

