/*
Copyright (c) 2020 Devilbinder (Binder Tronics) https://bindertronics.com/

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
#include "adc_hal.h"
#include "timer0_hal.h"

uint8_t print_buffer[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 0;
	uint16_t adc = 0;
	uint32_t holder = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	uart_init(9600,0);
	adc_init();
	adc_pin_enable(ADC5_PIN);
	adc_pin_select(ADC5_PIN);
	
	timer0_init();
	
	sei();
	
	uart_send_string((uint8_t*)start);
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
	
	adc = adc_convert();
	holder = millis();
	
    while (1) 
    {
		
		if(millis_end(holder,adc)){
			run++;
			PORTD &= 0x0F;
			PORTB &= 0xF0;
			PORTD |= ((run & 0x0F) << 4);
			PORTB |= ((run & 0xF0) >> 4);
			adc = adc_convert();
			holder = millis();
		}

    }
}

