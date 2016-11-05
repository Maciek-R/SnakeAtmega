#include "menu.h"
#include <avr/io.h>
#include "N6100.h"
#include "snake.h"
//#include "FONT8x8.h"

/*menu[0] = "START";
menu[1] = "WYNIKI";
menu[2] = "EXIT";

pozycja_menu_poziom[0] = 50;
pozycja_menu_poziom[1] = 58;
pozycja_menu_poziom[2] = 66;

pozycja_menu_pion[0] = 48;
pozycja_menu_pion[1] = 44;
pozycja_menu_pion[2] = 48;

akt_menu = 0;*/

static char * menu[DL_MENU] = {"START", "WYNIKI", "EXIT"};
static uint8_t pozycja_menu_poziom[DL_MENU] = {50, 58, 66};
static uint8_t pozycja_menu_pion[DL_MENU] = {48, 44, 48};
static uint8_t akt_menu = 0;

void Menu_init()
{
/*char * menu[DL_MENU] = {"START", "WYNIKI", "EXIT"};
uint8_t pozycja_menu_poziom[DL_MENU] = {50, 58, 66};
uint8_t pozycja_menu_pion[DL_MENU] = {48, 44, 48};
uint8_t akt_menu = 0;*/
		

uint8_t i;
LCD_String("     SNAKE    ", 30, 8, GREEN, WHITE);

for (i=0; i<DL_MENU; ++i)
	LCD_String(menu[i], pozycja_menu_poziom[i], pozycja_menu_pion[i], RED, WHITE);
			

LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], GREEN, RED);

}

void Menu_up()
{
	LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], RED, WHITE);
	if (akt_menu==0) akt_menu = 2;
	else --akt_menu;
	LCD_String("                ", pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], WHITE, WHITE);
	LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], GREEN, RED);
}

void Menu_down()
{
	LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], RED, WHITE);
	if (++akt_menu>=3) akt_menu = 0;
	LCD_String("                ", pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], WHITE, WHITE);
	LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], GREEN, RED);
}

void Menu_push()
{
	if (akt_menu==0)
	{
		clr_scr();
		snake_init();
		plansza_init();
	}
}
void clr_scr()
{
	LCD_Box(0,0,131,131,FILL,WHITE);
}
