/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core2 sample source code
*                          配套  M5Core2 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/core2
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/core2
*
* Describe: Display Example.  显示屏示例
* Date: 2021/7/21
*******************************************************************************
*/
#include <M5Core2.h>

const int DATASIZE = 25;
const int COEFS = 25;

int sensorPin = 36;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int outPin = 26;
int sensorValue = 0;  // variable to store the value coming from the sensor
int i, j;
int x[DATASIZE];

int k[COEFS];
int y;
int t;

const int LINESIZE = 320;
int ys[LINESIZE];


unsigned int time_now;

Button lt(0, 0, 60, 20, "-");
Button gt(80, 0, 60, 20, "+");

int scale;

void colorButtons(Event& e) {
  Button& b = *e.button;
  if ((e.to.x <= 60) && (e.to.y <= 20))
  {
      M5.Lcd.fillRect(b.x, b.y, b.w, b.h, b.isPressed() ? WHITE : BLUE);
      scale = 180;
  }
  if ((e.to.x >= 80) && (e.to.x <= 140) && (e.to.y <= 20))
  {
      M5.Lcd.fillRect(b.x, b.y, b.w, b.h, b.isPressed() ? WHITE : BLUE);

      scale = 90;
  }
}

void FillKoefs()
{
      for (i = 0; i < COEFS; i++) 
      {
        k[i] = 1;
      }
}

void ReadADC()
{
  time_now = micros();
  for (i = 0; i < DATASIZE; i++)
  {
    while ((micros() - time_now) <= 1000) {};
    time_now = micros();
    x[i] = analogRead(sensorPin);
  }

    y = 0;
      for (j = 0; j < COEFS; j++) 
      {
        y += x[j]*k[j];
      }

    Serial.println(y);

}

void setup() {

    Serial.begin(115200);
    FillKoefs();
    t = 0;

    scale = 180;

    M5.begin();                      // Init M5Core2.  

    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(100, 100);      // Move the cursor position to (x,y).
    M5.Lcd.setTextColor(WHITE);      // Set the font color to white. 
    M5.Lcd.setTextSize(2);           // Set the font size.  
    M5.Lcd.printf("Analog input.");  

    delay(500);                
    M5.Lcd.fillScreen(BLACK);

    M5.Buttons.addHandler(colorButtons,  E_TOUCH + E_RELEASE);

    delay(500);

}  


void loop() {

    ReadADC();

    M5.Lcd.drawPixel(t, 230 - ys[t], BLACK);
    
    y = y * scale / 4096 / COEFS;
    if (y > 200) y = 200;

    (y == 200) ? M5.Lcd.drawPixel(t, 230 - y, YELLOW) : M5.Lcd.drawPixel(t, 230 - y, GREEN);

    ys[t] = y;

    M5.Lcd.drawLine(t, 20, t, 24, BLACK);
    t++;
    if (t > 319) t = 0;
    M5.Lcd.drawLine(t, 20, t, 24, RED);
    analogWrite(outPin, t / 10);

    M5.update();  // Read the press state of the key. 
}
