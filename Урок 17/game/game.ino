#include <Wire.h> //библиотека двухпроводного интерфеса
#include <Adafruit_SSD1306.h> //библиотека экрана

Adafruit_SSD1306 display;//экран

const int AbutUP    = A1; //кнопки игрока А
const int AbutDOWN  = A0;
const int BbutUP    = A3; //кнопки игрока Б
const int BbutDOWN  = A2;

int scoreA = 0; //очки игрока А
int scoreB = 0; //очки игрока Б

float x = 0; //положение мячика
float y = 0;
float dx = 0.5f; //направление движения мячика
float dy = 0.5f; //онаже скорость

float Ar = 0; //положение ракетки игрока А
float Br = 0; //положение ракетки игрока Б
float As = 10; //размер ракетки игрока А
float Bs = 10; //размер ракетки игрока Б
float Av = 1; //скорость перемещения ракетки А
float Bv = 1; //скорость перемещения ракетки Б

void setup()   
{                
    Wire.begin(); //настройка интерфеса
	//настройка экрана
    display.begin(SSD1306_SWITCHCAPVCC,  0x3C);   
    display.clearDisplay();
    display.display(); //показываем экран
	//настраиваем кнопки
    pinMode(AbutUP,   INPUT_PULLUP);
    pinMode(AbutDOWN, INPUT_PULLUP);
    pinMode(BbutUP,   INPUT_PULLUP);
    pinMode(BbutDOWN, INPUT_PULLUP);

    newGame();//новая игра
}
//функция новой игры
void newGame()
{
    x = 64; //начальное положение мяча
    y = 16;
    dx = -dx; //меняем тракторию движения меча
    delay(1000);
}
//функция, выиграл игрок А
void winA()
{
    scoreA++; //увеличим очки
    newGame(); //запустим новую игру
}
//ффункция выиграл игрок Б
void winB()
{
    scoreB++;//увеличим очки игрока Б
    newGame();//запустим новую игру
}
void loop() 
{
    display.clearDisplay(); //стираем изображения экрана
    display.drawPixel(x, y, WHITE);//рисуем мяч
	//рисуем ракетку игрока А слевой стороны
    display.drawLine(5, Ar, 5, Ar + As, WHITE);
	//рисуем ракетку игрока Б справой стороны
    display.drawLine(122, Br, 122, Br + Bs, WHITE);
	//рисуем количество очков
    display.setTextSize(1); //размер текста 
    display.setTextColor(WHITE); //цвет текста
    display.setCursor(56,0);//кордината вывода текса
    display.print(scoreA);//рисуем очки игрока А
    display.print(":");
    display.print(scoreB); //очки игрока Б
    display.display(); //выводим изображеие на экран
    //столкновения
	//об ракетку игрока А
    if (x <= 6 && y > Ar && y < Ar + As)
    {
        dx = abs(dx); //изменим движение мяча
        x = 6;
    }
	//столкновения об ракетки игрока Б
    if (x >= 121 && y > Br && y < Br + Bs)
    {
        dx = -abs(dx);
        x = 121;
    }

	//двигаем мяч
    x += dx;
    y += dy;
    if (x < 0)
    {
        winB(); 
    }
    if (x > 127)
    {
        winA();
    }
    //столкновения об верхнию и нижнию стенку
    if (y < 0)
    {
        dy = abs(dy);
        y = 0;
    }
    if (y > 32)
    {
        dy = -abs(dy);
        y = 32;
    }
	//опрос кнопок и двежение ракетки игрока А
    if (digitalRead(AbutUP) == LOW && Ar > 0)
    {
        Ar -= Av;
    }
    if (digitalRead(AbutDOWN) == LOW && Ar < 32 - As)
    {
        Ar += Av;
    }
	//двжиение ракетки игрока Б
    if (digitalRead(BbutUP) == LOW && Br > 0)
    {
        Br -= Bv;
    }
    if (digitalRead(BbutDOWN) == LOW && Br < 32 - Bs)
    {
        Br += Bv;
    }
}