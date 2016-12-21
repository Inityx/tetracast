#include "step4988.h"
long Step4988::del = 800;
void Step4988::rotate(int16_t deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for (int16_t i = 0; i < abs(deg * 200 / 360); i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}
void Step4988::microtate(long deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for (long i = 0; i < abs(deg); i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(Step4988::del);
  }
}
void Step4988::enable()
{
  digitalWrite(enablePin, 0);
}

void Step4988::disable()
{
  digitalWrite(enablePin, 1);
}

Step4988::Step4988(byte stepPin, byte dirPin, byte enablePin):
  stepPin(stepPin), dirPin(dirPin), enablePin(enablePin)
{
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
}
