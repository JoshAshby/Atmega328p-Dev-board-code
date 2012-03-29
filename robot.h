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
//Steering/Turn/Front Motor
//========================
#define PWM_FRONT 1
#define PMW_FRONT_BIT 0b00000010

#define RELAY_FRONT 3
#define RELAY_FRONT_BIT 0b00001000

//Drive/Back Motor
//========================
#define PWM_BACK 2
#define PMW_BACK_BIT 0b00000100

#define RELAY_BACK 4
#define RELAY_BACK_BIT 0b00010000

//Left Ultrasound
//========================
#define ULTRASOUND_LEFT 0
#define ULTRASOUND_LEFT_BACK 1

//Right Ultrasound
//========================
#define ULTRASOUND_RIGHT 2
#define ULTRASOUND_RIGHT_BACK 3

//Center Ultrasound
//========================
#define ULTRASOUND_CENTER 4

//Temp control
//========================
#define FAN 5 //PORTB 5
#define FAN_BIT 0b00100000

#define TEMP 5

//Switches
//========================
#define SWITCH1 7 //PORTD 7
#define SWITCH1_BIT 0b10000000
#define SWITCH2 0 //PORTB 0
#define SWITCH2_BIT 0b00000001


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
void init_sensors(void);
uint8_t ultrasound_filter(void);

#endif
