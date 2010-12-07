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

void portB_out(int pin, _Bool value) {
    if (value == 0) {
        PORTB &= ~(1<<pin);
    } else  {
        PORTB |= (1<<pin);
    }
}

void portD_out(int pin, _Bool value) {
    if (value == 0) {
        PORTD &= ~(1<<pin);
    } else {
        PORTD |= (1<<pin);
    }
}

void out(char port, int pin, _Bool value) {
    switch (port) {
        case 'D':
            DDRD |= (1<<pin);
            if(value == 1) {
                PORTD |= (1<<pin);
            } else {
                PORTD &= ~(1<<pin);
            }
            break;
        case 'B':
            DDRB |= (1<<pin);
            if(value == 1) {
                PORTB |= (1<<pin);
            } else {
                PORTB &= ~(1<<pin);
            }
            break;
    }
}

void init_button_timer0(void) {
    TCNT0 = 0;
    TCCR0B |= (1<<CS01);
    TIMSK0 |= (1<<TOIE0);
}

void buttons(void) {
    //button one
    if (count[0] > 5) {
        if ((PIND & button_one) == 0) {
            count[0] = 0;
        }
        button[0] = 1;
    }
    if (count[0] > 250) {
        if ((PIND & button_one) == 0) {
            count[0] = 0;
        }
        button[0] = 2;
    }
    if ((PIND & button_one) == 0) {
            button[0] = 0;
    }

    //button two
    if (count[1] > 5) {
        if ((PIND & button_two) == 0) {
            count[1] = 0;
        }
        button[1] = 1;
    }
    if (count[1] > 250) {
        if ((PIND & button_two) == 0) {
            count[1] = 0;
        }
        button[1] = 2;
    }
    if ((PIND & button_two) == 0) {
            button[1] = 0;
    }
}

//pin change interrupt; whats in here will get ran everytime either of the pins we
//setup in main.c change state. ie: when a buttons been pressed
ISR(TIMER0_OVF_vect) {
    //figure out what pins been changed, and take the correct action
    if ((PIND & button_one)) {
        //simply increases or resets a counter, the main code then looks at the counter
        //and determines if the buttons been pressed, or held down
        count[0]++; //if buttton_ones been pressed, increase the count, as long as
        //the button continues to stay the same
    } else {
        count[0] = 0;
        //if the button changes state, reset the count
    }
    if ((PIND & button_two)) {
        //simply increases or resets a counter, the main code then looks at the counter
        //and determines if the buttons been pressed, or held down
        count[1]++; //if buttton_ones been pressed, increase the count, as long as
        //the button continues to stay the same
    } else {
        count[1] = 0;
        //if the button changes state, reset the count
    }
}
