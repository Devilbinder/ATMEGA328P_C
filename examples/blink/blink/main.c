/*
 * blink.c
 *
 * Created: 2020/09/06 00:24:30
 * Author : DevilBinder
 */ 

#include <stdint.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	
	uint16_t run = 1;
	
	DDRD = 0xFF; //0b11111111
	
    while (1) 
    {
		PORTD = 0x00; // bit 7 on 0b10000000
		_delay_ms(250);
		PORTD = run; // bit 7 off 0b00000000
		_delay_ms(250);
		
		//0b00000001 1
		//0b00000010 2
		//0b00000100 4
		//0b00001000 8
		//0b00010000 16
		//0b00100000 32
		//0b01000000 64
		//0b10000000 128
		//0b00000001 1
		
		if(run >= 0x80){
			run = 1;
		}else{
			run *= 2;
		}

    }
}

