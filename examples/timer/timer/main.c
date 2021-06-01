/*
 * timer.c
 *
 * Created: 2020/10/17 21:54:25
 * Author : DevilBinder
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

