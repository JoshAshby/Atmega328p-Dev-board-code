//-------------------------------------------
/*
main.c
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

int main(void) { //Main loop, runs once but can have an infinit loop in it
    DDRD |= (1<<2);
    PORTD |= (1<<2);
    //as soon as the board comes on the above runs to keep the regulator running
    //after the power on button is released
    pwm_setup_all();
    adc_start(1);
    uart_start();
    twi_start();

    DDRD |= (0<<3)
         |  (0<<4); //setup the button pins as inputs

    init_button_timer0();

    while(1) { //infinit loop that doesn't stop running. (always true since 1 is always 1

        buttons();

        if (button[0] == 1) { //If either are pulled high then turn pin 1 on port B on
            out('B',1,!debug);
        } else { //if either are off, turn pin1 port B off
            out('B',1,debug);
        }
        //button_two = (button_two * 9 + (PIND & 0b00010000) * 16)/16;
        if (button[1] == 1) { //If either are pulled high then turn pin 1 on port B on
            out('B',2,!debug);
        } else { //if either are off, turn pin1 port B off
            out('B',2,debug);
        }
        pwm2A(ADCH); //test to see if the code still will allow me to do both PWM
        //and ADC result at the same time and not slow down the core too much
        //it worked, and very well if i might say so
    };
    return 0;
}
