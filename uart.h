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
#include <avr/sleep.h>

#define BAUD 9600
#define BUFF_LEN 700

void uart_start(void);
void uart_send(uint8_t data);
uint8_t uart_get(void);

char input_buffer[BUFF_LEN];

uint16_t read_spot;


#endif


