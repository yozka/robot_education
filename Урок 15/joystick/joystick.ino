#include <Servo.h> //подключаем библиотеку управления сервами

const int servo1 = 5;       // пин первой сервы
const int servo2 = 6;       // пин второй сервы
const int joyH = A0;        // пин джойстика по горизонтали
const int joyV = A1;        // пин джойстика по вертикали

Servo myservo1;  // объявление объекта первой сервы
Servo myservo2;  // объект вторя серва

void setup() 
{
    myservo1.attach(servo1);  // инциализируем серву 1
    myservo2.attach(servo2);  // 
    pinMode(joyH, INPUT); //выставим пин джойстика по горизонтали
    pinMode(joyV, INPUT); //пин джойстика на чтение
}

void loop() 
{
    //первая серва
    int val = analogRead(joyH); //получаем значение джойстика по горизонтали
    val = map(val, 0, 1023, 20, 160); //маштабируем значени джойстика для сервы
    myservo2.write(val);  //повернем серву

    //вторая серва
    val = analogRead(joyV);           
    val = map(val, 0, 1023, 20, 160); 

    myservo1.write(val);  //поворачиваем серву
}
