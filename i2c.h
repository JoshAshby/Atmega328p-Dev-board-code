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
#include "global.h"

//-------------------------------------------
//Defines
//-------------------------------------------

#define MAX_TRIES 50
#define TWI_START 0
#define TWI_DATA 1
#define TWI_STOP 2

//-------------------------------------------
//Prototypes
//-------------------------------------------

void twi_start(void);
unsigned char twi_tran(unsigned char type);
int twi_mcp_dac(unsigned int twi_address, uint16_t data, _Bool type);
uint8_t twi_mcp_read(unsigned int twi_address);

//-------------------------------------------
//Variables
//-------------------------------------------

uint16_t mcp_data[2];

//uint16_t itg_data[3];

//signed int gyrox = 0;
//signed int gyroy = 0;
//signed int gyroz = 0;

#endif
