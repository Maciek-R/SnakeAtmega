#include "joystick.h"
#include "ADC.h"

uint8_t joy_left(uint16_t * pom)
{
	if ((*pom < JOY_LEFT+50) && (*pom > JOY_LEFT-50)) return 1;

	return 0;
}
uint8_t joy_right(uint16_t * pom)
{
	if ((*pom < JOY_RIGHT+50) && (*pom > JOY_RIGHT-50)) return 1;

	return 0;
}
uint8_t joy_up(uint16_t * pom)
{
	if ((*pom < JOY_UP+50) && (*pom >= 0)) return 1;		//>=0 wazne !!!!

	return 0;
}
uint8_t joy_down(uint16_t * pom)
{
	if ((*pom < JOY_DOWN+50) && (*pom > JOY_DOWN-50)) return 1;

	return 0;
}
uint8_t joy_push(uint16_t * pom)
{
	if ((*pom < JOY_PUSH+50) && (*pom > JOY_PUSH-50)) return 1;

	return 0;
}
uint8_t joy_dowolny(uint16_t * pom)
{
	if (*pom < 1000) return 1;

	return 0;
}
