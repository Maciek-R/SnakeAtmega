#ifndef przyciski_h
#define przyciski_h

#define KEY_PUSH	(1<<PD7)
#define KEY_RIGHT	(1<<PD6)
#define KEY_DOWN	(1<<PD5)
#define KEY_LEFT	(1<<PD4)
#define KEY_UP		(1<<PD3)

#define KEY_PORT 	PORTD
#define KEY_DDR		DDRD
#define KEY_PIN		PIND

#define KEY_PUSH_DOWN		(!(KEY_PIN & KEY_PUSH))
#define KEY_RIGHT_DOWN		(!(KEY_PIN & KEY_RIGHT))
#define KEY_DOWN_DOWN		(!(KEY_PIN & KEY_DOWN))
#define KEY_LEFT_DOWN		(!(KEY_PIN & KEY_LEFT))
#define KEY_UP_DOWN			(!(KEY_PIN & KEY_UP))

#define KEY_NACIS	(KEY_PUSH_DOWN || KEY_RIGHT_DOWN || KEY_DOWN_DOWN || KEY_LEFT_DOWN || KEY_UP_DOWN)

void Key_init()
{
	KEY_DDR &= ~(KEY_PUSH | KEY_RIGHT | KEY_DOWN | KEY_LEFT | KEY_UP);
	KEY_PORT |= (KEY_PUSH | KEY_RIGHT | KEY_DOWN | KEY_LEFT | KEY_UP);
}

#endif
