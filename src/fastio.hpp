#ifndef FASTIO
#define FASTIO

#define _SFR_ASM_COMPAT 1
#include <avr/io.h>

typedef const uint16_t Pin;
//#define Pin constexpr uint16_t
#define to_pin(port,pin) ((port << 8) | pin)
#define p_port(pin) ((pin >> 8) - 0)
#define p_ddr(pin)  ((pin >> 8) - 1)
#define p_pin(pin)  ((pin >> 8) - 2)
#define p_bit(pin)   (pin & 0x03)

template <int p, int i>
inline void faston()
{
	asm volatile("sbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));
}

template <int p, int i>
inline void fastoff()
{
	asm volatile("cbi %0, %1\n":: "I" (_SFR_IO_ADDR(p)), "M" (i));
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

//fast digitalWrite <pin> (value)
template <Pin pin>
inline void fastdw(bool value)
{
	fastdw<p_port(pin), p_bit(pin)> (value);
}

//fast pinMode <pin> (direction)
// (1 = out, 0 = in)
template <Pin pin>
inline void fastpm(bool dir)
{
	fastdw<p_ddr(pin), p_bit(pin)> (dir);
}


inline void digitalwrite(int& pin, bool value)
{
	if(value)
		to_reg(p_port(pin)) |=  _BV(p_bit(pin));
	else
		to_reg(p_port(pin)) &= ~_BV(p_bit(pin));
}




#endif
