// Пример 1
// 
#include <LiquidCrystal.h> //подключение бибилотеки
LiquidCrystal lcd(4, 5, 10, 11, 12, 13 ); //создание дисп

//настройка
void setup() 
{
  lcd.begin(16, 2); //инциализация дисплея
  lcd.print("Hello World!");//вывод текста
}

//основной цикл
void loop() 
{
}
//=====================================================

// Пример 3
// Для вывода кирилицы используется стороння библиотека
// https://github.com/ssilver2007/LiquidCrystal_1602_RUS
//
#include <LiquidCrystal_1602_RUS.h>
LiquidCrystal_1602_RUS lcd(4, 5, 10, 11, 12, 13 );

void setup() 
{
  lcd.begin(16, 2);
  lcd.print(L"Привет мир!");
}

void loop() 
{
}