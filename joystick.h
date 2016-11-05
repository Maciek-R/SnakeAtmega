#ifndef joystick_h
#define joystick_h

#include <avr/io.h>

#define JOY_NIC		1016	//4,99V	//liczby zwracane przez ADC
#define JOY_LEFT 	152		//0,76V
#define JOY_RIGHT 	508		//2,54V
#define JOY_UP 		7		//0,03V
#define JOY_DOWN 	327		//1,63V
#define JOY_PUSH 	739		//3,69V

#define PIN_ADC		7		//pin PA7 ktory mierzy napiecie

uint8_t joy_left(uint16_t *);	//sprawdzany pomiar otrzymany przez wskaznik
uint8_t joy_right(uint16_t *);
uint8_t joy_up(uint16_t *);
uint8_t joy_down(uint16_t *);
uint8_t joy_push(uint16_t *);
uint8_t joy_dowolny(uint16_t *);		//jesli nacisniety dowolny przycisk joysticka



#endif
