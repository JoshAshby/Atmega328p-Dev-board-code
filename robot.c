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
    DDRB &= ~(1<<SWITCH1_BIT);
    DDRD &= ~(1<<SWITCH2_BIT);

    init_out('B', PWM_BACK);
    init_out('B', PWM_FRONT);
    init_out('B', RELAY_BACK);
    init_out('B', RELAY_FRONT);
    init_out('B', FAN);
}

//What to run only once and once only when button 1 has been pressed.
void button1_once(void) {
    #if !KERNEL_COOP
        kernel_stack.task_flags[0] = 1;
    #endif
    if(led <= 250) {
        led += 5;
    }
}

void button2_once(void) {
    #if !KERNEL_COOP
        kernel_stack.task_flags[0] = 1;
    #endif
    if(led >= 5) {
        led -= 5;
    }
}

void button3_once(void) {
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
