//-------------------------------------------
/*
DIGITAL.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void out(char port, int pin, _Bool value) {
    /*
    Change the state of a pin on given port
    simply pass the Port as either D or B (make sure to enclose it in single
    quotes like so: 'D')
    The pin number you would like to change state of,
    and either a 0 to sink current or 1 to source it on that pin
    */
    switch (port) { //switch determines if which port it is
        case 'D':
            DDRD |= (1<<pin); //change the pin to output
            if(value == 1) { //sink or source current
                PORTD |= (1<<pin);
            } else {
                PORTD &= ~(1<<pin);
            }
            break;
        case 'B':
            DDRB |= (1<<pin); //change pin to output
            if(value == 1) { //sink or source current
                PORTB |= (1<<pin);
            } else {
                PORTB &= ~(1<<pin);
            }
            break;
    }
}

/*
Buttons, this section uses timer2 because timer 1 is reserved for 16bit tasks
and timer0 is reserved for the kernel and task switching
 */
void init_debounce(void) {
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
    Timer2 overflow interrupt servic routine.
    In here is a fancy counter that keeps track of how long the button has been stable for
    if the button is still bouncing then the count will reset before it reaches the safe
    limit to count it as pressed.
    */
    button(1, (PIND & button_one));
}
