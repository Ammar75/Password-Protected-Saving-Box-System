/*
 * Keypad_driver.h
 *
 * Created: 4/19/2025 12:35:37 AM
 *  Author: Ammar
 */ 


#ifndef KEYPAD_DRIVER_H_
#define KEYPAD_DRIVER_H_

void keypad_intialize( unsigned char port);
unsigned char Keypad_Pressed_value8u(void);
unsigned char keypad_u8check_press(void);


#endif /* KEYPAD_DRIVER_H_ */