// �����������
//
#include <stdio.h> //����������� ����������
#include <clocale> 


int main()
{
	setlocale(LC_CTYPE, "rus"); //��������� ��������

	int a = 0; //�������� ���������� "�"
	int b = 0; //�������� ���������� "b"
	
	printf("����� ����� a:");
	scanf("%i", &a); //���� ����� �� ����������

	printf("����� ����� b:");
	scanf("%i", &b);

	int c = a + b;   //�������������� ��������
	printf("��������� %i", c);



	scanf("%i", &c); 
    return 0;
}

