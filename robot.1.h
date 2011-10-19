//-------------------------------------------
/*
ROBOT.h
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef ROBOT_H
#define ROBOT_H
#include "global.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------
#define PWM1 1
#define PWM2 2
#define OUT1 3
#define OUT2 4
#define ULTRASOUND_LEFT 0
#define ULTRASOUND_LEFT_BACK 1
#define ULTRASOUND_RIGHT 2
#define ULTRASOUND_RIGHT_BACK 3
#define ULTRASOUND_CENTER 4
#define ADC1 5

#define EXTRA1 7 //PORTD7
#define EXTRA1 0 //PORTB 0
#define EXTRA1 5 //PORTB 7

//-----------------------------------------------
//Variables
//-----------------------------------------------
volatile uint8_t filt;
volatile uint8_t rollAverage[16];
volatile uint8_t average;
volatile uint8_t j;
volatile uint8_t adc;

//-----------------------------------------------
//Structers and Unions and typedefs
//-----------------------------------------------

//-----------------------------------------------
//Prototypes
//-----------------------------------------------
uint8_t ultrasound_filter(void);

#endif
