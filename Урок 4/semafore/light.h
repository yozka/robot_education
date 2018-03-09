#pragma once
#include "led.h"


//класс светофора
//включает и выключает светодиоды
class ALight
{
    public:

        //конструктор
        ALight(ALed &red, ALed &yellow, ALed &green)
        :
            mRed(red),
            mYellow(yellow),
            mGreen(green)
        {
        }

        //метод зажигает только красный светодиод
        void red() 
        {
            mRed.on();
            mYellow.off();
            mGreen.off();
        }

        void yellow() //зажигаем только желтый светодиод
        {
            mRed.off();
            mYellow.on();
            mGreen.off();
        }

        void green() //включаем только зеленый светодиод
        {
            mRed.off();
            mYellow.off();
            mGreen.on();
        }

        void off() //выключаем все светодиоды
        {
            mRed.off();
            mYellow.off();
            mGreen.off();       
        }

    private:

        //переменные где хранятся светодиоды
        ALed &mRed;
        ALed &mYellow;
        ALed &mGreen;
 
};

