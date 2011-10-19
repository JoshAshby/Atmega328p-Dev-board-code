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
    if(which == 1) {
        if(what == 1) {
            //Runs once once per button press and no more.
            if(once[which] == 1) {
                return;
            } else {
                button1_once();
            }
            once[which] = 1;
        } else {
            once[which] = 0;
            out('D', stat_led1, 1);
        }
    }
    if(which == 2) {
        if(what == 1) {
            //runs for an infinit amount of time during the button press, stops when buttons been released.
            out('D', stat_led2, 0);
        } else {
            out('D', stat_led2, 1);
        }
    }
}

//What to run only once and once only when button 1 has been pressed.
void button1_once(void) {
    out('D', stat_led1, 0);
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
    if((PIND & button_one)) {
        dig_count[1]++;
        if (dig_count[1] > DEBOUNCE_TIME) {
            button(1, 1);
        }
    } else {
        //if the button changes state, reset the count and trigger the button bounce function
        dig_count[1] = 0;
        button(1, 0);
    }
    if((PIND & button_two)) {
        dig_count[2]++;
        if (dig_count[2] > DEBOUNCE_TIME) {
            button(2, 1);
        }
    } else {
        //if the button changes state, reset the count and trigger the button bounce function
        dig_count[2] = 0;
        button(2, 0);
    }
    if ((PIND & button_one) | (PIND & button_two)) {
        #if DEBUG
            uart_sendint(BUTTON_KEY);
            #if DEBUG_BEG
                uart_sendstr("0x08 - Button pressed");
            #endif
        #endif
    }
}

/*
Buttons, this section uses timer2 because timer 1 is reserved for 16bit tasks
and timer0 is reserved for the kernel and task switching
 */
void init_buttons(void) {
    DDRD &= ~(1<<DDD3)
         & ~(1<<DDD4);

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
