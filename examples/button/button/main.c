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
	
	DDRB &= 0xF9;
	
	PORTB |= (1 << PORTB1) | (1 << PORTB2);
	
    while (1) 
    {
		
		if((PINB & (1 << PINB1)) == 0){
			_delay_ms(250);
			if(run >= 0x80){
				run = 1;
			}
			else{
				run *= 2;
			}
		}
		
		if((PINB & (1 << PINB2)) == 0){
			_delay_ms(250);
			if(run <= 1){
				run = 0x80;
			}
			else{
				run /= 2;
			}
		}


		PORTD = run; // bit 7 off 0b00000000

    }
}

