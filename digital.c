//-------------------------------------------
/*
digital.c
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

/*
Pretty useless library, all it does it clean up the main code a little, and makes
sure I don't have to remember how to turn a pin high or low ;D
The out() function is the most usefull I find, since i just have to tell it which port
and what pin and value to set it at
*/

void portB_out(int pin, _Bool value)
{
    if (value == 0)
    {
        PORTB &= ~(1<<pin);
    }
    else
    {
        PORTB |= (1<<pin);
    }
}

void portD_out(int pin, _Bool value)
{
    if (value == 0)
    {
        PORTD &= ~(1<<pin);
    }
    else
    {
        PORTD |= (1<<pin);
    }
}

void out(char port, int pin, _Bool value){
    switch (port) {
        case 'D':
            DDRD |= (1<<pin);
            if(value == 1){
                PORTD |= (1<<pin);
            }
            else {
                PORTD &= ~(1<<pin);
            }
            break;
        case 'B':
            DDRB |= (1<<pin);
            if(value == 1){
                PORTB |= (1<<pin);
            }
            else {
                PORTB &= ~(1<<pin);
            }
            break;
    }
}

ISR(PCINT2_vect) {
    button_one = (button_one * 9 + (PIND & 0b00001000) * 16)/16;
    button_two = (button_two * 9 + (PIND & 0b00010000) * 16)/16;
}
