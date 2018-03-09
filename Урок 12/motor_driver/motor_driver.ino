int m1dir = 7;
int m2dir = 8;
int m1pwm = 9;
int m2pwm = 10;


void setup() 
{
    pinMode(m1dir,    OUTPUT);
    pinMode(m2dir,    OUTPUT);
    pinMode(m1pwm,    OUTPUT);
    pinMode(m2pwm,    OUTPUT);

    // 16MHz / 1 (prescaler) / 2 (phase-correct) / 400 (top) = 20kHz
    TCCR1A = 0b10100000;
    TCCR1B = 0b00010001;
    ICR1 = 400;
}


void loop() 
{
	int speed = 200;
	
	//установка скорости на 2 двигатель
    OCR1B = speed;
    digitalWrite(m2dir, LOW);

	//установка скорости на 1 двигатель
    OCR1A = speed;
    digitalWrite(m1dir, LOW);
	
	delay(5000); //пауза 5сек
	speed = 400;
	
	//установка скорости на 2 двигатель
	OCR1B = speed;
	digitalWrite(m2dir, HIGH); //крутим в обратную сторону
	
	//установка скорости на 1 двигатель
	OCR1A = speed;
	digitalWrite(m1dir, HIGH); //крутим в обратную сторону
	
	delay(5000);
}
