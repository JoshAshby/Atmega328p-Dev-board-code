//-------------------------------------------
/*
PWM.c
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
#include "i2c.h"

void pwm_setup_all(void){
    TCCR0B |= (1<<CS00)
            | (1<<CS01);
    TCCR0A |= (1<<WGM00);

    DDRD |= (1<<5);
    DDRD |= (1<<6);

    TCCR1B |= (1<<CS11)
            | (1<<CS10);
    TCCR1A |= (1<<WGM10);

    DDRB |= (1<<1);
    DDRB |= (1<<2);

    TCCR2B |= (1<<CS22);
    TCCR2A |= (1<<WGM20);

    DDRD |= (1<<3);
    DDRB |= (1<<3);
}
void pwm_setup0(void)
{
    TCCR0B |= (1<<CS00)
            | (1<<CS01);
    TCCR0A |= (1<<WGM00);

    DDRD |= (1<<5);
    DDRD |= (1<<6);
}
void pwm0A(uint16_t value)//set the duty cycle on the PWM
{
    TCCR0A |= (1<<COM0A1);
    OCR0A = value;
}
void pwm0B(uint16_t value)//set the duty cycle on the PWM
{
    TCCR0A |= (1<<COM0B1);
    OCR0B = value;
}
void pwm_setup1(void)
{
    TCCR1B |= (1<<CS11)
            | (1<<CS10);
    TCCR1A |= (1<<WGM10);

    DDRB |= (1<<1);
    DDRB |= (1<<2);
}
void pwm1A(uint16_t value)//set the duty cycle on the PWM
{
    TCCR1A |= (1<<COM1A1);
    OCR1A = value;
}
void pwm1B(uint16_t value)//set the duty cycle on the PWM
{
    TCCR1A |= (1<<COM1B1);
    OCR1B = value;
}
void pwm_setup2(void)
{
    TCCR2B |= (1<<CS22);
    TCCR2A |= (1<<WGM20);

    DDRD |= (1<<3);
    DDRB |= (1<<3);
}
void pwm2A(uint16_t value)//set the duty cycle on the PWM
{
    TCCR2A |= (1<<COM2A1);
    OCR2A = value;
}
void pwm2B(uint16_t value)//set the duty cycle on the PWM
{
    TCCR2A |= (1<<COM2B1);
    OCR2B = value;
}
