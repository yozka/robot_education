//описание пинов
int ir      = A0;   //инфакрасный приемник
int irLed   = PD3;  //инфакрасный светодиод
int led     = PD2;  //светодиод

void setup() //настройка
{
    pinMode(led,    OUTPUT); //настроем порт светодиода на выход
    pinMode(irLed,  OUTPUT); //настроем порт инфокрасного на выход
    pinMode(ir,     INPUT);  //настроем порт инфокрасного приемника на вход
}

//основной цикл
void loop()
{
    //опрос датчика
    digitalWrite(irLed, HIGH); //включить инфокрасный светодиод
    bool sensor = false;
    int level = analogRead(ir); //прочитам напряжение от 0 до 1024 едениц
    if (level < 700) //порог 700 едениц, значит есть отраженный сигнал
    {
        sensor = true; //отраженный сигнал есть
    }
    digitalWrite(irLed, LOW); //выключим инфокрасный светодиод
    //


    //результат покажем на светодиоде
    if (sensor)
    {
        digitalWrite(led, HIGH); //включить светодиод
    }
    else 
    {
        digitalWrite(led, LOW); //выключить светодиод
    }
}
