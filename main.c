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
    adc_start("left");
    PORTB |= (1<<1);
    unsigned char data_a;
    int first,second,set;
    while(1){
        data_a = ((ADCL << 2) | ADCH);
        //twi_mcp_ee(MCP_ADDRESS, data_a);
        twi_mcp_read(MCP_ADDRESS, &set, &first, &second);
        pwm1A((first << 4) | second);
    };

    return 0;
}
