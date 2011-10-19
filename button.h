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
#define DEBOUNCE_TIME 10

//-----------------------------------------------
//Variables
//-----------------------------------------------
uint8_t dig_count[2];
uint8_t once[2];

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
void button(char which, char what);
void button1_once(void);
void check_buttons(void);
void init_buttons(void);

#endif

