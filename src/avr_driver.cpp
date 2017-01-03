#include "fastio.hpp"
#include <util/delay.h>

//memory and computing speed are tight.
//global variables will be used occasionally for optimization purposes.
//this version of the driver software will use 2 stepper motors
//driven by Pololu A49888 stepper motor drivers
//
//currently it's just full of a bunch of experimental crap




int main()
{
	Pin led = to_pin(PORTB, PB5);

	to_reg(DDRB) |= _BV(5);

	while(1)
	{
		fastdw<led>(1);
		_delay_ms(500);
		fastdw<led>(0);
		_delay_ms(500);
	}
}

