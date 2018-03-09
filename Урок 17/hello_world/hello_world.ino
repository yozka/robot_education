#include <Wire.h> //библиотека двухпроводного интерфеса
#include <Adafruit_SSD1306.h> //библиотека экрана

Adafruit_SSD1306 display;//экран



void setup()   
{                
    Wire.begin(); //настройка интерфеса
	//настройка экрана
    display.begin(SSD1306_SWITCHCAPVCC,  0x3C);   
    
	display.clearDisplay();//стираем экран
	
	display.setTextSize(1); //размер текста 
    display.setTextColor(WHITE); //цвет текста
    display.setCursor(0,0);//кордината вывода текста
	
	display.print("Hello world");
   display.drawPixel(30, 30, WHITE); 
	display.display(); //показываем экран
}

void loop() 
{
}
