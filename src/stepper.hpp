#ifndef STEPPER
#define STEPPER

//class for using the Pololu A4988 stepper motor driver chip

template <
	Pin pin_enable,
	Pin pin_clk,
	Pin pin_dir>
class Stepper
{
	private:
	public:
		void init();

};

#endif
