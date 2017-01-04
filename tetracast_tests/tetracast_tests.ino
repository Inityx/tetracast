//#include "db.h"
#include "step4988.h"
#include "coord.h"

typedef Coord<long> mov_c;

enum Pen : uint8_t {
  UP = HIGH,
  DOWN = LOW
};
bool drawdots = false;
uint8_t pen_val;
void pen(uint8_t p)
{
  digitalWrite(7, p);
  pen_val = p;
}
int STEP_SIZE = 8;


void microtate(Coord<Step4988&> steps, const mov_c& deg)
{
  static int j;
  digitalWrite(steps.x.dirPin, deg.x > 0);
  digitalWrite(steps.y.dirPin, deg.y > 0);
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
    
    if(!(j++%STEP_SIZE) && pen_val == UP && drawdots)
    {
      pen(DOWN);
      delayMicroseconds(Step4988::del / 4);
      pen(UP);
      delayMicroseconds(Step4988::del * 3 / 4);
    }
    else
      delayMicroseconds(Step4988::del);
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
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

void stepris_bdraw(Coord<Step4988&> steppers, uint8_t blockCode, mov_c& delta)
{
  uint8_t last = (blockCode >> 6) & 0x3;
  for (uint8_t i = 0; i < 8; i += 2)
  {
    mov_c m_delta (0,0);
    uint8_t c = (blockCode >> (6 - i)) & 3;
    int step = c & 2 ? -1 : 1;
    if((i == 6) && (c == (last ^ 0x2)))
      break;
    delayMicroseconds(200);
    pen(DOWN);
    if (c & 1)
      m_delta.x = step;
    else
      m_delta.y = step;
    microtate(steppers, m_delta * STEP_SIZE);
    last = c & 3;
    pen(UP);
    delta += m_delta;
  
  }
  delayMicroseconds(3000);
  //steppers.x.microtate(-delta.x * stepsize);
  //steppers.y.microtate(-delta.y * stepsize);
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
  int jump_size = 4;
  while (true)
  {
    mov_c netDelta(0, 0);
    for (int i = 0; i < sizeof(pieces); i++)
    {
      delayMicroseconds(300); //for laser to stabilize
      pen(DOWN);
      mov_c cDelta(0,0);
      stepris_bdraw(steppers, pieces[i], cDelta); //draw piece
      netDelta += cDelta;
      pen(UP);
      mov_c movement;
      switch(i%4)
      {
        case 0: movement = mov_c(-1,  0); break;
        case 1: 
        case 3: movement = mov_c( 0,  1); break;
        case 2: movement = mov_c( 1,  0); break;
      }
      movement = movement * jump_size - cDelta;
      microtate(steppers, movement * STEP_SIZE);
      netDelta += movement;
        
    }
    microtate(steppers, netDelta * (-STEP_SIZE));
    netDelta = mov_c(0,0);
    if(Step4988::del < 140)
      Step4988::del = 1000;
    while (Serial.available())
    {
      switch (Serial.read())
      {
        case 'q': STEP_SIZE--; break;
        case 'e': STEP_SIZE++; break;
        case 'w': ystepper.microtate(-STEP_SIZE); break;
        case 's': ystepper.microtate( STEP_SIZE); break;
        case 'a': xstepper.microtate(-STEP_SIZE); break;
        case 'd': xstepper.microtate( STEP_SIZE); break;
        case 'x': Step4988::del = Step4988::del * 102 / 100; break;
        case 'c': Step4988::del = Step4988::del * 98  / 100; break;
        case 'f': drawdots ^= 1; break;
        default: break;
      }
      delay(1);
    }
  }


}
