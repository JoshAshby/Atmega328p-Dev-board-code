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
    adc_start(0);
    uart_start();
    twi_start();

    while(1) { //infinit loop that doesn't stop running. (always true since 1 is always 1

        //sample button text, eventually this will become the meet and bones of
        //digital.c running as an interrupt code which also debounces the button
        //and letting the main code know that a button has been pressed, and which one
        temp = (PIND & 0x0c); //temp is the 3rd and 4th pins of port D
        if (temp == 1){ //If either are pulled high then turn pin 1 on port B on
            out('B',1,1);
        }
        if (temp == 0){ //if either are off, turn pin1 port B off
            out('B',1,0);
        }
    };
    return 0;
}
