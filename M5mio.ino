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

const int DATASIZE = 51;
const int COEFS = 51;

int sensorPin = 36;   // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int outPin = 26;
int sensorValue = 0;  // variable to store the value coming from the sensor
int i, j;
int x[DATASIZE];

int k[COEFS];
int y, y_re, y_im, ampl;
int t;

const int LINESIZE = 320;
int ys[LINESIZE];

int k_re[COEFS] = {
0  ,
-405  ,
-1052  ,
-731  ,
2874  ,
9770  ,
11096  ,
-10897  ,
-60568  ,
-89956  ,
0  ,
247797  ,
459594  ,
227778  ,
-638911  ,
-1549691  ,
-1255504  ,
879564  ,
3487452  ,
3694939  ,
0  ,
-5179601  ,
-6853084  ,
-2422894  ,
4848127  ,
8388606  ,
4848127  ,
-2422894  ,
-6853084  ,
-5179601  ,
0  ,
3694939  ,
3487452  ,
879564  ,
-1255504  ,
-1549691  ,
-638911  ,
227778  ,
459594  ,
247797  ,
0  ,
-89956  ,
-60568  ,
-10897  ,
11096  ,
9770  ,
2874  ,
-731  ,
-1052  ,
-405  ,
0  
};


int k_im[COEFS] = {
219  ,
294  ,
-342  ,
-2249  ,
-3955  ,
0  ,
15273  ,
33538  ,
19680  ,
-65357  ,
-187689  ,
-180035  ,
149331  ,
701029  ,
879385  ,
0  ,
-1728053  ,
-2707020  ,
-1133142  ,
2684531  ,
5499568  ,
3763200  ,
-2226702  ,
-7456900  ,
-6672875  ,
0  ,
6672875  ,
7456900  ,
2226702  ,
-3763200  ,
-5499568  ,
-2684531  ,
1133142  ,
2707020  ,
1728053  ,
0  ,
-879385  ,
-701029  ,
-149331  ,
180035  ,
187689  ,
65357  ,
-19680  ,
-33538  ,
-15273  ,
0  ,
3955  ,
2249  ,
342  ,
-294  ,
-219  

};

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
  double xd, yd;
  time_now = micros();
  for (i = 0; i < DATASIZE; i++)
  {
    while ((micros() - time_now) <= 1000) {};
    time_now = micros();
    x[i] = analogRead(sensorPin);
  }

    y_re = 0;
    y_im = 0;
      for (j = 0; j < COEFS; j++) 
      {
        y_re += x[j]*k_re[j];
        y_im += x[j]*k_im[j];
      }

    xd = y_re;
    yd = y_im;
    ampl = round(sqrt(xd*xd + yd*yd));  

    Serial.println(ampl);

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
    
    y = ampl / 1000;
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
