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
#include "wdt_hal.h"
//#include "avr/wdt.h"


static char print_buffer[64] = {0};

int main(void)
{
	uint8_t i = 0;
	WDT_off(0);
	WDT_prescaler_change(0,wdt_timeout_2s);
	
	DDRD |= (1 << DDD7) | (1 << DDD6);
	
	for(i = 0; i < 3; i++){ //4*3 1200ms
		PORTD |= (1 << PORTD7 | 1 << PORTD6);
		_delay_ms(200);
		PORTD &= ~(1 << PORTD7 | 1 << PORTD6);
		_delay_ms(200);
	}
	
	uart_init(9600,0);


	sei();
	uart_send_string((uint8_t*)"\n\rProgram Start\n\r");
	
	
	
    while(1) 
    {
		for(i = 0; i < 15; i++){ //15*4 6000ms 
			PORTD |= 1 << PORTD7;
			PORTD &= ~(1 << PORTD6);
			_delay_ms(200);
			PORTD |= 1 << PORTD6;
			PORTD &= ~(1 << PORTD7);
			_delay_ms(200);
			wdr();
		}
		break;
    }
	wdr();
	while(1){
		
	}
}

