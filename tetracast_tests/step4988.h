#ifndef STEP4988_H
#define STEP4988_H

//class definition for Pololu A4988 stepper motor driver

template <typename T>
class Coord;
class Step4988
{
  private:
    byte stepPin, dirPin, enablePin;
  public:
    static long del;
    Step4988(byte stepPin, byte dirPin, byte enablePin);
    void rotate(int16_t deg);
    void microtate(long deg);
    void disable();
    void enable();
    friend void microtate(Coord<Step4988&> steps, const Coord<long>& deg);

};


#endif


