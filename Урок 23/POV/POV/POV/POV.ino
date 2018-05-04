#include "Fonts.h"

//�������� �����������
int speed = 40;
String text = "Hello world!!!"; 

//���� ������
char custom[8] =
{
	0b01111100,
	0b10000010,
	0b10101010,
	0b10101010,
	0b10000010,
	0b10111010,
	0b10000010,
	0b01111100
};



void setup() 
{
	//��������� ����� �����������
	pinMode(A0, OUTPUT);
	pinMode(A1, OUTPUT);
	pinMode(A2, OUTPUT);
	pinMode(A3, OUTPUT);
	pinMode(A4, OUTPUT);
	pinMode(A5, OUTPUT);
	pinMode(A6, OUTPUT);
	pinMode(A7, OUTPUT);
}


//����� �� ����������
//�������� �������� ���������
void display(const byte val)
{
	digitalWrite(A0, val & (1 << 0) ? HIGH : LOW);
	digitalWrite(A1, val & (1 << 1) ? HIGH : LOW);
	digitalWrite(A2, val & (1 << 2) ? HIGH : LOW);
	digitalWrite(A3, val & (1 << 3) ? HIGH : LOW);
	digitalWrite(A4, val & (1 << 4) ? HIGH : LOW);
	digitalWrite(A5, val & (1 << 5) ? HIGH : LOW);
	digitalWrite(A6, val & (1 << 6) ? HIGH : LOW);
	digitalWrite(A7, val & (1 << 7) ? HIGH : LOW);
	delay(speed); //����, ����� ������
}
//-------------------

//�������� ����������
void displayCustom()
{
	for (int i = 0; i < 8; i++)
	{
		display(custom[i]);
	}
	display(0);
}
//-------------------


//�������� �������
void displayText()
{
	for (int i = 0; i < text.length(); i++)
	{
		//������� ���� ������
		char s = text[i];
		for (int i = 4; i >= 0; i--)
		{
			display(getFont(s, i));
		}
		//����� ������� ������� ������
		display(0);
	}
}
//-------------------


//�������� ����
void loop() 
{
	displayCustom();
}
