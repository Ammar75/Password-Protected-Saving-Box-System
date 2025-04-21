/*
 * lcd.c
 *
 * Created: 4/16/2025 8:50:52 PM
 *  Author: Ammar
 */ 

#include "lcd.h"
#include "std_macros.h"
#include "DIO.h"
#include <util/delay.h>

// LCD Configuration (private)


// Private function prototype
static void enable(void);

void enable(void)
{
    DIO_vwrite(LCD_control_port, En, "HIGH");
    _delay_ms(1);       // Enable pulse width (typically >450ns)
    DIO_vwrite(LCD_control_port, En, "LOW");
    _delay_ms(1);     // Command/data execution time
}

void Lcd_Send_cmd(uint8_t cmd)
{
	#if defined Eight_bit_mode
    DIO_VWrite_port(LCD_Data_port, cmd);
    DIO_vwrite(LCD_control_port, RS, "LOW");
    enable();
	#else
	DIO_vwrite(LCD_control_port, RS, "LOW");
	Dio_Write_lowNibble(LCD_Data_port,(cmd >> 4)); // Send the most 4 bits
	enable();
	DIO_vwrite(LCD_control_port, RS, "LOW");
	Dio_Write_lowNibble(LCD_Data_port,cmd); // send the least 4 bits
	enable();
	#endif
	
    // Most commands need 1-2ms except clear and home
    if(cmd == LCD_CLEAR_DISPLAY || cmd == LCD_RETURN_HOME) {
        _delay_ms(2);
    } else {
        _delay_us(100);
    }
}

void Lcd_Send_char(uint8_t data)
{	
	#if defined Eight_bit_mode
    DIO_VWrite_port(LCD_Data_port, data);
    DIO_vwrite(LCD_control_port, RS, "HIGH");
    enable();
    _delay_us(100);     // Character write time
	#else
	DIO_vwrite(LCD_control_port, RS, "HIGH");
	Dio_Write_lowNibble(LCD_Data_port,(data >> 4)); // Send the most 4 bits
	enable();
	DIO_vwrite(LCD_control_port, RS, "HIGH");
	Dio_Write_lowNibble(LCD_Data_port,data); // send the least 4 bits
	enable();
	#endif
	
}

void Lcd_Initialize(void)
{
    // Set data and control pins as outputs
	#if defined Eight_bit_mode
    DIO_VSet_port_Direction(LCD_Data_port, "OUTPUT");
    Dio_VSet_pin_Dir(LCD_control_port, RS, "OUTPUT");
    Dio_VSet_pin_Dir(LCD_control_port, En, "OUTPUT");
	
	#else
	Dio_Set_lowNibble(LCD_Data_port);
	Dio_VSet_pin_Dir(LCD_control_port, RS, "OUTPUT");
	Dio_VSet_pin_Dir(LCD_control_port, En, "OUTPUT");
	#endif
    _delay_ms(30);
    
    // Initialization sequence
	Lcd_Send_cmd(LCD_RETURN_HOME); //return home
	_delay_ms(10);
	Lcd_Send_cmd(LCD_FUNCTION_SET); //4bit mode
	_delay_ms(1);
	Lcd_Send_cmd(LCD_CURSOR_ON);//display on cursor on
	_delay_ms(1);
	Lcd_Send_cmd(LCD_CLEAR_DISPLAY);//clear the screen
	_delay_ms(10);
	Lcd_Send_cmd(LCD_ENTRY_MODE_SET); //entry mode
	_delay_ms(1);


}

void Lcd_Clear_Screen(void)
{
    Lcd_Send_cmd(LCD_CLEAR_DISPLAY);
    _delay_ms(2);       // Clear display needs extra time
}

void Lcd_send_string(const uint8_t *data)
{
    while (*data != '\0') {
        Lcd_Send_char(*data++);
    }
}	

void Lcd_Set_cursor(unsigned char row , unsigned char column)
{	unsigned char address_line = 0;
	if (row == 1 && column >= 0 && column <= 16)
	{
		address_line = 0x80 + column -1;
	}
	else if(row == 2 && column >= 0 && column <= 16)
	{
		address_line = 0xC0 + column -1 ;
	}
	else 
	{
		address_line = 0x80;
	}
	Lcd_Send_cmd(address_line);
}