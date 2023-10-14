#include <Arduino.h>
#include <TFT_eSPI.h>
#include <math.h>

#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735


// #define LEFT_KEY  digitalRead()

// void KEY_INIT() {

// }
TFT_eSPI tft;

#define TFT_CS2     19       //管脚定义，右边的屏幕
#define TFT_RST2    12
#define TFT_DC2     18
#define TFT_SCLK2   0
#define TFT_MOSI2   1
#define BL_EN   8

Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT_CS2, TFT_DC2, TFT_MOSI2, TFT_SCLK2, TFT_RST2);

void setup() {

  pinMode(BL_EN,OUTPUT);
  digitalWrite(BL_EN,LOW);          //打开背光
  tft2.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
  tft2.setRotation(0);               //旋转屏幕

  tft2.fillRect(0,0,160,80,ST77XX_WHITE);
  tft2.drawLine(0,0,0,79,ST77XX_BLUE);      //第二块屏幕最左侧那一列的像素画一条线-蓝色
  tft2.drawLine(1,0,1,79,ST77XX_YELLOW);      //第二块屏幕最左侧倒数第二列的像素画一条线-黄色
  tft2.drawLine(2,0,2,79,ST77XX_GREEN);      //第二块屏幕最左侧倒数第二列的像素画一条线-绿

  Serial.begin(115200);
  Serial.println("Hello ESP32C3!!");
  tft.begin();
  tft.setRotation(3);
  // tft.setRotation(1);
  tft.setTextFont(2);
  tft.fillScreen(TFT_BLACK);  //clear
  tft.drawString("Hello ESP32C3!!", 0, 0);
  tft.drawRect(2, 20, 100, 20, TFT_BROWN);
}

void loop() {
  tft.drawString("Hello ESP32C3!!", 0, 0);


}