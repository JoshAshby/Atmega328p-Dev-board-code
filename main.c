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
        check_buttons(); //debounces the buttons with the aid of the timer0 interrupt
        buttons(); //if a buttons been pressed, code inside of here will run, if not
        //it's skiped over. simply cleans up this part of the code
    };
    return 0;
}
