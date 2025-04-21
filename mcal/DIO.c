/*
 * DIO.c
 *
 * Created: 3/5/2025 4:26:20 PM
 *  Author: Ammar
 */ 
#include "std_macros.h"
#include <string.h>

void Dio_VSet_pin_Dir(unsigned char port, unsigned char reg_numb, const char *dir)
{
	if (((strcmp(dir, "OUTPUT")) == 0) || ((strcmp(dir, "output")) == 0))
	{
		switch (port)
		{
			case 'A':
			case 'a':
				SET_BIT(DDRA_, reg_numb);
				break;
			case 'B':
			case 'b':
				SET_BIT(DDRB_, reg_numb);
				break;
			case 'C':
			case 'c':
				SET_BIT(DDRC_, reg_numb);
				break;
			case 'D':   // Fixed inconsistency
			case 'd':
				SET_BIT(DDRD_, reg_numb);
				break;
			default:
				break;  // Handle unexpected port values
		}
	}
	else if (((strcmp(dir, "INPUT")) == 0) || ((strcmp(dir, "input")) == 0))
	{
		switch (port)
		{
			case 'A':
			case 'a':
			CLEAR_BIT(DDRA_, reg_numb);
			break;
			case 'B':
			case 'b':
			CLEAR_BIT(DDRB_, reg_numb);
			break;
			case 'C':
			case 'c':
			CLEAR_BIT(DDRC_, reg_numb);
			break;
			case 'D':   // Fixed inconsistency
			case 'd':
			CLEAR_BIT(DDRD_, reg_numb);
			break;
			default:
			break;  // Handle unexpected port values
		}
	}
}

void DIO_vwrite(unsigned char port , unsigned char reg_numb, const char *val)
{
	if (((strcmp(val, "HIGH")) == 0) || ((strcmp(val, "high")) == 0) || ((strcmp(val, "1")) == 0) )
	{
		switch (port)
		{
			case 'A':
			case 'a':
			SET_BIT(PORTA_, reg_numb);
			break;
			case 'B':
			case 'b':
			SET_BIT(PORTB_, reg_numb);
			break;
			case 'C':
			case 'c':
			SET_BIT(PORTC_, reg_numb);
			break;
			case 'D':   // Fixed inconsistency
			case 'd':
			SET_BIT(PORTD_, reg_numb);
			break;
			default:
			break;  // Handle unexpected port values
		}
	}
	else if (((strcmp(val, "LOW")) == 0) || ((strcmp(val, "low")) == 0) || ((strcmp(val, "0")) == 0))
	{
		switch (port)
		{
			case 'A':
			case 'a':
			CLEAR_BIT(PORTA_, reg_numb);
			break;
			case 'B':
			case 'b':
			CLEAR_BIT(PORTB_, reg_numb);
			break;
			case 'C':
			case 'c':
			CLEAR_BIT(PORTC_, reg_numb);
			break;
			case 'D':   // Fixed inconsistency
			case 'd':
			CLEAR_BIT(PORTD_, reg_numb);
			break;
			default:
			break;  // Handle unexpected port values
		}
	}
	
}

void DIO_vToggle(unsigned char port , unsigned char reg_numb)
{
	switch (port)
	{
		case 'A':
		case 'a':
		TOG_BIT(PORTA_, reg_numb);
		break;
		case 'B':
		case 'b':
		TOG_BIT(PORTB_, reg_numb);
		break;
		case 'C':
		case 'c':
		TOG_BIT(PORTC_, reg_numb);
		break;
		case 'D':   // Fixed inconsistency
		case 'd':
		TOG_BIT(PORTD_, reg_numb);
		break;
		default:
		break;  // Handle unexpected port values
	}
	
}

unsigned char DIO_u8Read_pin(unsigned char port , unsigned char reg_numb)
{
	
	switch (port)
	{
		case 'A':
		case 'a':
		return READ_BIT(PINA_, reg_numb);
		break;
		case 'B':
		case 'b':
		return READ_BIT(PINB_, reg_numb);
		break;
		case 'C':
		case 'c':
		return READ_BIT(PINC_, reg_numb);
		break;
		case 'D':   // Fixed inconsistency
		case 'd':
		return READ_BIT(PIND_, reg_numb);
		break;
		default:
		break;  // Handle unexpected port values
	}
}


void DIO_VSet_port_Direction(unsigned char port , unsigned char *dir)
{
	if (((strcmp(dir, "OUTPUT")) == 0) || ((strcmp(dir, "output")) == 0))
		{
			switch(port)
			{
				case'a':
				case'A':
				DDRA_ = 0xff;
				break;
				case 'b':
				case 'B':
				DDRB_ = 0xff;
				break;
				case 'C':
				case 'c':
				DDRC_ = 0xff;
				break;
				case 'd':
				case 'D':
				DDRD_ = 0xff;
				break;
			}
		}
	else if (((strcmp(dir, "INPUT")) == 0) || ((strcmp(dir, "input")) == 0))
	{
		switch(port)
		{
			case'a':
			case'A':
			DDRA_ = 0;
			break;
			case 'b':
			case 'B':
			DDRB_ = 0;
			break;
			case 'C':
			case 'c':
			DDRC_ = 0;
			break;
			case 'd':
			case 'D':
			DDRD_ = 0;
			break;
		}
	}
}

