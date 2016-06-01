/*
 *  Wireless eStop Program
 */

int RCPin = 7;
int RelayPin = 4;
unsigned long duration;

void setup()
{
  pinMode(RCPin, INPUT);
  pinMode(RelayPin, OUTPUT);  
  
}

void loop()
{
  duration = pulseIn(RCPin, HIGH);
  if (duration >  1500)
    digitalWrite(RelayPin, HIGH);
  else
    digitalWrite(RelayPin, LOW);  
}
