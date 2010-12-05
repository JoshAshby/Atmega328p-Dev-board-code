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

    while(1) { //infinit loop that doesn't stop running.
        temp = (PIND & 0x0c);
        if (temp == 1){
            out('B',1,1);
        }
        if (temp == 0){
            out('B',1,0);
        }
    };
    return 0;
}
