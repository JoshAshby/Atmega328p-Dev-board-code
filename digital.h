//-------------------------------------------
/*
DIGITAL.h
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef DIGITAL_H
#define DIGITAL_H
#include "global.h"

void portB_out(int pin, _Bool value);
void portD_out(int pin, _Bool value);
void out(char port, int pin, _Bool value);
#endif
