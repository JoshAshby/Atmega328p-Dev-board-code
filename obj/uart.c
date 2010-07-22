//-------------------------------------------
/*
uart.c
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "adc.h"
#include "pwm.h"
#include "global.h"
#include "i2c.h"
#include "uart.h"

//code examples stolen from the atmega328 datasheet, don't know if they work or not...probably not in their current state

void uart_start(void) {
  UBRR0H = (((F_CPU/BAUD)/16)-1)>>8;	// set baud rate
  UBRR0L = (((F_CPU/BAUD)/16)-1);
  UCSR0B = (1<<RXEN0)|(1<<TXEN0); 		 // enable Rx & Tx
  UCSR0C=  (1<<UCSZ01)|(1<<UCSZ00);  	        // config USART; 8N1
}

void uart_transmit(unsigned char data) {
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    /* Put data into buffer, sends the data */
    UDR0 = data;
}

unsigned char uart_receive(void) {
    /* Wait for data to be received */
    while (!(UCSR0A & (1<<RXC0)));
    /* Get and return received data from buffer */
    return UDR0;
}
