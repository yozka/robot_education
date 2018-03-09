#include <Keypad.h> // подключаем библиотеку
const byte ROWS = 4; //число строк у клавиатуры
const byte COLS = 4; //число столбцов у клавиатуры
const char keys[ROWS][COLS] = 
  {
    {'1','2','3','A'}, // здесь мы располагаем названия клавиш, 
    {'4','5','6','B'}, // как на клавиатуре,для удобства пользования
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

const byte rowPins[] = {9, 8, 7, 6}; //выводы подключения управление строками
const byte colPins[] = {5, 4, 3, 2}; //выводы подключания управление столбцами
//создаем клавиатуру keypad
auto  keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

const byte buzzer = 10;//пин пищалки

void setup()
{
    Serial.begin(9600); //настройка порта для вывода на компьютер
    pinMode(buzzer, OUTPUT);//настройка порта для пищалки
}
void loop()
{
    const auto key = keypad.getKey(); //читаем одни символ клавиатуры
    if (key) //проверка, нажали ли на клавишу
    {
        Serial.println(key); //выведем нажатую кнопку в порт
        
        int frq = 3500; //частота пищалки от 3500 - 4500 
        tone(buzzer, frq, 20); //пищим
    }
}