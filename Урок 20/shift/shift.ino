//Линия переброса данных на внешние ноги
//Пин подключен к ST_CP входу 74HC595
const int st_pin = 13;

//Линия передача данных в ячейку
//Пин подключен к SH_CP входу 74HC595
const int sh_pin = 12;

//Линия данных
//Пин подключен к DS входу 74HC595
const int data_pin = 11;

void setup() 
{
  //устанавливаем режим
  pinMode(st_pin, OUTPUT);
  pinMode(sh_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}

//функция возвращает код символа
byte code(const int number)
{
    /*   1
     * 2   0
     *   3
     * 6   4 
     *   5
     */
    switch (number)
    {
        case 0 : return 0b01110111;
        case 1 : return 0b00010001;
        case 2 : return 0b01101011;
        case 3 : return 0b00111011;
        case 4 : return 0b00011101;
        case 5 : return 0b00111110;
        case 6 : return 0b01111110;
        case 7 : return 0b00010011;
        case 8 : return 0b01111111;
        case 9 : return 0b00111111;
    }
    return 0;
}

//запись числа в сдвиговый регистр
void shift(const byte v)
{
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(sh_pin, LOW);
        digitalWrite(data_pin, v & (1 << i ));
        digitalWrite(sh_pin, HIGH);
    }
    digitalWrite(st_pin, HIGH); 
    digitalWrite(st_pin, LOW);
}

 void loop() 
{
  for (int i = 0; i < 10; i++) 
  {
      shift(code(i)); 
      // пауза перед следующей итерацией
      delay(1000);
  }
}