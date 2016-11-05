

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "N6100.h"
//#include "FONT8x8.h"
#include <util/delay.h>
//#include "przyciski.h"
#include "menu.h"
#include "timer.h"
#include "snake.h"
#include "joystick.h"
#include "ADC.h"

/*char * menu[DL_MENU] = {"START", "WYNIKI", "EXIT"};
uint8_t pozycja_menu_poziom[DL_MENU] = {50, 58, 66};
uint8_t pozycja_menu_pion[DL_MENU] = {48, 44, 48};
uint8_t akt_menu = 0;*/


int main (void)
{

LCD_Init();
clr_scr();

Menu_init();

ADC_init();

//Key_init();

//snake_init();
//plansza_init();

Timer_off();
//Timer_on();
sei();

//uint8_t x = 16;
//uint8_t y = 0;
uint8_t gra = 0;		//0 menu   1 gra
uint16_t pom_nap;

	while (1)
	{
		pom_nap = pomiar(PIN_ADC);
		
		if (joy_dowolny(&pom_nap))
		{	
			_delay_ms(80);
			pom_nap = pomiar(PIN_ADC);

				if (joy_dowolny(&pom_nap))
				{	
						if(joy_left(&pom_nap))
						{
							_delay_ms(100);
							pom_nap = pomiar(PIN_ADC);
							while (joy_left(&pom_nap)) {pom_nap = pomiar(PIN_ADC);};
						}
						if(joy_down(&pom_nap))
						{
							
							Menu_down();
							_delay_ms(100);
							pom_nap = pomiar(PIN_ADC);
							while (joy_down(&pom_nap)) {pom_nap = pomiar(PIN_ADC);};
						}
						if(joy_right(&pom_nap))
						{
							_delay_ms(100);
							pom_nap = pomiar(PIN_ADC);
							while (joy_right(&pom_nap)) {pom_nap = pomiar(PIN_ADC);};
						}
						if(joy_up(&pom_nap))
						{
							Menu_up();
							_delay_ms(100);
							pom_nap = pomiar(PIN_ADC);
							while (joy_up(&pom_nap)) {pom_nap = pomiar(PIN_ADC);};

						}
						if(joy_push(&pom_nap))
						{
							Menu_push();
							gra = 1;
							_delay_ms(100);
							pom_nap = pomiar(PIN_ADC);
							while (joy_push(&pom_nap)) {pom_nap = pomiar(PIN_ADC);};
							Timer_on();
						
						}
					_delay_ms(50);
					//pom_nap = pomiar(PIN_ADC);
				}
			
		}
		
		while (gra)
		{

		pom_nap = pomiar(PIN_ADC);
			if (joy_dowolny(&pom_nap))
			{
				_delay_ms(50);
				pom_nap = pomiar(PIN_ADC);
				if (joy_dowolny(&pom_nap))
				{
					if(joy_up(&pom_nap))
					{
						//_delay_ms(50);
						snake_skret (1);

						//while (joy_up(&pom_nap)) {};
					}
					if(joy_down(&pom_nap))
					{
						//_delay_ms(50);
						snake_skret (3);

						//while (joy_down(&pom_nap)) {};
					}
					if(joy_right(&pom_nap))
					{
						//_delay_ms(50);
						snake_skret (2);

						//while (joy_right(&pom_nap)) {};
					}
					if(joy_left(&pom_nap))
					{
						//_delay_ms(50);
						snake_skret (4);

						//while (joy_left(&pom_nap)) {};
					}
					if(joy_push(&pom_nap))
					{
					//	_delay_ms(50);
					//	gra = 0; clr_scr(); Menu_init();

						//while (joy_push(&pom_nap)) {};
					}
				//pom_nap = pomiar(PIN_ADC);
				}
					//{gra = 0; clr_scr(); Menu_init();}
			}
			
			if (czy_grac_dalej == 0) {LCD_String("KONIEC", 22, 32, RED, WHITE); Timer_off();}

			while(czy_grac_dalej == 0) {};
			
		}

	}

}
