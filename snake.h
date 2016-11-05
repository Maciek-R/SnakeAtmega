#ifndef snake_h
#define snake_h
#include <avr/io.h>

typedef struct				//struktura przechowujaca elementy weza
{
	uint8_t x;
	uint8_t y;
	struct Snake * next;
	
} Snake;

void snake_init();
void plansza_init();
void snake_skret(uint8_t);

extern volatile uint8_t czy_grac_dalej;


#endif
