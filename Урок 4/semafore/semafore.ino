#include "led.h"
#include "light.h"

ALed   lRed      (A0);  //красный светодиод
ALed   lYellow   (A1);  //желтый светодиод
ALed   lGreen    (A2);  //зеленый светодиод

ALight light(lRed, lYellow, lGreen); //светофор

//настройка
void setup() 
{
   light.off(); //выключим светофор
   //кнопка
   pinMode(A3, INPUT_PULLUP);
}

//основной цикл
void loop() 
{
    light.red(); //включим красный цыет на светофоре
    while (digitalRead(A3) == HIGH)
    {
        delay(100);
    }
    
    light.yellow();
    delay(1000);
    light.green();
    delay(2000);
    light.yellow();
    delay(1000);
}
