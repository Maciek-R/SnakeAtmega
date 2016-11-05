#ifndef menu_h
#define menu_h

#define DL_MENU 3
	
/*extern char * menu[DL_MENU];
extern uint8_t pozycja_menu_poziom[DL_MENU];
extern uint8_t pozycja_menu_pion[DL_MENU];
extern uint8_t akt_menu;*/


void Menu_init();
/*{
	uint8_t i;
	LCD_String("     SNAKE    ", 30, 8, GREEN, WHITE);

	for (i=0; i<DL_MENU; ++i)
		LCD_String(menu[i], pozycja_menu_poziom[i], pozycja_menu_pion[i], RED, WHITE);
			

	LCD_String(menu[akt_menu], pozycja_menu_poziom[akt_menu], pozycja_menu_pion[akt_menu], GREEN, RED);

}*/
void Menu_up();
void Menu_down();
void Menu_push();


void clr_scr();

/*char * menu[DL_MENU] = {"START", "WYNIKI", "EXIT"};
uint8_t pozycja_menu_poziom[DL_MENU] = {50, 58, 66};
uint8_t pozycja_menu_pion[DL_MENU] = {48, 44, 48};
uint8_t akt_menu = 0;*/



#endif
