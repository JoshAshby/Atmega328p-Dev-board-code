//-------------------------------------------
/*
main.c
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

int main(void)
{
    DDRD |= (1<<2);
    PORTD |= (1<<2);
    //as soon as the board comes on this runs to keep the regulator running
    pwm_setup_all();
    adc_start("");
    PORTB |= (1<<1);
    uint16_t data_a;
    uint16_t first;
    uint16_t second;
    int set;
    while(1){
        data_a = ADCL;
        data_a += (ADCH<<8);
        twi_mcp_ee(MCP_ADDRESS, data_a);
        twi_mcp_read(MCP_ADDRESS, &set, &first, &second);
        first += (second<<8);
        pwm1A(first);
    };

    return 0;
}
