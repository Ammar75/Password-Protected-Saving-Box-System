/*
 * EEPROM_Driver.c
 *
 * Created: 4/9/2025 5:01:53 PM
 *  Author: Ammar
 */ 
#include "std_macros.h"
#include "EEPROM_Driver.h"
#include <stdint.h>
#define EEMWE_ 2
#define EEWE_  1
#define EERE_  0
#define EEPROM_MAX_ADDR 1023
#define EEPROM_READ_ERROR 0x00

void EEPROM_WriteByte(unsigned short address , unsigned char data)
{
	if (address > EEPROM_MAX_ADDR) return EEPROM_READ_ERROR;
	EEARL_ = (unsigned char) address ;
	EEARH_ = (unsigned char) (address >> 8);
	EEDR_ = data;
	SET_BIT(EECR_,EEMWE_);
	SET_BIT(EECR_,EEWE_);
	
	while(READ_BIT(EECR_,EEWE_));
}

unsigned char EEPROM_ReadByte_8u(unsigned short address)
{
	if (address > EEPROM_MAX_ADDR) return EEPROM_READ_ERROR;
	unsigned char data = 0 ; 
	EEARL_ = (unsigned char) address ;
	EEARH_ = (unsigned char) (address >> 8);
	
	SET_BIT(EECR_,EERE_);
	data = EEDR_;
	while(READ_BIT(EECR_,EERE_));
	return data;
}
	
	
void EEPROM_WriteInt16_16u(unsigned short address , int data)
{	
	if (address > EEPROM_MAX_ADDR) return EEPROM_READ_ERROR;
	uint8_t lowbyte = (uint8_t)(data);
	uint8_t highbyte = (uint8_t)(data>>8);
	EEPROM_WriteByte(address,lowbyte);
	EEPROM_WriteByte((address+1),highbyte);
	
	
}

int16_t EEPROM_ReadInt16(unsigned short address)
{	
	if (address > EEPROM_MAX_ADDR) return EEPROM_READ_ERROR;
	uint16_t valuee = 0;
	uint8_t lowByte = EEPROM_ReadByte_8u(address);
	uint8_t highByte = EEPROM_ReadByte_8u(address + 1);
	valuee = lowByte | ((uint16_t)highByte << 8);
	return (int16_t)valuee;
}