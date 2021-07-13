/*
 * timer0_hal.h
 *
 * Created: 2020/10/18 14:42:26
 *  Author: DevilBinder
 */ 


#ifndef TIMER0_HAL_H_
#define TIMER0_HAL_H_

#include <stdint.h>
#include "config.h"
#include <avr/io.h>
#include <avr/interrupt.h>


void timer0_init(void);
uint32_t millis(void);
uint8_t millis_end(uint32_t start_time,uint32_t delay_time);


#endif /* TIMER0_HAL_H_ */