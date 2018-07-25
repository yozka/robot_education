#include <ESP8266WiFi.h> //вайфай
#include <WiFiClientSecure.h> //клиент для подключения
#include <AzureIoTHubMQTTClient.h>

#include <DHTesp.h> //DHT sensor library for ESPx by beege_tokyo



#define PINLED                  5
#define IOTHUB_HOSTNAME         "iotTemperature3291.azure-devices.net"//адрес подключения к облаку
#define DEVICE_ID               "device-temperature"//название девайса
#define DEVICE_KEY              "QuXMKKN3fB/KpqGIPjDcfFLXfV3NeYI2rwOaDXKHoDE=" //Первичный ключ девайса



WiFiClientSecure tlsClient; //соеденение с вайфаем
AzureIoTHubMQTTClient client(tlsClient, IOTHUB_HOSTNAME, DEVICE_ID, DEVICE_KEY); //клиент для облака



DHTesp dht; 				//датчик температуры
unsigned long lastMillis = 0; //интервал для следующей отправки данных



//опрос датчика температуры
void readSensor(float *temp, float *humidity)
{
    auto t = dht.getTempAndHumidity();
    *temp = t.temperature;
    *humidity = t.humidity;
}



//выполнение команды от сервера
//{"Name":"led","Parameters":{"Activated":0}}
void onLedCommand(String cmdName, JsonVariant jsonValue) 
{
    JsonObject& jsonObject = jsonValue.as<JsonObject>();
    if (jsonObject.containsKey("Parameters")) 
    {
        auto params = jsonValue["Parameters"];
        auto isAct = (params["Activated"]);
        if (isAct) 
        {
            Serial.println("Led true");
            digitalWrite(PINLED, HIGH);//визаулизация светодиода
        }
        else 
        {
            Serial.println("Led false");
            digitalWrite(PINLED, LOW);
        }
    }
}



//настройка устройства
void setup() 
{
    Serial.begin(115200);

    pinMode(PINLED, OUTPUT);
    dht.setup(16, DHTesp::DHT11);//настройка датчика температуры

    WiFi.disconnect();
    WiFi.softAPdisconnect();

    //настройка вайфая
    WiFi.begin("Имя сети", "Пароль");
    //ждем кодгда подключится интернет
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    //синхронизация с сервером времени
    Serial.println("Sync time");
    NTP.begin(NTP_DEFAULT_HOST);
    while (NTP.getTime() < 30000)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    //

    //привяжем команду к клиенту
    //Формат команды таков: {"Name":"[COMMAND_NAME]","Parameters":[PARAMETERS_JSON_ARRAY]}
    client.onCloudCommand("led", onLedCommand);
    
    //запуск
    client.begin(); 
}





//обработка цикла сообщений
void loop() 
{
    client.run();

    if (client.connected()) 
    {
        //Публикуем собщения раз в 3 секунды, также учитываем стобы было установленно системное время
        if(millis() - lastMillis > 3000 && timeStatus() != timeNotSet) 
        {
            lastMillis = millis();

            //Читаем актуальную температуру от сенсора
            float temp, humidity;
            readSensor(&temp, &humidity);
            
            //Берем текущее время, используем библиотеку Timelib
            time_t currentTime = now();

            //Публикуем полезную нагрузку IoT Hub
            Serial.println("DeviceId:" + String(DEVICE_ID) + ", MTemperature:" + String(temp) + ", EventTime:" + String(currentTime));

            //Формируем строчку для отправки на сервер
            AzureIoTHubMQTTClient::KeyValueMap keyVal = {{"MTemperature", temp}, {"MHumidity", humidity}, {"DeviceId", DEVICE_ID}, {"EventTime", currentTime}};
            client.sendEventWithKeyVal(keyVal);
        }
    }
    delay(10); // <- магия для исправление проблем с устойчивостью работы с WiFi
}
