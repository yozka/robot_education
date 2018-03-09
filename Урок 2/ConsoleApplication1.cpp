// Калькулятор
//
#include <stdio.h> //стандартная библиотека
#include <clocale> 


int main()
{
	setlocale(LC_CTYPE, "rus"); //установка кирилицы

	int a = 0; //создание переменной "а"
	int b = 0; //создание переменной "b"
	
	printf("Введи число a:");
	scanf("%i", &a); //ввод числа из клавиатуры

	printf("Введи число b:");
	scanf("%i", &b);

	int c = a + b;   //математическое действие
	printf("Результат %i", c);



	scanf("%i", &c); 
    return 0;
}

