#define _SFR_ASM_COMPAT 1
#include <avr/io.h>
#include <util/delay.h>

//memory and computing speed are tight.
//global variables will be used occasionally for optimization purposes.
//this version of the driver software will use 2 stepper motors
//driven by Pololu A49888 stepper motor drivers
//
//currently it's just full of a bunch of experimental crap

template <int p, int i>
inline void faston()
{
	asm volatile("sbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));
}

inline volatile uint8_t& to_reg(uint8_t reg) {
	  return *reinterpret_cast<volatile uint8_t*>(reg);
}
template <int p, int i>
inline void fastdw(bool v)
{
	if(v)
		asm volatile("sbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));
	else
		asm volatile("cbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));

}

template <int p, int i>
inline void fastoff()
{
	asm volatile(
			"cbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));
}


int main()
{
	to_reg(DDRB) |= _BV(5);
	while(1)
	{
		fastdw<PORTB, PB5>(1);
		_delay_ms(500);
		fastdw<PORTB, PB5>(0);
		_delay_ms(500);
	}
}

