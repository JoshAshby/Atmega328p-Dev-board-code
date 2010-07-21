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
#include "adc.h"
#include "pwm.h"
#include "global.h"
#include <util/delay.h>


int main(void)
{
    DDRD |= (1<<2);
    PORTD |= (1<<2);
    //as soon as the board comes on this runs to keep the regulator running
    pwm_setup_all();
    adc_start();
    PORTB |= (0<<1);
    PORTB |= (0<<2);
    while(1){
        adc_change(0);
        _delay_ms(50);
        pwm1A(ADCH);
        adc_change(1);
        _delay_ms(50);
        pwm1B(ADCH);
    }
    ;

    return 0;
}
