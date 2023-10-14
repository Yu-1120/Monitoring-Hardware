#include <Arduino.h>
#include <TFT_eSPI.h>
#include <math.h>


#define LEFT_KEY  digitalRead()

void KEY_INIT() {

}
TFT_eSPI tft;

void setup() {




  Serial.begin(115200);
  Serial.println("Hello ESP32C3!!");
  tft.begin();
  tft.setRotation(3);
  // tft.setRotation(1);
  tft.setTextFont(2);
  tft.fillScreen(TFT_BLACK);
  tft.drawString("Hello ESP32C3!!", 0, 0);
  tft.drawRect(2, 20, 100, 20, TFT_BROWN);
}

void loop() {
  tft.drawString("Hello ESP32C3!!", 0, 0);


}