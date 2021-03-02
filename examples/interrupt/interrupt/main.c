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
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t counter = 0x10; //0b00010000

ISR(INT0_vect){
	
	if(counter >= 0x80){
		counter = 0x10;
	}else{
		counter *= 2;
	}
}

ISR(INT1_vect){
	
	if(counter <= 0x10){
		counter = 0x80;
	}else{
		counter /= 2;
	}
}


int main(void)
{
	DDRD &= 0xF3; //0b11110011
	DDRD |= 0xF0; //0b11110000
	
	PORTD = 0x0C; //0b00001100
	
	EICRA |= (0b10 << ISC10) | (0b10 << ISC00);
	
	EIMSK = 0x03; //0b00000011
	
	sei();
	
    while (1) 
    {
		PORTD &= 0x0F; //0b00001111
		PORTD |= counter; //
		
    }
}

