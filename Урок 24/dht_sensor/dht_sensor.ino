#include <SimpleDHT.h> //подключение библиотеки

SimpleDHT11 dht; //создание датчика
const int pinDht = 2; //цифровой пин, ккоторому подключен датчик


unsigned long timeUpdate = 0; //время обновления датчика


void setup() 
{
    Serial.begin(9600);//инциализация порта вывода
}


void loop() 
{
    // Задержка 2 секунды между измерениями
    const auto time = millis(); //текущее время
    if (time > timeUpdate)
    {
        //пришло время
        timeUpdate = time + 2000; //установим новое время на перед в 2 секунды

        //делаем новое измерение
        byte temperature = 0; //температура
        byte humidity = 0; //влажность
        const auto code = dht.read(pinDht, &temperature, &humidity, NULL);  
        if (code == SimpleDHTErrSuccess)
        {
            //ошибок нет, можно прочитать даныне
            Serial.print("Влажность: ");
            Serial.print(humidity);
            Serial.print(" %\t Температура: ");
            Serial.print(temperature);
            Serial.println(" *C ");
        }
    }
    //

    
}
