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

int main(void) {
    DDRD |= (1<<2);
    PORTD |= (1<<2);
    //as soon as the board comes on the above runs to keep the regulator running
    //after the power on button is released

    pwm_setup_all();
    adc_start(0);
    uart_start();
    twi_start();

    uart_sendchar("Booted Up");
    getByte = uart_get();
    uart_sendint(getByte);

    while(1) {
        data_analog = ADCL;
        data_analog += (ADCH<<8);
        twi_mcp_dac(MCP_ADDRESS, data_analog, 0);
        pwm1A(data_analog);
        uart_sendint16(data_analog);
        _delay_ms(50);
    };

    return 0;
}
