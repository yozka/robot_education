// Пример 2
// используется бибилотека NewPing
// Порядок установки библиотеки:
// 1. Скетч -> Подключить библиотеку -> Управлять бибилотеками...
// 2. В строке поиска набрать "NewPing", найти библиотеку 
// 2. В найденной библиотеке нажать кнопку "установка"

#include <NewPing.h>

NewPing sonar(PD3, PD2, 200);

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
	delay(50);
	Serial.print("Ping: ");
	Serial.print(sonar.ping_cm());
	Serial.println("cm");  
}
