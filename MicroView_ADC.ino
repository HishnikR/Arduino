
#include <MicroView.h>

void setup() {
  // put your setup code here, to run once:
  uView.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 64; i++)
  {
    int x = analogRead(A0);
    uView.clear(PAGE);
    // вывод пикселей на дисплей
    uView.pixel(i, 24- (x / 32));

    if ( i == 63) {
    //  uView.setCursor(8, 0);
    //  uView.print(x);
    }

    // отображаем содержимое из буфера экрана
    uView.display();

    delay(1);
  }



}
