/*
 * lcd.h
 *
 * Created: 4/16/2025 8:50:59 PM
 *  Author: Ammar
 */ 


#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>



// Public function prototypes
void Lcd_Initialize(void);
void Lcd_Send_char(uint8_t data);
void Lcd_Send_cmd(uint8_t cmd);
void Lcd_Clear_Screen(void);
void Lcd_send_string(const uint8_t *data);
void Lcd_Set_cursor(unsigned char row , unsigned char column);

// LCD Command definitions (public)
#define LCD_CLEAR_DISPLAY    0x01
#define LCD_RETURN_HOME      0x02
#define LCD_ENTRY_MODE_SET   0x06
#define LCD_DISPLAY_ON       0x0C
#define LCD_CURSOR_ON        0x0E
#define LCD_BLINK_ON         0x0F

#if defined Eight_bit_mode
#define LCD_FUNCTION_SET     0x38
#else
#define LCD_FUNCTION_SET     0x28
#endif


#define LCD_Data_port 'A'
#define LCD_control_port 'B'
#define En 0
#define RS 1

#endif /* LCD_H_ */