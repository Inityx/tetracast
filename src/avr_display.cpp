#include "avr_aux/fastio.hpp"
#include "avr_aux/arduino_pins.hpp"
#include <util/delay.h>
#ifndef _BV
#define _BV(x) (1<<(x))
#endif

int main()
{
    Pin led   = arduino::PIN[13];
    Pin laser = arduino::PIN[7];

    fastpm<led>(OUTPUT);
    //fastpm<laser>(OUTPUT);

	while(1)
	{
        fastdw <led>   (1);
        //fastdw <laser> (0);
		_delay_us(200);
        fastdw <led>   (0);
        //fastdw <laser> (1);
		_delay_us(300);
	}
}

