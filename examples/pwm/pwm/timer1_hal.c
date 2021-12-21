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
 
#include "timer1_hal.h"


volatile static uint8_t update_pwm_ready = 0;

ISR(TIMER1_OVF_vect){
	
	update_pwm_ready = 0;
}

ISR(TIMER1_COMPA_vect){
	
}



void pwm_init(void){
	
	DDRB |= (1 << DDB1);
	
	TCCR1A = (0b10 << COM1A0) | (0b00 << COM1B0) | (0b10 << WGM10);
	
	TIMSK1 = (1 << TOIE1) | (1 << OCIE1A);

	OCR1AH = (SEVRO_MIN & 0xFF00) >> 8;
	OCR1AL = (SEVRO_MIN & 0x00FF);
	
	ICR1H = (PWM_TOP & 0xFF00) >> 8;
	ICR1L = (PWM_TOP & 0x00FF);
	
	
	
	
	TCCR1B = (0b11 << WGM12) | (0b010 << CS10);
	
}

static void update_pwm(uint16_t i){
	update_pwm_ready = 1;
	while(update_pwm_ready != 0);
	OCR1AH = (i & 0xFF00) >> 8;
	OCR1AL = (i & 0x00FF);
}

void pwm_sweep(void){
	uint16_t i = 0;
	for(i = SEVRO_MIN; i <= SEVRO_MAX;i=+50){
		update_pwm(i);
		_delay_ms(40);
	}
	for(i = SEVRO_MAX; i >= SEVRO_MIN;i-=50){
		update_pwm(i);
		_delay_ms(40);
	}
}


void servo_set(uint16_t deg,uint16_t max_deg){
	
	float set = (float)deg / (float)max_deg;
	
	set = (((float)SEVRO_MAX-(float)SEVRO_MIN)*set) + (float)SEVRO_MIN;
	
	uint16_t piont = (uint16_t)set;
	
	update_pwm(piont);
	
}



