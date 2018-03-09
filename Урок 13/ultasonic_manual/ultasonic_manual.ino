// Пример 1
// без использования библиотек
const int trigPin = PD3;
const int echoPin = PD2;

void setup() 
{
    Serial.begin(115200);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() 
{
    digitalWrite(trigPin, LOW);  //выключаем сенсор
    delayMicroseconds(2);       //ждем 2 микросекунды, чтобы убрать "эхо"
    digitalWrite(trigPin, HIGH); //включаем сенсор
    delayMicroseconds(10);      //ждем 10 микросекунд для подачи "эха"
    digitalWrite(trigPin, LOW); //выключаем
    long duration = pulseIn(echoPin, HIGH); //считаем сколько время прошло 
    int distance = (duration / 2) / 29.1; //высчитываем растояние в см.
    if (distance > 200)
    {
        //растояние вышло за пределы
        distance = 0;
    }

    delay(50);
    Serial.print("Ping: ");
    Serial.print(distance);
    Serial.println("cm"); 
}

