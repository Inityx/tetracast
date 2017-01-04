#ifndef STEPPER
#define STEPPER

#include "fastio.hpp"
#include <util/delay.h>
#include <stdlib.h>

//class for using the Pololu A4988 stepper motor driver chip

template <
    Pin pin_enable, //    EN on A4988 (active low)
    Pin pin_clk,    //  STEP on A4988 (rising edge trigger)
    Pin pin_dir     //   DIR on A4988 (1 = CW, 0 = CCW)
>
class Stepper {
    private:
    public:
        void init() {
            fastpm <pin_enable> (OUTPUT);
            fastpm <pin_clk>    (OUTPUT);
            fastpm <pin_dir>    (OUTPUT);
            fastdw <pin_enable> (1); 
        }
        
        inline void step() {
            fastdw <pin_clk> (1);
            _delay_us(2);
            fastdw <pin_clk> (0);
            _delay_us(2);
        }

        void rotate(int16_t steps) {
            uint16_t absteps = abs(steps);
            fastdw <pin_dir> (steps > 0); //set rotation direction
            for(; absteps; absteps--)
                step();
        }

        inline void enable() {
            fastoff <pin_enable>();
        }

        inline void disable() {
            faston <pin_enable>();
        }
};

#endif
