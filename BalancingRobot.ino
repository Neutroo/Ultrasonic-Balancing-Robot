#include <HCSR04.h>

//Motor driver pins
#define ENA       3
#define ABack     5
#define AForward  7
#define BBack     4
#define BForward  2
#define ENB       6

HCSR04 rangefinder(8, new int[3] {11, 10, 9}, 3);

void setup() 
{
  pinMode(ENA, OUTPUT);
  pinMode(ABack, OUTPUT);
  pinMode(AForward, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(BBack, OUTPUT);
  pinMode(BForward, OUTPUT);

  digitalWrite(ABack, LOW);
  digitalWrite(AForward, HIGH);
  digitalWrite(BBack, LOW);
  digitalWrite(BForward, HIGH);
}

uint8_t speedA = 120; 
uint8_t speedB = 120;  

uint8_t increaseA(int distance, uint8_t value)
{
  return value - distance;
}

uint8_t increaseB(int distance, uint8_t value)
{
  if (distance > 70)
    distance = 70;
  return distance - (value - 10);
}

void loop() 
{
  int distance = (int)rangefinder.dist(0);
  int rf1 = (int)rangefinder.dist(1);
  int rf2 = (int)rangefinder.dist(2);
  uint8_t balancingRf1 = 0, balancingRf2 = 0;
  
  if (rf1 > rf2)
  {
    balancingRf1 = rf1 - rf2;
    if (balancingRf1 > 50)
      balancingRf1 = 50;
  }
  else if (rf1 < rf2)
  {
    balancingRf2 = rf2 - rf1;
    if (balancingRf2 > 50)
      balancingRf2 = 50;
  }
  else 
    {
      balancingRf1 = 0;
      balancingRf2 = 0;
    }
 
  if (distance < 35)
  {
    analogWrite(ENA, speedA + increaseA(distance, 50) + abs(balancingRf2));                  
    analogWrite(ENB, speedB);                                           
  }
  else if (distance > 45)
  {
    analogWrite(ENA, speedA);   
    analogWrite(ENB, speedB + increaseB(distance, 50) + abs(balancingRf1));                  
  }
  else 
  {
    analogWrite(ENA, speedA);                  
    analogWrite(ENB, speedB);
  }
}
