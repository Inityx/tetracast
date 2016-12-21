//#include "db.h"
#include "step4988.h"
#include "coord.h"

typedef Coord<long> mov_c;
void microtate(Coord<Step4988&> steps, const mov_c& deg)
{
  digitalWrite(steps.x.dirPin, deg.x < 0);
  digitalWrite(steps.y.dirPin, deg.y < 0);
  mov_c ab (abs(deg.x), abs(deg.y));
  for (long i = 0; i < max(ab.x, ab.y); i++)
  {
    if (i < ab.x)
    {
      digitalWrite(steps.x.stepPin, HIGH);
      digitalWrite(steps.x.stepPin, LOW);
    }
    if (i < ab.y)
    {
      digitalWrite(steps.y.stepPin, HIGH);
      digitalWrite(steps.y.stepPin, LOW);
    }
    delayMicroseconds(Step4988::del);
  }
}
const int STEP_SIZE = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}
enum Pen : uint8_t {
  UP = LOW,
  DOWN = HIGH
};
void pen(uint8_t p)
{
  digitalWrite(7, p);
}
void stepris_draw(Coord<Step4988&> steppers, uint16_t blockCode)
{
  const int stepsize = STEP_SIZE;
  Coord<int> netDelta(0, 0);
  Coord<int8_t> oldxy(0, 0);
  const long freezetime = 12;
  int8_t x, y;
  for (uint16_t sh = blockCode; sh; sh >>= 4)
  {
    x = (sh & 0xC) >> 2;
    y = (sh & 0x2) >> 1;
    if (blockCode >> 4)
      pen(DOWN);
    steppers.x.microtate(stepsize * (x - netDelta.x));
    steppers.y.microtate(stepsize * (y - netDelta.y));
    delay(1);
    pen(UP);
    netDelta.x += (x - netDelta.x);
    netDelta.y += (y - netDelta.y);
    delay(freezetime);
    oldxy = Coord<int8_t>(x, y);
  }
  steppers.x.microtate(-stepsize * netDelta.x);
  steppers.y.microtate(-stepsize * netDelta.y);
}

void stepris_bdraw(Coord<Step4988&> steppers, uint8_t blockCode)
{
  const int stepsize = STEP_SIZE;
  mov_c delta(0, 0);
  uint8_t last = (blockCode >> 6) & 0x3;
  for (uint8_t i = 0; i < 8; i += 2)
  {
    uint8_t c = (blockCode >> (6 - i)) & 3;
    int step = c & 2 ? -stepsize : stepsize;
    //    if(i == 6 )
    //      break;
    delayMicroseconds(500);
    pen(DOWN);
    if (c & 1)
    {
      steppers.x.microtate(step);
      delta.x += (c & 2) ? -1 : 1;
    }
    else
    {
      steppers.y.microtate(step);
      delta.y += (c & 2) ? -1 : 1;
    }
    last = c & 3;
    //delay(1);
    pen(UP);
  }
  steppers.x.microtate(-delta.x * stepsize);
  steppers.y.microtate(-delta.y * stepsize);
}

void loop() {
  // put your main code here, to run repeatedly:

  Step4988 ystepper(10, 9, 8);
  Step4988 xstepper(13, 12, 11);
  Coord<Step4988&> steppers(xstepper, ystepper);
  uint8_t pieces[] = {
    0b01010010, //J
    0b00000111, //L
    0b01000111, //Z
    0b00010010, //S
    0b01001110, //O
    0b01001001, //T
    0b00000010, //I
  };
  int jump_size = STEP_SIZE * 4;
  while (true)
  {
    mov_c netDelta(0, 0);
    for (int i = 0; i < sizeof(pieces); i++)
    {
      delayMicroseconds(300); //for laser to stabilize
      pen(DOWN);
      stepris_bdraw(steppers, pieces[i]);
      pen(UP);
      mov_c movement = (i%4 == 3) ? 
        mov_c(1, -3):
        mov_c(0, 1);
      microtate(steppers, movement * jump_size);
      netDelta += movement;
//      if (i % 4 == 3)
//      {
//        xstepper.microtate(jumpsize);
//        ystepper.microtate(-3 * jumpsize);
//        netDelta.x++;
//        netDelta.y -= 3;
//      }
//      else
//      {
//        ystepper.microtate(jumpsize);
//        netDelta.y++;
//      }
    }
    microtate(steppers, netDelta * (-jump_size));
    Step4988::del = Step4988::del * 98  / 100;
    if(Step4988::del < 140)
      Step4988::del = 1000;
//    ystepper.microtate(-jumpsize * netDelta.y);
//    xstepper.microtate(-jumpsize * netDelta.x);
//    //stepris_drawgrid(steppers, 4, 4);
    while (Serial.available())
    {
      switch (Serial.read())
      {
        case 'w': ystepper.microtate(-STEP_SIZE); break;
        case 's': ystepper.microtate( STEP_SIZE); break;
        case 'a': xstepper.microtate(-STEP_SIZE); break;
        case 'd': xstepper.microtate( STEP_SIZE); break;
        case 'x': Step4988::del = Step4988::del * 102 / 100; break;
        case 'c': Step4988::del = Step4988::del * 98  / 100; break;
        default: break;
      }
      delay(1);
    }
  }


}
