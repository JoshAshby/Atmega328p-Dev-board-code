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
#include "uart.h"

int main(void)
{
    DDRD |= (1<<2);
    PORTD |= (1<<2);
    //as soon as the board comes on this runs to keep the regulator running
    pwm_setup_all();
    adc_start(0);
    uart_start();
    twi_start();
    uart_sendchar("hello");
    uint8_t getByte;
    getByte = uart_get();
    uart_sendint(getByte);
    uint16_t data_a;
    while(1){
        data_a = ADCL;
        data_a += (ADCH<<8);
        twi_mcp_dac(MCP_ADDRESS, data_a, 1);
        pwm1A(data_a);
        uart_sendint16(data_a);
        _delay_ms(50);
    };

    return 0;
}
