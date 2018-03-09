#pragma once

//класс светодиода
class ALed
{
    public:
        //конструктор
        ALed(int pin)
        {
            mPin = pin;
            pinMode(mPin, OUTPUT); //переключаем ножку на выход
        }

        
        //включить светодиод 
        void on()
        {
            digitalWrite(mPin, HIGH);
        }

        //выключить светодиод 
        void off()
        {
            digitalWrite(mPin, LOW);
        }
          
    private:
        int mPin; //ножка к которому подключен светодиод
};



