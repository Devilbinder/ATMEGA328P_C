/*
 * eeprom.c
 *
 * Created: 2020/10/31 22:54:59
 *  Author: DevilBinder
 */ 

#include "eeprom.h"



uint8_t EEPROM_read(uint16_t uiAddress, uint8_t *data)
{
	
	if(uiAddress > EEPROM_SIZE){
		return EEPROM_INVALID_ADDR;
	}
	
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEARH = (uiAddress & 0xFF00) >> 8;
	EEARL = (uiAddress & 0x00FF);
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	*data = EEDR;
	return EEPROM_OK;
}


uint8_t EEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
	if(uiAddress > EEPROM_SIZE){
		return EEPROM_INVALID_ADDR;
	}
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address and Data Registers */
	EEARH = (uiAddress & 0xFF00) >> 8;
	EEARL = (uiAddress & 0x00FF);
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
	return EEPROM_OK;
}

uint8_t EEPROM_update(uint16_t uiAddress, uint8_t ucData){
	uint8_t err = EEPROM_OK;
	if(uiAddress > EEPROM_SIZE){
		return EEPROM_INVALID_ADDR;
	}
	uint8_t value = 0;
	
	err = EEPROM_read(uiAddress,&value);
	if(err != EEPROM_OK){
		return err;
	}
	if(value == ucData){
		return EEPROM_OK;
	}
	
	err = EEPROM_write(uiAddress,ucData);
	if(err != EEPROM_OK){
		return err;
	}
	
	err = EEPROM_read(uiAddress,&value);
	if(err != EEPROM_OK){
		return err;
	}
	if(value != ucData){
		return EEPROM_WRITE_FAIL;
	}
	
	return EEPROM_OK;
	
}

uint8_t EEPROM_update_batch(uint16_t uiAddress, void *data,uint16_t len){
	uint16_t i = 0;
	uint8_t err = EEPROM_OK;
	uint8_t *data_cast = (uint8_t *)data;
	
	for(i = 0; i < len; i++){
		err = EEPROM_update(uiAddress + i,data_cast[i]);
		if(err != EEPROM_OK){
			return err;
		}
	}

	return EEPROM_OK;
}


uint8_t EEPROM_read_batch(uint16_t uiAddress, void *data,uint16_t len){
	uint16_t i = 0;
	uint8_t err = EEPROM_OK;
	uint8_t *data_cast = (uint8_t *)data;
	
	for(i = 0; i < len; i++){
		err = EEPROM_read(uiAddress + i,&data_cast[i]);
		if(err != EEPROM_OK){
			return err;
		}
	}

	return EEPROM_OK;
}
































