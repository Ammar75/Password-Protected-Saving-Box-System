/*
 * project_1_saving_machine.c
 *
 * Created: 4/19/2025 6:02:46 PM
 *  Author: Ammar
 */ 


#include <avr/io.h>
#include "lcd.h"
#include "Keypad_driver.h"
#include "util/delay.h"
#include "EEPROM_Driver.h"
#define Pass_Address 100
#define max_trials 3

// return u_char
// 0 = first time
// 1 = Second time
unsigned char check_stored_pass(unsigned char address);

void enter_first_time_pass(unsigned char address);
// check the entered pass return
// return 1 if verified
// return 0 if denied
unsigned char check_pass(unsigned int address);


int main(void)
{	Lcd_Initialize();
	keypad_intialize('D');
	
	// check for old pass inside EEPROM
	Lcd_Set_cursor(1,3);
	Lcd_send_string("checking.....");
	_delay_ms(1000);
	Lcd_Clear_Screen();
	unsigned char check = check_stored_pass(Pass_Address);

	if (check == 0)
	{
		Lcd_send_string("Set New Pass");
		_delay_ms(1000);
		Lcd_Clear_Screen();
		enter_first_time_pass(Pass_Address);
	}
	else
	{
		Lcd_send_string("Welcome Back!");
		_delay_ms(1000);
		Lcd_Clear_Screen();
		
	}

	unsigned char trials = max_trials;
	unsigned char flag=0;
	while(1)
	
    {	
		while(trials > 0 )
		{
		Lcd_Clear_Screen();	
		check = check_pass(Pass_Address);
		_delay_ms(1000);
		Lcd_Clear_Screen();
		if (check)
		{   
			Lcd_Clear_Screen();	
			Lcd_Set_cursor(1,1);
			Lcd_send_string("Safe is opened ");
			Lcd_Set_cursor(2,1);
			Lcd_send_string("for :");
			for (int i = 9 ; i > 0 ; i--)
			{
				Lcd_Set_cursor(2,7);
				Lcd_Send_char(i+48);
				_delay_ms(1000);
				Lcd_send_string(" seconds");
			}
			_delay_ms(100);
			Lcd_Clear_Screen();
			Lcd_Set_cursor(1,6);
			Lcd_send_string("Locked");
			Lcd_Set_cursor(2,2);
			Lcd_send_string("See you again ");
			_delay_ms(2000);
		}		
		else
		{   trials--;
			Lcd_Send_char(trials+48);
			Lcd_send_string(" Trials Left");
			_delay_ms(1000);
			Lcd_Clear_Screen();	
		}		
		
		Lcd_Clear_Screen();
		}

		
	}
}


unsigned char check_stored_pass(unsigned char address)
{	
	unsigned char arr[4];
	unsigned char empty_flag =0;
	for(int i=0;i<4;i++)
	{
		if (EEPROM_ReadByte_8u(address+i) == 0xff)
		empty_flag++;
	}

	if ( empty_flag == 4)
	return 0;
	else
	return 1;
	
}


void enter_first_time_pass(unsigned char address)
{	
	Lcd_Clear_Screen();
	_delay_ms(500);
	unsigned char arr[4];
	int Entered_pass= 0 ;
	Lcd_Set_cursor(1,1);
	Lcd_send_string("new pass :");
	for (int i = 0 ; i < 4 ;i++)
	{
		do 
		{
			arr[i] = keypad_u8check_press(); 
			
		} while (arr[i] == 0);
		Lcd_Send_char(arr[i]);
		_delay_ms(200);
	}
	
	for (int i = 0 ; i < 4 ; i++)
	{
		EEPROM_WriteByte(address+i,(arr[i]-48));
		Entered_pass = Entered_pass * 10 + (arr[i]-48);
	}
	Lcd_Set_cursor(2,1);
	Lcd_send_string("pass is ");
	for (int i = 0 ; i < 4 ; i++)
	{
		Lcd_Send_char(arr[i]);
	}
	_delay_ms(2000);
	Lcd_Clear_Screen();
}




unsigned char check_pass(unsigned int address)
{
	unsigned int Entered_pass =0;
	unsigned int old_pass = 0;
	unsigned int new_pass[4];
	
	Lcd_Set_cursor(1,1);
	Lcd_send_string("enter pass: ");
	for (int i = 0; i < 4; i++)
	{
		unsigned char val = EEPROM_ReadByte_8u(address + i);
		old_pass = old_pass * 10 + val;
	}

	
	for (int i = 0 ; i < 4 ;i++)
	{
		do
		{
			new_pass[i] = keypad_u8check_press();
			_delay_ms(50);
		} while (new_pass[i] == 0);
		Lcd_Set_cursor(1,13+i);
		Lcd_Send_char(new_pass[i]);
		_delay_ms(200);
		Lcd_Set_cursor(1,13+i);
		Lcd_Send_char('*');
		Entered_pass = Entered_pass * 10 + (new_pass[i]-48) ; 
	}

	_delay_ms(500);
	Lcd_Clear_Screen();
	if (Entered_pass == old_pass)
	{	Lcd_send_string("Access granted");
		_delay_ms(500);
		Lcd_Clear_Screen();
		return 1;
	}	
	else
	{	Lcd_send_string("Access Denied");
		_delay_ms(500);
		Lcd_Clear_Screen();
		return 0;
	}	

}


