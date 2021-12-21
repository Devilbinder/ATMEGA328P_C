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
 


#include "timer0_hal.h"


volatile static uint32_t millis_c = 0;

ISR(TIMER0_COMPA_vect){
	millis_c++;
}



void timer0_init(void){
	TCCR0A |= (0b10 << WGM00);
	OCR0A = 249; // TOP value
	TIMSK0 |= (1 << OCIE0A);
	TCCR0B |= (0b011<< CS00);	
}


uint32_t millis(void){
	return millis_c;
}


uint8_t millis_end(uint32_t start_time,uint32_t delay_time){
	
	return ((millis() - start_time) >= delay_time);
	
}