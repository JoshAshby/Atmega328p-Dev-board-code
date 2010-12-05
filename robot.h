//-------------------------------------------
/*
robot.h
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef ROBOT_H
#define ROBOT_H
#include <avr/io.h>
void robot_setup(void);
void forward(int speed);
void backward(int speed);
void spot_left(int speed);
void spot_right(int speed);
void track(int in_speed, int out_speed);
void stop(void);
#endif

