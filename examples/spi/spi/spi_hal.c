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
#include "spi_hal.h"


volatile uint8_t spi_rx_data = 0;
volatile uint8_t spi_txrx_done = 0;

ISR(SPI_STC_vect){
	
	if(SPSR & 0x40){
		spi_rx_data = SPDR;
		spi_rx_data = 0;
		spi_txrx_done = 1;
	}else{
		spi_rx_data = SPDR;
		spi_txrx_done = 1;
	}
}


void spi_master_init(void){
	DDRB |= (1 << DDB5) | (1 << DDB3) | (1 << DDB2); 
	PORTB |= 1 << PORTB2;
	
	SPCR = (1 << SPIE) | (1 << SPE) | (1 << MSTR)  | (1 << CPOL) | (0 << CPHA) | (0b11 << SPR0);
}



static void spi_send(uint8_t *tx,uint8_t *rx){
	spi_txrx_done = 0;
	SPDR = *tx;
	while(spi_txrx_done == 0);
	*rx = spi_rx_data;
}

void spi_tranfer(uint8_t *tx,uint8_t *rx,uint16_t len){
	
	PORTB &= ~(1 << PORTB2);
	_delay_us(100);
	for(uint16_t i=0; i < len;i++){
		
		spi_send(&tx[i],&rx[i]);
	}
	PORTB |= 1 << PORTB2;
	_delay_us(100);
}



 
