#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>


TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h


#define ANALOG_PIN_0   27


int x, y;
unsigned int time_now;

void setup(){
  Serial.begin(115200);
  pinMode(ANALOG_PIN_0,INPUT);

  tft.init();
  tft.setRotation(1);
  tft.setSwapBytes(true); // We need to swap the colour bytes (endianess)
  tft.fillScreen(TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setCursor (12, 5);
  tft.print("Analog draw");

  x = 0;
}




void loop() {
  int analog_value = 0;

  time_now = micros();
    while ((micros() - time_now) <= 1000) {};
    time_now = micros();
  analog_value = analogRead(ANALOG_PIN_0);

  y = analog_value / 20;

  tft.drawPixel(x, y, TFT_BLUE);
  x++;

  if (x > 320) {
    x = 0;
    tft.fillScreen(TFT_WHITE);
  }
}
