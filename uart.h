//-------------------------------------------
/*
uart.h
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD 9600

void uart_start(void);
void uart_send(char *data);

char getByte;


#endif


