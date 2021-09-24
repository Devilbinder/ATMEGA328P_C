/*
Copyright (c) 2021 Devilbinder (Binder Tronics) https://bindertronics.com/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */ 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart_hal.h"
#include "timer0_hal.h"
#include "spi_hal.h"


static char print_buffer[64] = {0};

int main(void)
{
	const char start[] = "\n\rProgram Start\n\r";

	uart_init(9600,0);

	spi_master_init();
	
	uint8_t tx_data = 0;
	uint8_t rx_data = 0;

	sei();
	uart_send_string((uint8_t*)"\n\rProgram Start\n\r");
	
	
	
    while(1) 
    {
		uart_send_string("tx start ");
		tx_data++;
		spi_tranfer(&tx_data,&rx_data,1);
		if(tx_data >= 255){
			tx_data = 0;
		}
		memset(print_buffer,0,sizeof(print_buffer));
		sprintf(print_buffer,"%c %d ",rx_data,tx_data);
		uart_send_string(print_buffer);
		uart_send_string("\n\r");
		
		_delay_ms(200);
		

    }
}

