int button = 2; //номер порта для кнопки
int led = 8; //номер порта для светодиода

void setup() //настройка
{
    pinMode(led, OUTPUT); //настроем порт светодиода на выход
    pinMode(button, INPUT); //настром порт кнопки на вход
}

void loop()
{
    
    int tm = millis(); //засекаем время
    while (digitalRead(button) == HIGH)
    {
        //пустой цикл
        //ждем когда нажата кнопка
    }

    //кнопку отпустили
    //высчитываем время когда была нажата кнопка
    int time = millis() - tm;

    if (time > 100)
    {
        digitalWrite(led, HIGH); //включить светодиод
        delay(time);
        digitalWrite(led, LOW); //выключить светодиод
    }
}
