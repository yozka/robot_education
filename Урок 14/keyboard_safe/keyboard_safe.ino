#include <Keypad.h> // подключаем нашу библиотеку
const byte ROWS = 4; //число строк у нашей клавиатуры
const byte COLS = 4; //число столбцов у нашей клавиатуры

const char keys[ROWS][COLS] = 
  {
    {'1','2','3','A'}, // здесь мы располагаем названия наших клавиш, 
    {'4','5','6','B'}, // как на клавиатуре,для удобства пользования
    {'7','8','9','C'},
    {'*','0','#','D'}
  };

const byte rowPins[] = {9, 8, 7, 6}; //к каким выводам подключаем управление строками
const byte colPins[] = {5, 4, 3, 2}; //к каким выводам подключаем управление столбцами
auto keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS); //создаем клавиатуру

const byte buzzer = 10;
const byte ledRed = 11;
const byte ledGreen = 12;

int code = 0; //кодовое число
String codeInput; //строка куда записываются введенные числа
void setup()
{
    pinMode(buzzer,   OUTPUT); //настройка портов
    pinMode(ledRed,   OUTPUT);
    pinMode(ledGreen, OUTPUT);

    randomSeed(analogRead(0)); //инциализация рандома
    code = random(20);

    Serial.begin(9600);
}

void loop()
{
    const auto key = keypad.getKey(); //читаем одни символ клавиатуры
    if (key) //проверка, нажали ли на клавишу
    {
        if (key == '#')
        {
            //проверка кода
            if (codeInput.toInt() == code)
            {
                //код введен правельно
                digitalWrite(ledRed, LOW);          
                digitalWrite(ledGreen, HIGH);
            }
            else
            {
                digitalWrite(ledRed, HIGH);          
                digitalWrite(ledGreen, LOW);
            }
            codeInput = "";
            return;            
        }
        int frq = 3500; //частота пищалки от 3500 - 4500 
        tone(buzzer, frq, 20); //пищим
        codeInput += key;
        Serial.println(codeInput);
    }
}
