//-------------------------------------------
/*
DIGITAL.h
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef DIGITAL_H
#define DIGITAL_H
#include "global.h"

//-------------------------------------------
//Macros (defines)
//-------------------------------------------

//-------------------------------------------
//Prototypes
//-------------------------------------------
void out(char port, int pin, _Bool value);


//-------------------------------------------
//Variables
//-------------------------------------------
uint8_t dig_count[1];

#endif
