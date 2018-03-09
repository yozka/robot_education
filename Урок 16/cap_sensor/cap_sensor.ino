int rpin  = PD4;     // Пин, который принимает сигнал
int spin  = PD3;     // Пин, который отправляет сигнал
int led   = PD2;     // Светодиод
 
void setup() 
{
  pinMode(spin, OUTPUT);
  pinMode(rpin, INPUT);
  pinMode(led, OUTPUT);
}

int touch()//функция считывает сенсор
{
  int total = 0;
  noInterrupts(); //отключим прерывания
  
  digitalWrite        (spin, LOW);
  pinMode             (rpin, OUTPUT);
  digitalWrite        (rpin, HIGH);
  delayMicroseconds   (10);
  digitalWrite        (rpin, LOW);
  delayMicroseconds   (10);
  
  pinMode(rpin, INPUT);
  digitalWrite(spin, HIGH); // Отправляем сигнал 
  
  while(digitalRead(rpin) == LOW) //цикл
  {
      //считаем пока непоявился сигнал
      total++;
  }
  digitalWrite(spin, LOW); // Останавливаем передачу сигнала
  interrupts();//включим прерывания
  return total;    
}
 
void loop() //основной цикл
{
    int ms = 0; //количество измерений
    for (int i = 0; i < 30; i++) //сделаем 30 измерений
    {
        ms += touch();
    }
    if(ms > 5) 
    {
        //если измерений больше 5 то включим светодиод
        digitalWrite(led, HIGH);
    }
    else
    {
        digitalWrite(led, LOW);
    }
    delay(10);
}
 

