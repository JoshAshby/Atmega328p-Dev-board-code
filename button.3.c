//-------------------------------------------
/*
BUTTON.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void button(char which, char what) {
    switch (which) {
        case 1:
            switch (what) {
                case 1:
                    out('D', stat_led1, 0);
                    break;

                case 0:
                    out('D', stat_led1, 1);
                    break;
            }
        case 2:
            switch (what) {
                case 1:
                    out('D', stat_led2, 0);
                    break;

                case 0:
                    out('D', stat_led2, 1);
                    break;
            }
    }
}

void check_buttons(void) {
    /*

    In here is a fancy counter that keeps track of how long the button has been stable for
    if the button is still bouncing then the count will reset before it reaches the safe
    limit to count it as pressed.
    simply increases or resets a counter
    if the counter is above 5 it means the button is stable enough to be used
    if this happens, the function tied to that button is called
    if the button is released, then the count is cleared
    and the button bounce function is called
    */
    char which;
    if((PIND & button_one) | (PIND & button_two)) {
        if((PIND & button_one)) {
            which = 1;
        }
        if((PIND & button_two)) {
            which = 2;
        }
    }
    dig_count[which]++;
    if (dig_count[which] > 5) {
        button(which, 1);
    }
    //if the button changes state, reset the count and trigger the button bounce function
    dig_count[which] = 0;
    button(which, 0);
    #if DEBUG
        uart_sendint(BUTTON_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x08 - Button pressed");
        #endif
    #endif
}

/*
Buttons, this section uses timer2 because timer 1 is reserved for 16bit tasks
and timer0 is reserved for the kernel and task switching
 */
void init_buttons(void) {
    DDRD |= (0<<button_one);
    DDRD |= (0<<button_two);

    TCNT2 = 0; //set the inital timer value to 0
    TCCR2B |= (1<<CS02); //set the clock prescaler to clock/256 or 62.5kHz
    TIMSK2 |= (1<<TOIE0); //start the timer with the interrupt overflow turned on
    sei();

    #if DEBUG
        uart_sendint(DEBOUNCE_KEY);
        #if DEBUG_BEG
            uart_sendstr("0x07 - DEBOUNCE is up...");
        #endif
    #endif
}

ISR(TIMER2_OVF_vect) {
    /*
    Timer2 overflow interrupt servic routine for the debouncing of buttons.
    */
    check_buttons();
}
