#ifndef ARDUINO_PINS
#define ARDUINO_PINS
#include "fastio.hpp"

namespace arduino
{
#if defined(PLATFORM_UNO)
    //pin defs for Arduino UNO
    constexpr uint16_t APIN[] = {
        to_pin(PORTC, PC0), //pin A0
        to_pin(PORTC, PC1), //pin A1
        to_pin(PORTC, PC2), //pin A2
        to_pin(PORTC, PC3), //pin A3
        to_pin(PORTC, PC4), //pin A4
        to_pin(PORTC, PC5), //pin A5
    };
    constexpr uint16_t PIN[] = {
        to_pin(PORTD, PD0), //pin 0
        to_pin(PORTD, PD1), //pin 1
        to_pin(PORTD, PD2), //pin 2
        to_pin(PORTD, PD3), //pin 3
        to_pin(PORTD, PD4), //pin 4
        to_pin(PORTD, PD5), //pin 5
        to_pin(PORTD, PD6), //pin 6
        to_pin(PORTD, PD7), //pin 7
        to_pin(PORTB, PB0), //pin 8
        to_pin(PORTB, PB1), //pin 9
        to_pin(PORTB, PB2), //pin 10
        to_pin(PORTB, PB3), //pin 11
        to_pin(PORTB, PB4), //pin 12
        to_pin(PORTB, PB5), //pin 13
    };
#else
#error "Invalid platform specified. See arduino_pins.hpp for valid options."
#endif

}
#endif
