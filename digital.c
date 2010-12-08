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

void check_buttons(void) {
    //button one
    if (count[0] > 5) { //if the buttons stable, set the array for button 1 as stable
        //and reset the counter if the buttons been released
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
    if ((PIND & button_one) == 0) { //reset the counter as soon as button one is released
            button[0] = 0;
    }

    //button two
    if (count[1] > 5) {//if the buttons stable, set the array for button 2 as stable
        //and reset the counter if the buttons been released
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
    if ((PIND & button_two) == 0) {//reset the counter as soon as button two is released
            button[1] = 0;
    }
}

void buttons(void) {
    if (button[0] == 1) { //If the first button is pulled high then
        //turn pin 1 on port B on
        out('D',stat_led1,!debug);
    } else { //if either are off, turn pin1 port B off
        out('D',stat_led1,debug);
    }
    if (button[1] == 1) { //If the second button is pulled high then
        //turn pin 2 on port B on
        out('D',stat_led2,!debug);
    } else { //if either are off, turn pin1 port B off
        out('D',stat_led2,debug);
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
