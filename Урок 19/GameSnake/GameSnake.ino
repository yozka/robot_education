#include <Wire.h> //библиотека двухпроводного интерфеса
#include <Adafruit_SSD1306.h> //библиотека экрана

Adafruit_SSD1306 display;//экран

const int butLeft     = A0; //кнопки 
const int butRight    = A1;
const int lenMax      = 120; //максимальный размер червя
const int cellX       = 3; //размер сегмента червя
const int cellY       = 2; //

enum eMove  //перечесляемый тип направления
{           //движения червя
  stop,
  left,
  right,
  up,
  down
};

int   score = 0;        //очки
float x = 32;           //положение головы змейки
float y = 15;           //
float speedX  = 1.0f;   //скорость змеи по оси Х
float speedY  = 0.5f;   //скорость змеи по оси Y
eMove move    = eMove::stop; //направление движения
int   bodyX[lenMax];  //масив коорданат сегментов 
int   bodyY[lenMax];
int   bodyLen = 0; //длина червя

int   frutX = -10;//положение фрукта
int   frutY = -10;//

int   butPush = 0;//нажа или не нанажата кнопки

//настройка
void setup()
{                
    Serial.begin(9600);
    Wire.begin(); //настройка интерфеса
	  //настройка экрана
    display.begin(SSD1306_SWITCHCAPVCC,  0x3C);   
    display.clearDisplay();
    display.display(); //показываем экран
	
	  //настраиваем кнопки
    pinMode(butLeft,   INPUT_PULLUP);
    pinMode(butRight, INPUT_PULLUP);
}

//функция завершения игры
void gameOver()
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(20,15);
    display.print("Game over!!!");
    display.display(); //показываем экран
    while (true) {}
}

//поворот змейки налево
void rotateLeft()
{
    switch (move)
    {
        case eMove::left  : move = eMove::down;   break;
        case eMove::right : move = eMove::up;     break;
        case eMove::up    : move = eMove::left;   break;
        case eMove::down  : move = eMove::left;   break;
        case eMove::stop  : move = eMove::left;   break;
    }
}

//поворот змеи на правое
void rotateRigth()
{
    switch (move)
    {
        case eMove::left  : move = eMove::up;     break;
        case eMove::right : move = eMove::down;   break;
        case eMove::up    : move = eMove::right;  break;
        case eMove::down  : move = eMove::right;  break;
        case eMove::stop  : move = eMove::right;  break;
    }
}

//движение змейки
void moveSnake()
{
    switch (move)
    {
        case eMove::left  : x = x - speedX; break;
        case eMove::right : x = x + speedX; break;
        case eMove::up    : y = y - speedY; break;
        case eMove::down  : y = y + speedY; break;
    }
    if (x < 0)    x = 127;
    if (x > 127)  x = 0;
    if (y < 0)    y = 31;
    if (y > 31)   y = 0;
    
    int bx = x / cellX;
    int by = y / cellY;
    if (bx != bodyX[0] || by != bodyY[0])
    {
      for (int i = bodyLen-1; i > 0; i--)
      {
         if (bx == bodyX[i] && by == bodyY[i])
         {
            gameOver(); 
         }
        
         bodyX[i] = bodyX[i - 1];
         bodyY[i] = bodyY[i - 1];
      }
      bodyX[0] = bx;
      bodyY[0] = by;
    }
}

//обработка фрукрта
void fruct()
{
    if (frutX < 0 || frutY < 0)
    {
        //покажем новый фрукт
        frutX = rand() % 128; //установим координаты
        frutY = rand() % 32;      
    }
    
    if (x - 2 <= frutX + 2 && x + 2 >= frutX - 2 &&
        y - 2 <= frutY + 2 && y + 2 >= frutY - 2)
    {
        //змея сожрала фрукт
        frutX = -10; //уберем фрукт с экрана
        frutY = -10;
        if (bodyLen < lenMax-1)
        {
            //увеличим размер змеи
            bodyX[bodyLen] = x / cellX;
            bodyY[bodyLen] = y / cellY;
            bodyLen++;
        }
        score++;//увеличим количество очков
    }
}

//основной цикл
void loop() 
{
    //отрисовываем змеюку
    display.clearDisplay();//стираем экран
    display.drawRect(x - 2, y - 1, 5, 3,  WHITE); //голова змеи
    display.drawPixel(x, y, WHITE);
    //хвост
    for (int i = 1; i < bodyLen; i++)
    {
       display.drawRect(bodyX[i] * cellX, bodyY[i] * cellY, cellX, cellY,  WHITE);
    }
    display.drawCircle(frutX, frutY, 2,  WHITE); //фрукт
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print(score);
    display.display(); //показываем экран

    moveSnake();//двигаем червя
    fruct();//обрабатываем фрукт
  
	  //опрос кнопок
    if (digitalRead(butLeft) == LOW && butPush == 0)
    {
        rotateLeft();
        butPush = 10;//устанавливаем счетчик нажатия
    }
    if(digitalRead(butRight) == LOW && butPush == 0)
    {
        rotateRigth();
        butPush = 10;
    }
    if (butPush > 0)
    {
        butPush--;
    }
}