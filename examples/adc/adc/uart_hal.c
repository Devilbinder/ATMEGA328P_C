/*
 * uart_hal.c
 *
 * Created: 2020/10/03 21:48:31
 *  Author: DevilBinder
 */ 


#include "uart_hal.h"

volatile static uint8_t rx_buffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rx_count = 0;	
volatile static uint8_t uart_tx_busy = 1;

ISR(USART_RX_vect){
	
	volatile static uint16_t rx_write_pos = 0;
	
	rx_buffer[rx_write_pos] = UDR0;
	rx_count++;
	rx_write_pos++;
	if(rx_write_pos >= RX_BUFFER_SIZE){
		rx_write_pos = 0;
	}
	
}


ISR(USART_TX_vect){
	uart_tx_busy = 1;
}


void uart_init(uint32_t baud,uint8_t high_speed){
	
	uint8_t speed = 16;
	
	if(high_speed != 0){
		speed = 8;
		UCSR0A |= 1 << U2X0;
	}
	
	baud = (F_CPU/(speed*baud)) - 1;
	
	UBRR0H = (baud & 0x0F00) >> 8;
	UBRR0L = (baud & 0x00FF);
	
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
	
}


void uart_send_byte(uint8_t c){
	while(uart_tx_busy == 0);
	uart_tx_busy = 0;
	UDR0 = c;
}

void uart_send_array(uint8_t *c,uint16_t len){
	for(uint16_t i = 0; i < len;i++){
		uart_send_byte(c[i]);
	}
}

void uart_send_string(uint8_t *c){
	uint16_t i = 0;
	do{
		uart_send_byte(c[i]);
		i++;
		
	}while(c[i] != '\0');
	uart_send_byte(c[i]);
}

uint16_t uart_read_count(void){
	return rx_count;
}

uint8_t uart_read(void){
	static uint16_t rx_read_pos = 0;
	uint8_t data = 0;
	
	data = rx_buffer[rx_read_pos];
	rx_read_pos++;
	rx_count--;
	if(rx_read_pos >= RX_BUFFER_SIZE){
		rx_read_pos = 0;
	}
	return data;
}
