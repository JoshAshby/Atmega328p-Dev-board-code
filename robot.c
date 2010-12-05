//-------------------------------------------
/*
robot.c
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
#include "uart.h"
#include "digital.h"

void robot_setup(void) {
    DDRD |= (1<<d6);
    DDRD |= (1<<d7);
    DDRB |= (1<<d8);
    DDRB |= (1<<d9);
    DDRB |= (1<<d10);
    DDRB |= (1<<d11);
    DDRB |= (1<<d13);
    pwm_setup_all();
    portB_out(d13, 1);
}

void forward(int speed) {
    portB_out(d8, 0);
    portD_out(d7, 0);
    portB_out(d9, 1);
    portB_out(d10, 1);
    pwm0A(speed);
    pwm2A(speed);
}

void backward(int speed) {
    portB_out(d9, 0);
    portB_out(d10, 0);
    portB_out(d8, 1);
    portD_out(d7, 1);
    pwm0A(speed);
    pwm2A(speed);
}

void spot_left(int speed) {
    portB_out(d9, 0);
    portB_out(d10, 1);
    portB_out(d8, 1);
    portD_out(d7, 0);
    pwm0A(speed);
    pwm2A(speed);
}

void spot_right(int speed) {
    portB_out(d9, 1);
    portB_out(d10, 0);
    portB_out(d8, 0);
    portD_out(d7, 1);
    pwm0A(speed);
    pwm2A(speed);
}

void track(int in_speed, int out_speed) {
    portB_out(d8, 0);
    portD_out(d7, 0);
    portB_out(d9, 1);
    portB_out(d10, 1);
    pwm0A(in_speed);
    pwm2A(out_speed);
}

void stop(void) {
    portB_out(d8, 0);
    portD_out(d7, 0);
    portB_out(d9, 0);
    portB_out(d10, 0);
    pwm0A(0);
    pwm2A(0);
}
