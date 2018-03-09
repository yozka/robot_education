#include <ESP8266WiFi.h> //вайфай
#include <ESP8266WebServer.h> //вебсервер

const int LEDPin = D0; //светодиод
ESP8266WebServer server(80);   //вебсервер 80 (http port)

//функция которая отправляет веб страницу
void page()
{
    //сформируем вебстраницу ввиде тегов HTML
    String s = "<h1>Led diode</h1> \
    <p> \
    <a href='ledon'><button>ON</button></a> \
    <a href='ledoff'><button>OFF</button></a> \
    </p>";
    
    server.send(200, "text/html", s); //отправляем страницу
    delay(1000); //ждем чтобы отправилось навярника
}

//обрабатывает вебстраницу включение светодиода
void ledon()
{
    digitalWrite(LEDPin, HIGH);
    page(); //отправим вебстраницу
}

//функция обрабатывает страницу выключение светодиода
void ledoff()
{
    digitalWrite(LEDPin, LOW);
    page(); //обновим 
}

void setup() 
{
    //настройка светодиода
    pinMode(LEDPin, OUTPUT);
    
    //настройка вайфая
    WiFi.mode(WIFI_AP_STA);//режим точки доступа
    WiFi.softAP("Teletube");//название сети (можно написать свое)

    //подключеи к серверу функции, которые обрабатывают адреса
    server.on("/", page); //главная страница
    server.on("/ledon",   ledon); //страница включение светодиода
    server.on("/ledoff",  ledoff); //страница выключения светодиода
    
    server.begin();//запуск вебсервера
}

void loop() 
{
    server.handleClient(); //обрабатываем сообщение сервера
}
