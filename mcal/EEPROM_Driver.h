/*
 * EEPROM_Driver.h
 *
 * Created: 4/9/2025 5:02:00 PM
 *  Author: Ammar
 */ 
#include <stdint.h>

#ifndef EEPROM_DRIVER_H_
#define EEPROM_DRIVER_H_
void EEPROM_WriteByte(unsigned short address , unsigned char data);
unsigned char EEPROM_ReadByte_8u(unsigned short address);

void EEPROM_WriteInt16_16u(unsigned short address , int data);

int16_t EEPROM_ReadInt16(unsigned short address);


#endif /* EEPROM_DRIVER_H_ */