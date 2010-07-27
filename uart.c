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

#define BAUD_PRESCALE (((F_CPU / (BAUD * 16UL))) - 1)

void uart_start(void) {
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);

    UBRR0L = BAUD_PRESCALE;
    UBRR0H = (BAUD_PRESCALE >> 8);

    UCSR0B |= (1 << RXCIE0);
    sei();
}

void uart_send(uint8_t data) {
    while (data) {
        while ((UCSR0A & (1 << UDRE0)) == 0);
		UDR0 = data;
		data += 1;
	}
}

uint8_t uart_get(void) {
    UCSR0B |= (1<<RXCIE0);

    sei();
	sleep_mode();
	cli();
	uint8_t b;
    if(read_spot == 0)
		b = input_buffer[sizeof(input_buffer) - 1];
	else
		b = input_buffer[read_spot - 1];
    if(b == '\r')
        b = '\n';
	return b;
}

ISR(SIG_USART_RECV) {
	input_buffer[read_spot] = UDR0;
	read_spot++;
	if(read_spot == BUFF_LEN) read_spot = 0;
}

//ISR(SIG_USART_RECV) {
//	uart_get();
//}
