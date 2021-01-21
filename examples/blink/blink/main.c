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

