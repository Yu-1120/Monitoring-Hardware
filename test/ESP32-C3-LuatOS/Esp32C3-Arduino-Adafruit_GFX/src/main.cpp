#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
 
#define TFT_CS      7        //管脚定义，左边的屏幕
#define TFT_RST    10
#define TFT_DC      6
#define TFT_SCLK    2
#define TFT_MOSI    3
 
#define TFT_CS2    19        //管脚定义，右边的屏幕
#define TFT_RST2    12
#define TFT_DC2     18
#define TFT_SCLK2   0
#define TFT_MOSI2   1
 
#define BL_EN1   8
 #define BL_EN2   12
//简单粗暴的双屏定义
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
Adafruit_ST7735 tft2 = Adafruit_ST7735(TFT_CS2, TFT_DC2, TFT_MOSI2, TFT_SCLK2, TFT_RST2);
 
void setup(){
    pinMode(BL_EN1,OUTPUT);
    digitalWrite(BL_EN1,LOW);          //打开背光
    pinMode(BL_EN2,OUTPUT);
    digitalWrite(BL_EN2,LOW);          //打开背光
    tft.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tft.setRotation(1);                //旋转屏幕
    tft2.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tft2.setRotation(1);               //旋转屏幕
 
    tft.fillRect(0,0,160,80,ST77XX_RED);
    tft2.fillRect(0,0,160,80,ST77XX_GREEN);
    

    tft.drawLine(0,0,159,0,ST77XX_GREEN);        //第一块屏幕最顶部画一条线-蓝色
    tft.drawLine(0,1,159,1,ST77XX_BLACK);      //第一块屏幕第二排像素画一条线-黄色
    tft.drawLine(0,2,159,2,ST77XX_GREEN);      //第一块屏幕第三排像素画一条线
    tft.drawLine(0,3,159,3,ST77XX_BLACK);      //第一块屏幕第三排像素画一条线



    // tft.invertDisplay(true);        //两个屏幕反色
    // tft2.invertDisplay(true);
}
void loop(){
}