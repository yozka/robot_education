#include <CapacitiveSensor.h>
CapacitiveSensor   ss = CapacitiveSensor(A0, A1);

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
    long total1 =  ss.capacitiveSensor(30);
    Serial.println(total1);
    delay(10);  
}
