/*
 * DIO.h
 *
 * Created: 3/5/2025 4:26:34 PM
 *  Author: Ammar
 */ 


#ifndef DIO_H_
#define DIO_H_





#endif /* DIO_H_ */

void Dio_VSet_pin_Dir(unsigned char port , unsigned char reg_numb , const char *dir);
void DIO_vwrite(unsigned char port , unsigned char reg_numb , const char *val);
void DIO_vToggle(unsigned char port , unsigned char reg_numb);
unsigned char DIO_u8Read_pin(unsigned char port , unsigned char reg_numb);
void Dio_connect_pullup(unsigned char port , unsigned char pin_numb , unsigned char state);

unsigned char DIO_U8Read_port(unsigned char port);
void DIO_VToggle_port(unsigned char port);
void DIO_VSet_port_Direction(unsigned char port , unsigned char *dir);
void DIO_VWrite_port(unsigned char port , unsigned char val);

void Dio_Write_lowNibble2(unsigned char port , unsigned char val );
void Dio_Write_highNibble2(unsigned char port , unsigned char val );
void Dio_Write_highNibble(unsigned char port , unsigned char val );
void Dio_Write_lowNibble(unsigned char port , unsigned char val );

Dio_Set_lowNibble(unsigned char port);
Dio_Set_highNibble(unsigned char port);