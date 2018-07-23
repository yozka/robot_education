#include <ESP8266WiFi.h> //вайфай
#include <WiFiClientSecure.h>
#include <AzureIoTHubMQTTClient.h>


//DHT sensor library for ESPx by beege_tokyo
#include <DHTesp.h> //датчик температуры 

#define IOTHUB_HOSTNAME         "iotTemperature3291.azure-devices.net"
#define DEVICE_ID               "device-temperature"
#define DEVICE_KEY              "QuXMKKN3fB/KpqGIPjDcfFLXfV3NeYI2rwOaDXKHoDE=" //Primary key of the device
WiFiClientSecure tlsClient;
AzureIoTHubMQTTClient client(tlsClient, IOTHUB_HOSTNAME, DEVICE_ID, DEVICE_KEY);


DHTesp dht; 				//датчик температуры

unsigned long lastMillis = 0;

//опрос датчика температуры
void readSensor(float *temp, float *humidity)
{
    auto t = dht.getTempAndHumidity();
    *temp = t.temperature;
    *humidity = t.humidity;
}



void connectToIoTHub() 
{
    Serial.print("\nBeginning Azure IoT Hub Client... ");
    if (client.begin()) 
    {
        Serial.println("OK");
    } else 
    {
        Serial.println("Could not connect to MQTT");
    }
}

void onClientEvent(const AzureIoTHubMQTTClient::AzureIoTHubMQTTClientEvent event) 
{
    Serial.println("Event iot");
    if (event == AzureIoTHubMQTTClient::AzureIoTHubMQTTClientEventConnected) 
    {
        Serial.println("Connected to Azure IoT Hub");
    }
}

void onActivateRelayCommand(String cmdName, JsonVariant jsonValue) 
{
    Serial.print("Command ");
    Serial.println(cmdName);

    //Parse cloud-to-device message JSON. In this example, I send the command message with following format:
    //{"Name":"ActivateRelay","Parameters":{"Activated":0}}

    JsonObject& jsonObject = jsonValue.as<JsonObject>();
    if (jsonObject.containsKey("Parameters")) 
    {
        auto params = jsonValue["Parameters"];
        auto isAct = (params["Activated"]);
        if (isAct) 
        {
            Serial.println("Activated true");
            digitalWrite(LED_BUILTIN, HIGH); //visualize relay activation with the LED
        }
        else 
        {
            Serial.println("Activated false");
            digitalWrite(LED_BUILTIN, LOW);
        }
    }
}


void setup() 
{
    Serial.begin(115200);
    while(!Serial) 
    {
        yield();
    }
    Serial.println();

    pinMode(LED_BUILTIN, OUTPUT);
    dht.setup(16, DHTesp::DHT11);//настройка датчика температуры

    WiFi.disconnect();
    WiFi.softAPdisconnect();

    //настройка вайфая
    WiFi.begin("Zoopark", "password");
  
    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println();
  
    Serial.print("Connected, IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Waiting for sync");
    NTP.begin(NTP_DEFAULT_HOST);
    while (NTP.getTime() < 30000)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println("OK SYNC TIME");
    //

    //Handle client events
    client.onEvent(onClientEvent);

    //Add command to handle and its handler
    //Command format is assumed like this: {"Name":"[COMMAND_NAME]","Parameters":[PARAMETERS_JSON_ARRAY]}
    client.onCloudCommand("ActivateRelay", onActivateRelayCommand);

    Serial.println("Ok!!!!!!!!");
 



    connectToIoTHub();
}

void loop() 
{
    client.run();

    if (client.connected()) 
    {
        // Publish a message roughly every 3 second. Only after time is retrieved and set properly.
        if(millis() - lastMillis > 1000 * 60 && timeStatus() != timeNotSet) 
        {
            lastMillis = millis();

            //Read the actual temperature from sensor
            float temp, humidity;
            readSensor(&temp, &humidity);
            
            //Get current timestamp, using Time lib
            time_t currentTime = now();

            // You can do this to publish payload to IoT Hub
            String payload = "{\"DeviceId\":\"" + String(DEVICE_ID) + "\", \"MTemperature\":" + String(temp) + ", \"EventTime\":" + String(currentTime) + "}";
            Serial.println(payload);
            
            ////client.publish(MQTT::Publish("devices/" + String(DEVICE_ID) + "/messages/events/", payload).set_qos(1));
            //client.sendEvent(payload);


            //Or instead, use this more convenient way
            AzureIoTHubMQTTClient::KeyValueMap keyVal = {{"MTemperature", temp}, {"MHumidity", humidity}, {"DeviceId", DEVICE_ID}, {"EventTime", currentTime}};
            client.sendEventWithKeyVal(keyVal);
        }
    }
    else 
    {

    }

    delay(10); // <- fixes some issues with WiFi stability

}
