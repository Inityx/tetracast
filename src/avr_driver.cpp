#include "avr_aux/fastio.hpp"
#include "avr_aux/stepper.hpp"
#include <util/delay.h>

//memory and computing speed are tight.
//global variables will be used occasionally for optimization purposes.
//this version of the driver software will use 2 stepper motors
//driven by Pololu A49888 stepper motor drivers
//
//note: currently just blinks an LED



int main()
{
    Pin led = to_pin(PORTB, PB5);

    Pin 
        en  = to_pin(PORTB, PB2),
        clk = to_pin(PORTB, PB3),
        dir = to_pin(PORTB, PB4);

    Stepper <en, clk, dir> myStepper;

    myStepper.init();


    fastpm<led>(OUTPUT);
    

    while(1)
    {
        fastdw<led>(1);
        _delay_ms(500);
        fastdw<led>(0);
        _delay_ms(500);
    }
}

