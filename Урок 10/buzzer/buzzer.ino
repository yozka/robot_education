int buzzer = 3; //пьезопищалка (англ. buzzer)
int ldr    = A0; //фоторезистр (англ. Light Dependent Resistor или просто LDR)
 
void setup()
{
  // пин с пьезопищалкой — выход...
  pinMode(buzzer, OUTPUT);
  pinMode(ldr, INPUT); //пин с фоторезистором вход
}
 
void loop()
{
  int val;
  int frequency;
 
  // считываем уровень освещённости так же, как для
  // потенциометра: в виде значения от 0 до 1023.
  val = analogRead(ldr);
 
  // рассчитываем частоту звучания пищалки в герцах (ноту),
  // используя функцию проекции (англ. map). Она отображает
  // значение из одного диапазона на другой, строя пропорцию.
  // В нашем случае [0; 1023] -> [3500; 4500]. Так мы получим
  // частоту от 3,5 до 4,5 кГц.
  frequency = map(val, 0, 1023, 3500, 4500);
 
  // заставляем пин с пищалкой «вибрировать», т.е. звучать
  // (англ. tone) на заданной частоте 20 миллисекунд. При
  // cледующих проходах loop, tone будет вызван снова и снова,
  // и на деле мы услышим непрерывный звук тональностью, которая
  // зависит от количества света, попадающего на фоторезистор
  tone(buzzer, frequency, 20);
}
