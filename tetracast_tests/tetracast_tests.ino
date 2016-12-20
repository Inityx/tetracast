//#include "db.h"
class Step4988
{
  private:
    byte stepPin, dirPin, enablePin;
  public:
    Step4988(byte stepPin, byte dirPin, byte enablePin);
    void rotate(int16_t deg);
    void microtate(long deg);
    void disable();
    void enable();
    
};

void Step4988::rotate(int16_t deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for(int16_t i=0; i<abs(deg*200/360); i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
}
unsigned long del = 140;
void Step4988::microtate(long deg)
{
  enable();
  digitalWrite(dirPin, deg < 0);
  for(long i=0; i < abs(deg); i++)
  {
    digitalWrite(stepPin, HIGH);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(del);
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
template <typename T>
struct Coord
{
  T x, y;
  Coord():x(0), y(0) {}
  Coord(T x, T y):
    x(x), y(y)
    {
    }
  Coord<T> operator-(const Coord<T>& p) const {
    return Coord<T>(x - p.x, y - p.y);
  }
  Coord(const Coord<T>& p):x(p.x), y(p.y) {}
};
typedef Coord<long> coord;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
}
//coord func (unsigned long t)
//{
//  coord result;
//  int scaleT = (t / 1000) % points;
//  result.x  = (signed char)pgm_read_byte_near(xvalues + scaleT)/3;
//  result.y = -(signed char)pgm_read_byte_near(yvalues + scaleT)/3;
//  return result;
//}
enum Pen: uint8_t {
  UP = LOW,
  DOWN = HIGH
};
void pen(uint8_t p)
{
  digitalWrite(7, p);
}
void stepris_draw(Coord<Step4988&> steppers, uint16_t blockCode)
{
  const int stepsize = 10;
  Coord<int> netDelta(0,0);
  Coord<int8_t> oldxy(0,0);
  const long freezetime = 12;
  int8_t x, y;
  for(uint16_t sh = blockCode; sh; sh >>= 4)
  {
    x = (sh & 0xC) >> 2;
    y = (sh & 0x2) >> 1;
    if(blockCode >> 4)
      pen(DOWN);
    steppers.x.microtate(stepsize * (x - netDelta.x));
    steppers.y.microtate(stepsize * (y - netDelta.y));
    delay(1);
    pen(UP);
    netDelta.x += (x - netDelta.x);
    netDelta.y += (y - netDelta.y);
    delay(freezetime);
    oldxy = Coord<int8_t>(x,y);
  }
  steppers.x.microtate(-stepsize * netDelta.x);
  steppers.y.microtate(-stepsize * netDelta.y);
}

void stepris_bdraw(Coord<Step4988&> steppers, uint8_t blockCode)
{
  const int stepsize = 10;
  Coord<int> delta(0,0);
  uint8_t last = (blockCode >> 6) & 0x3;
  for(uint8_t i = 0; i < 8; i+=2)
  {
    uint8_t c = (blockCode >> (6 - i)) & 3;
    int step = c & 2 ? -stepsize : stepsize;
//    if(i == 6 && c == (last ^ 0x2))
//      break;
    pen(DOWN);
    if(c & 1)
    {
      steppers.x.microtate(step);
      delta.x+= (c & 2) ? -1 : 1;
    }
    else
    {
      steppers.y.microtate(step);
      delta.y+= (c & 2) ? -1 : 1;
    }
    last = c & 3;
    delay(1);
    pen(UP);
  }
  steppers.x.microtate(-delta.x * stepsize);
  steppers.y.microtate(-delta.y * stepsize);
}
void loop() {
  // put your main code here, to run repeatedly:
  
  Step4988 ystepper(10, 9, 8);
  Step4988 xstepper(13, 12, 11);
  Coord<long> now,last;
//  last = func(0);
  Coord<Step4988&> steppers(xstepper, ystepper);
  uint8_t pieces[] = {
    0b01010010, //J
    0b00000111, //L
    
  };
  while(true)
  {
    pen(DOWN);
    //stepris_draw(steppers, 0x159B);
    delay(2);
    stepris_bdraw(steppers, pieces[0]);
    pen(UP);
    ystepper.microtate(-40);
    pen(DOWN);
    delay(2);
    stepris_draw(Coord<Step4988&>(xstepper, ystepper), 0x159B);
    pen(UP);
    ystepper.microtate(40);
  }

}
