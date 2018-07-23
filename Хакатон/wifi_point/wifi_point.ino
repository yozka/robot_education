#include <ESP8266WiFi.h> //вайфай
#include <ESP8266WebServer.h> //вебсервер


//DHT sensor library for ESPx by beege_tokyo
#include <DHTesp.h> //датчик температуры 


DHTesp dht; 				//датчик температуры
TempAndHumidity dhtTemp; 	//температура
long updateTime = 0; 		//время обновления датчика

ESP8266WebServer server(80); //вебсервер 80 (http port)

//функция которая отправляет веб страницу
void webPage()
{
    //сформируем вебстраницу ввиде тегов HTML
    String s = "<h1>Temperature</h1>";

    s += String("<p>Temperature: ") + String(dhtTemp.temperature) + String("</p>");
    s += String("<p>Humidity: ") + String(dhtTemp.humidity) + String("</p>");
 
    server.send(200, "text/html", s); //отправляем страницу
}

//опрос датчика температуры
void readSensor()
{
    const auto t = millis();
    if (t < updateTime)
    {
        return;
    }
    updateTime = t + 2000;
    dhtTemp = dht.getTempAndHumidity();
}

void setup() 
{
    dht.setup(16, DHTesp::DHT11);//настройка датчика температуры

    //настройка вайфая
    WiFi.disconnect();
    WiFi.softAPdisconnect();
    
    IPAddress apIP(192,168,4,1);
    WiFi.mode(WIFI_AP_STA);//режим точки доступа
    WiFi.softAP("IoT Device");//название сети (можно написать свое)
    WiFi.softAPConfig(apIP,apIP, IPAddress(255,255,255,0));

    //подключеи к серверу функции, которые обрабатывают адреса
    server.on("/", webPage); //главная страница
    server.begin();//запуск вебсервера
}

void loop() 
{
    readSensor();
    server.handleClient(); //обрабатываем сообщение сервера
}
