//-------------------------------------------
/*
i2c.h
2010 - Josh Ashby
joshuaashby@joshashby.com
http://joshashby.com
http://github.com/JoshAshby
freenode/#linuxandsci - JoshAshby
*/
//-------------------------------------------
#ifndef I2C_H
#define I2C_H
#include <avr/io.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <compat/twi.h>

#define MAX_TRIES 50
#define TWI_START 0
#define TWI_DATA 1
#define TWI_STOP 2

unsigned char twi_tran(unsigned char type);
int twi_mcp_dac(unsigned int twi_address, uint16_t data);
int twi_mcp_ee(unsigned int twi_address, uint16_t data);
int twi_mcp_read(unsigned int twi_address, int *set, int *first, int *second);

#endif

