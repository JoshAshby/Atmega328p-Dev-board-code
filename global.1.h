//-------------------------------------------
/*
GLOBAL.h
2011 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef GLOBAL_H
#define GLOBAL_H

//-----------------------------------------------
//Libraries
//-----------------------------------------------
#include <avr/io.h>
#include <stdio.h>
#include <avr/interrupt.h>
#include <compat/twi.h>
#include <inttypes.h>
#include <stdlib.h>
#include <avr/sleep.h>

#include "kernel.h"
#include "adc.h"
#include "pwm.h"
#include "i2c.h"
#include "uart.h"
#include "digital.h"
#include "button.h"
#include "thread.h"

//-----------------------------------------------
//Macros (defines)
//-----------------------------------------------
//Debug
//========================
#define DEBUG 0 //if true, anything inside of an if(DEBUG){} or #if DEBUG tag will run, DEBUG_KEYS are sent this way
#define DEBUG_BEG 0 //if true, DEBUG_KEYS will also come with more info and a fancy LED. This comes at the price of a few extra CPU cycles for debug
#define DEBUG_KERNEL 0 //set to debug the KERNEL and THREADs

//CPU power and Debug LEDs
//========================
#define CPU_POW 2 //PORTD

//Status LEDs
//========================
#define stat_led1 5 //PORTD
#define stat_led2 6 //PORTD

//Buttons
//========================
#define button_one 0b00001000 //PORTD pin 3
#define button_two 0b00010000 //PORTD pin 4

//TWI addresses
//========================
#define MCP_ADDRESS 0xC0 //address of the MCP I2C DAC
//addresses of the IGT I2C gyroscope
#define GX_H    0x1D
#define GX_L    0x1E
#define GY_H    0x1F
#define GY_L    0x20
#define GZ_H    0x21
#define GZ_L    0x22

//Debug KEYS
//========================
//Here we have a list of "keys" or the debug code which is sent out to the serial port each time the debug is set, and the setup
//routines for each "key" start.
#define BIOS_KEY 0x01
#define DIG_KEY 0x02
#define ADC_KEY 0x03
#define UART_KEY 0x04
#define TWI_KEY 0x05
#define MAIN_KEY 0x06
#define DEBOUNCE_KEY 0x07
#define BUTTON_KEY 0x08
#define PWM_KEY 0x10 //0x10 - setup PWM_ALL
    //0x11 - setup PWM0
    //0x12 - setup PWM1
    //0x13 - setup PWM2

//KERNEL and related THREAD keys
#define KERNEL_KEY 0x15
#define THREAD0_KEY 0x20
#define THREAD1_KEY 0x21
#define THREAD2_KEY 0x22
#define THREAD3_KEY 0x23


//BIOS
//========================
/*
This macro is to setup hardaware, it will start
the pwm, adc, uart, and twi along with turn on the CPU power pin.
If the pin isn't pulled hight then somethings gone wrong before the
CPU is even up and running the code most of the time. Just so you know

UART has to be started first if your deebuging and using the serial console to do so
All debug keys get output to there

We're only starting PWM1 because the kernel uses TIMER0 for context switches,
and the button debouncer uses TIMER2 for the overflow interrupt
*/
#define bios() \
    uart_start(); \
    pwm_setup(2); \
    adc_start(1); \
    twi_start(); \
    DDRD |= (1<<CPU_POW); \
    PORTD |= (1<<CPU_POW); \
    if (DEBUG) { \
        uart_sendint(BIOS_KEY); \
        if (DEBUG_BEG) { \
            uart_sendstr("0x01 - Hardware setup successful..."); \
            uart_sendstr("Bios complete..."); \
            uart_sendstr("Starting main code..."); \
        }\
    } \
    sei();

#endif
