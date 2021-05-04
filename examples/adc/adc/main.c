/*
 * adc.c
 *
 * Created: 2020/10/04 00:34:42
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

uint8_t print_buffer[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 1;
	uint16_t convert = 0;

	DDRD &= 0xF0;
	DDRB &= 0x0F;
	
	uart_init(9600,0);
	
	adc_init();
	adc_pin_enable(ADC5_PIN);
	adc_pin_select(ADC5_PIN);

	//PORTD |= 0xF0;
	//PORTB = 0x0F;
	sei();
	uart_send_string((uint8_t*)start);
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
    /* Replace with your application code */
    while (1) 
    {

		convert = adc_convert();
		float volts = ADC_VOLT(convert);
		memset(print_buffer,0,sizeof(print_buffer));
		sprintf((char*)print_buffer,"ADC res:0x%04x V:%0.2f\r",convert,volts);
		uart_send_string(print_buffer);
		
		run = convert >> 2;
		PORTD &= 0x0F;
		PORTB &= 0xF0;
		PORTD |= ((run & 0x0F) << 4);
		PORTB |= ((run & 0xF0) >> 4); 
		
    }
}

