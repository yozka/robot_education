#pragma once
#include <string>
#include <memory>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
//-----------------------------------------------------------------------------




 ///---------------------------------------------------------------------------
///
/// �������
///
///
///----------------------------------------------------------------------------
class ASprite
{
public:
	ASprite();
	ASprite(const std::string &fileName);
	virtual ~ASprite();
	void draw(Graphics *graphics);

	void move(const int x, const int y);
	void move(const float x, const float y);
	float x() const { return mX; }
	float y() const { return mY; }

	void show();
	void hide();
	bool isVisible() const { return mVisible; }

	ASprite(const ASprite&) = delete;
	void operator=(const ASprite&) = delete;

	void destroy();

	void load(const std::string &fileName);

private:
	Image *mImage = nullptr;
	std::wstring mName;
	float mX = 0;
	float mY = 0;
	bool mVisible = false;
	bool mInit = false;

	void init();
};
///----------------------------------------------------------------------------





 ///---------------------------------------------------------------------------
///
/// ����� ������� ����������
///
///
///----------------------------------------------------------------------------
void print		(const std::string &text);
void println	(const std::string &text);
void print		(const int value);
void println	(const int value);
void print		(const float value);
void println	(const float value);

void cls(); //������� ������
void delay(const int ms); //�������� �������
void main(); //�������� ����� �����
void repaint();
int  random(const int max); //��������� ���������� �����

void scan(int &value); //���� �����
void scan(float &value); //���� �����
void scan(std::string &value); //���� �������
void scan(char* value, const int size); //���� �����

void setScreenSize(const int width, const int height); //��������� ������� ������

extern ASprite robot;
extern ASprite cat;
extern ASprite dog;


extern bool keyLeft;
extern bool keyRight;
extern bool keyUp;
extern bool keyDown;
extern bool keySpace;

extern int  screenWidth;
extern int  screenHeight;