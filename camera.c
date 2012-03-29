//-------------------------------------------
/*
CAMERA.c
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#include "global.h"

void camera_Canon_IR(char port, uint8_t pin) { //Main loop, runs once but can have an infinit loop in it
    init_out(port, pin);
    for (i=0; i<17; i++) {
        out(port, pin, 1);
        _delay_ms(0.012);
        out(port, pin, 0);
        _delay_ms(0.012);
    }
    _delay_ms(7.5);
    for (i=0; i<17; i++) {
        out(port, pin, 1);
        _delay_ms(0.012);
        out(port, pin, 0);
        _delay_ms(0.012);
    }
    return;
}

