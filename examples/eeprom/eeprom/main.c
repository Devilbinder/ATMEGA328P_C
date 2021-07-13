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
#include "eeprom.h"

uint8_t print_buffer[64] = {0};

int main(void)
{
	const uint8_t start[] = "\n\rProgram Start\n\r";
	uint8_t run = 0;
	uint8_t err = 0;
	
	DDRD &= 0xF0;
	DDRB &= 0x0F;
	uart_init(9600,0);
	
	sei();
	uart_send_string((uint8_t*)start);
	
	err = EEPROM_read(96,&run);
	
	memset(print_buffer,0,sizeof(print_buffer));
	sprintf((char*)print_buffer,"%d value %d\r\n",__LINE__,run);
	uart_send_string(print_buffer);
	
	uint8_t c = run + 1;
	
	memset(print_buffer,0,sizeof(print_buffer));
	sprintf((char*)print_buffer,"%d value %d\r\n",__LINE__,c);
	uart_send_string(print_buffer);
	
	err = EEPROM_update(96,c);

	
	PORTD &= 0x0F;
	PORTB &= 0xF0;
	PORTD |= ((run & 0x0F) << 4);
	PORTB |= ((run & 0xF0) >> 4);
	
    while (1) 
    {
    }
}

