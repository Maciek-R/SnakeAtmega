#include "snake.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "N6100.h"

static uint8_t piksele = 8;			//szerokosc i dlugosc jednego znaku
#define szerokosc 16        		//szerokosc i dlugosc pola gry

static volatile int8_t glowa_x = 5;
static volatile int8_t glowa_y = 7;			//x gora dol     y lewo prawo

static volatile int8_t ogon_x = 5;
static volatile int8_t ogon_y = 5;

static uint8_t przes = 2; //ilosc pikseli do wyrownania na ekranie

static uint8_t kierunek = 2;	//0 puste 1 gora 2 prawo 3 dol 4 lewo

volatile uint8_t czy_grac_dalej = 1;

//-------------------------------
//Snake * pocz_weza;	//pierwszy element weza zaczynajac od ogona
//pocz_weza = malloc (sizeof(Snake));

static volatile uint8_t pole_gry[szerokosc][szerokosc];

void plansza_init()
{
	uint8_t i;
	uint8_t j;
	
	for (i=0; i<szerokosc; ++i)
		for (j=0; j<szerokosc; ++j)
		{
			pole_gry[i][j] = 0;
		}
	pole_gry[glowa_x][glowa_y] = 2;							//prawo
	pole_gry[(glowa_x+ogon_x)/2][(glowa_y+ogon_y)/2] = 2;
	pole_gry[ogon_x][ogon_y] = 2;
}

static void pokoloruj_za_glowa()
{
	//static uint8_t strona = 2;

	if (kierunek == 1)
	{
		if (pole_gry[glowa_x+1][glowa_y]==1) //dol gora
			LCD_Char(136, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x][glowa_y-1]==2) //lewo gora
			LCD_Char(139, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x][glowa_y+1]==4) //prawo gora
			LCD_Char(140, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	}
	else if (kierunek == 2)
	{
		if (pole_gry[glowa_x][glowa_y-1]==2) //lewo prawo
			LCD_Char(137, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x-1][glowa_y]==3) //gora prawo
			LCD_Char(140, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x+1][glowa_y]==1) //dol prawo
			LCD_Char(141, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	}
	else if (kierunek == 3)
	{
		if (pole_gry[glowa_x-1][glowa_y]==3) //gora dol
			LCD_Char(136, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x][glowa_y-1]==2) //lewo dol 
			LCD_Char(138, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x][glowa_y+1]==4) //prawo dol
			LCD_Char(141, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	}
	else if (kierunek == 4)
	{
		if (pole_gry[glowa_x][glowa_y+1]==4) //prawo lewo
			LCD_Char(137, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x-1][glowa_y]==3) //gora lewo
			LCD_Char(139, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
		else if (pole_gry[glowa_x+1][glowa_y]==1) //dol lewo
			LCD_Char(138, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	}
}

void snake_init()
{	
	//rysowanie obramowania
	uint8_t i;
	for (i=0; i<szerokosc; ++i)			//gora
		LCD_Char('#', 0+przes, i*piksele + przes, BLUE, WHITE);
	for (i=0; i<szerokosc; ++i)
		LCD_Char('#', (szerokosc-1)*piksele + przes, i*piksele + przes, BLUE, WHITE);	//dol
	for (i=0; i<szerokosc; ++i)
		LCD_Char('#', i*piksele + przes, 0 + przes, BLUE, WHITE);	//lewo
	for (i=0; i<szerokosc; ++i)
		LCD_Char('#', i*piksele + przes, (szerokosc-1)*piksele + przes, BLUE, WHITE);	//prawo
	
	//rysowanie weza
	LCD_Char(129, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);	//129 to glowa w prawo
	LCD_Char(137, ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);
	LCD_Char(133, ((glowa_x+ogon_x)/2)*piksele + przes, ((glowa_y+ogon_y)/2)*piksele + przes, GREEN, WHITE);
}

static uint8_t czy_crash()
{
	if (glowa_x >= 15 || glowa_x < 1) return 1;		//sprawdzanie czy uderzyl w sciane
	if (glowa_y >= 15 || glowa_y < 1) return 1;

	if (pole_gry[glowa_x][glowa_y] > 0) return 1;  //czy uderzyl w siebie

	return 0;
}

static uint8_t ruch_weza()		//1 udalo sie 0 koniec gry
{
	LCD_Char(' ', glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	pokoloruj_za_glowa();

	if (kierunek == 1)
	{
		--glowa_x;
	}
	else if (kierunek == 2)
	{
		++glowa_y;
	}
	else if (kierunek == 3)
	{
		++glowa_x;
	}
	else if (kierunek == 4)
	{
		--glowa_y;
	}

	if (czy_crash()) return 0;

	pole_gry[glowa_x][glowa_y] = kierunek;

	LCD_Char(' ', ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);

	if (pole_gry[ogon_x][ogon_y]==1)
	{
		pole_gry[ogon_x][ogon_y]=0;
		--ogon_x;
	}
	else if (pole_gry[ogon_x][ogon_y]==2)
	{
		pole_gry[ogon_x][ogon_y]=0;
		++ogon_y;
	}
	else if (pole_gry[ogon_x][ogon_y]==3)
	{
		pole_gry[ogon_x][ogon_y]=0;
		++ogon_x;
	}
	else if (pole_gry[ogon_x][ogon_y]==4)
	{
		pole_gry[ogon_x][ogon_y]=0;
		--ogon_y;
	}
//rysowanie ogona
	LCD_Char(' ', ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);

	if (pole_gry[ogon_x][ogon_y]==1)
		LCD_Char(132, ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);
	if (pole_gry[ogon_x][ogon_y]==2)
		LCD_Char(133, ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);
	if (pole_gry[ogon_x][ogon_y]==3)
		LCD_Char(134, ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);
	if (pole_gry[ogon_x][ogon_y]==4)
		LCD_Char(135, ogon_x*piksele + przes, ogon_y*piksele + przes, GREEN, WHITE);
//rysowanie glowy
	
	if (kierunek==1)
		LCD_Char(128, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	else if (kierunek==2)
		LCD_Char(129, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	else if (kierunek==3)
		LCD_Char(130, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	else if (kierunek==4)
		LCD_Char(131, glowa_x*piksele + przes, glowa_y*piksele + przes, GREEN, WHITE);
	
	return 1;
}

void snake_skret(uint8_t x)
{	
	if (kierunek == 1 && x == 3) return;
	if (kierunek == 3 && x == 1) return;
	if (kierunek == 2 && x == 4) return;
	if (kierunek == 4 && x == 2) return;

	kierunek = x;
	pole_gry[glowa_x][glowa_y] = x;
}


ISR (TIMER0_COMP_vect)
{
static uint8_t x = 0;
//static uint8_t y = 10;
	if (++x == 125) x = 0;			//co sekunde ruch weza

	if (x==0)
		//ruch_weza();
		//LCD_Char('X', y+=10, 5, RED, WHITE);
		czy_grac_dalej = ruch_weza();	//1 dalej 0 koniec
}