void DIO_VWrite_port(unsigned char port , unsigned char val)
{
		switch(port)
		{
			case'a':
			case'A':
			PORTA_ = val;
			break;
			case 'b':
			case 'B':
			PORTB_ = val;
			break;
			case 'C':
			case 'c':
			PORTC_ = val;
			break;
			case 'd':
			case 'D':
			PORTD_ = val;
			break;
		
	}

}


unsigned char DIO_U8Read_port(unsigned char port)
{
	switch(port)
	{
		case'a':
		case'A':
			return PINA_ ;
			break;
		case 'b':
		case 'B':
			return PINB_;
			break;
		case 'C':
		case 'c':
			return PINC_;
			break;
		case 'd':
		case 'D':
			return PIND_;
			break;
	}
}


void DIO_VToggle_port(unsigned char port)

{
	switch(port)
	{
		case'a':
		case'A':
			return PORTA_ ^= (0xff);
			break;
		case 'b':
		case 'B':
			return PORTB_ ^= (0xff);
			break;
		case 'C':
		case 'c':
			return PORTC_ ^= (0xff);
			break;
		case 'd':
		case 'D':
			return PORTD_ ^= (0xff);
			break;
	}
}


void Dio_connect_pullup(unsigned char port , unsigned char pin_numb , unsigned char state)
{
// by default the PUD of SFIOR is set to low which means the pull-up is enabled
	switch(port)
	{
		case 'A':
		case 'a':			
			(state == 1) ?  (SET_BIT(PORTA_ , pin_numb),0) : (CLEAR_BIT(PORTA_,pin_numb),0);
			break;
		case 'B':
		case 'b':
			(state == 1) ?  (SET_BIT(PORTB_ , pin_numb),0) : (CLEAR_BIT(PORTB_,pin_numb),0);
			break;
		case 'C':
		case 'c':
			(state == 1) ?  (SET_BIT(PORTC_ , pin_numb),0) : (CLEAR_BIT(PORTC_,pin_numb),0);
			break;
		case 'D':
		case 'd':
			(state == 1) ?  (SET_BIT(PORTD_ , pin_numb),0) : (CLEAR_BIT(PORTD_,pin_numb),0);
			break;
		default:
			break;
			
}
}


void Dio_Write_lowNibble2(unsigned char port , unsigned char val )
{
	const char *bit_as_string[] = {"0", "1"};
	DIO_vwrite(port , 0 , bit_as_string[READ_BIT(val,0)]);
	DIO_vwrite(port , 1 , bit_as_string[READ_BIT(val,1)]);
	DIO_vwrite(port , 2 , bit_as_string[READ_BIT(val,2)]);
	DIO_vwrite(port , 3 , bit_as_string[READ_BIT(val,3)]);
}

void Dio_Write_highNibble2(unsigned char port , unsigned char val )
{
	const char *bit_as_string[] = {"0", "1"};
	DIO_vwrite(port , 4 , bit_as_string[READ_BIT(val,0)]);
	DIO_vwrite(port , 5 , bit_as_string[READ_BIT(val,1)]);
	DIO_vwrite(port , 6 , bit_as_string[READ_BIT(val,2)]);
	DIO_vwrite(port , 7 , bit_as_string[READ_BIT(val,3)]);
}

void Dio_Write_lowNibble(unsigned char port , unsigned char val )
{
	val &=0x0f;
	switch(port)
	{
		case'A':
		case'a':
			PORTA_&=0xf0;
			PORTA_|=val;
			break;
		case'b':
		case'B':
			PORTB_&=0xf0;
			PORTB_|=val;
			break;
		case'C':
		case'c':
			PORTC_&=0xf0;
			PORTC_|=val;
			break;
		case'D':
		case'd':
			PORTD_&=0xf0;
			PORTD_|=val;
			break;
		default:
			break;
	
	}
}



void Dio_Write_highNibble(unsigned char port , unsigned char val )
{
	val<<=4;
	switch(port) 
	{
		case'A':
		case'a':
			PORTA_&=0xf0;
			PORTA_|=val;
			break;
		case'b':
		case'B':
			PORTB_&=0xf0;
			PORTB_|=val;
			break;
		case'C':
		case'c':
			PORTC_&=0xf0;
			PORTC_|=val;
			break;
		case'D':
		case'd':
			PORTD_&=0xf0;
			PORTD_|=val;
			break;
		default:
			break;
		
	}
}

Dio_Set_lowNibble(unsigned char port)
{
	Dio_VSet_pin_Dir(port , 0,"OUTPUT");
	Dio_VSet_pin_Dir(port , 1,"OUTPUT");
	Dio_VSet_pin_Dir(port , 2,"OUTPUT");
	Dio_VSet_pin_Dir(port , 3,"OUTPUT");
}

Dio_Set_highNibble(unsigned char port)
{
	Dio_VSet_pin_Dir(port , 4,"OUTPUT");
	Dio_VSet_pin_Dir(port , 5,"OUTPUT");
	Dio_VSet_pin_Dir(port , 6,"OUTPUT");
	Dio_VSet_pin_Dir(port , 7,"OUTPUT");
}