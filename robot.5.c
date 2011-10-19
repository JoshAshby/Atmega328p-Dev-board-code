//-------------------------------------------
/*
ROBOT.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void init_sensors(void) {
    DDRB |= (1<<3)
          | (1<<4);
    PORTB |
}

uint8_t ultrasound_filter(void) {
    filt = (average>>1);
    adc = ADCH;
    for (j = 0; j <= 16; j++){
        if (ADCH > average + 100)
        {
            adc = (ADCH >> 1) + filt;
        }
        if (ADCH < average - 100){
            adc = (ADCH >> 1) + filt;
        }
        rollAverage[j] = adc;
    }
    for (j = 0; j <= 16; j++){
        average += rollAverage[j];
    }
    average = average >> 4;
    return average;
}
