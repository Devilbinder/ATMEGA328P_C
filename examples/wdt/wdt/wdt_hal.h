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
 


#ifndef WDT_HAL_H_
#define WDT_HAL_H_

#include <stdint.h>
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define wdr() __asm__ __volatile__ ("wdr")

typedef enum{
	wdt_timeout_16ms,
	wdt_timeout_32ms,
	wdt_timeout_64ms,
	wdt_timeout_125ms,
	wdt_timeout_250ms,
	wdt_timeout_500ms,
	wdt_timeout_1s,
	wdt_timeout_2s,
	wdt_timeout_4s,
	wdt_timeout_8s,
}wdt_timeout_e;


void WDT_off(uint8_t int_enable);
void WDT_enable(void);
void WDT_prescaler_change(uint8_t int_enable,wdt_timeout_e timeout);


#endif /* WDT_HAL_H_ */