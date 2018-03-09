int button = 2; //номер порта для кнопки
int led = 8; //номер порта для светодиода

void setup() //настройка
{
    pinMode(led, OUTPUT); //настроем порт светодиода на выход
    pinMode(button, INPUT); //настром порт кнопки на вход
}

void loop()
{
  if (digitalRead(button) == HIGH) //если нажата кнопка
  {
      digitalWrite(led, HIGH); //включить светодиод
  }
  else 
  {
      digitalWrite(led, LOW); //выключить светодиод
  }
}
