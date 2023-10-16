#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
// #include <SPI.h>
#include <Fonts/FreeMono12pt7b.h>
#define TFT_CS      7        //管脚定义，左边的屏幕
#define TFT_RST    10
#define TFT_DC      6
#define TFT_SCLK    2
#define TFT_MOSI    3
 

#define BTN_U 13
#define BTN_D 8
#define BTN_L 9
#define BTN_R 5
#define BTN_C 4

 
#define BL_EN1   8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);
 

void helloworld(){
    tft.fillRect(0,0,160,80,ST77XX_BLACK);
    tft.setTextSize(2);  // 设置字体大小
    tft.setFont(&FreeMono12pt7b);
    tft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tft.setCursor(0, 30); // 设置文本位置

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tft.print(F("Hello World")); //读不了中文

}

void share(){
    tft.fillRect(0,0,160,80,ST77XX_BLACK);
    tft.setTextSize(2);  // 设置字体大小
    tft.setFont(&FreeMono12pt7b);
    tft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tft.setCursor(0, 30); // 设置文本位置

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tft.print(F("Share Screen")); //读不了中文

}
void CPU(){
    tft.fillRect(0,0,160,80,ST77XX_BLACK);
    tft.setTextSize(2);  // 设置字体大小
    tft.setFont(&FreeMono12pt7b);
    tft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tft.setCursor(0, 30); // 设置文本位置

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tft.print(F("Look at CPU")); //读不了中文


}


void setup(){
    pinMode(BL_EN1,OUTPUT);
    digitalWrite(BL_EN1,LOW);          //打开背光
    tft.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tft.setRotation(1);                //旋转屏幕
 
    tft.fillRect(0,0,160,80,ST77XX_BLACK);
    
    pinMode(BTN_U, INPUT_PULLUP); // 使用内部上拉电阻，按钮未按下时为高电平
    pinMode(BTN_D, INPUT_PULLUP);
    pinMode(BTN_L, INPUT_PULLUP);
    pinMode(BTN_R, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);


    Serial.begin(9600); // 初始化串口通信
}
int key_check(){
   // 读取按键状态
    int state_U = digitalRead(BTN_U);
    int state_D = digitalRead(BTN_D);
    int state_L = digitalRead(BTN_L);
    int state_R = digitalRead(BTN_R);
    int state_C = digitalRead(BTN_C);
  // 判断按键状态并执行相应操作
  if (state_D == LOW) {
    // Serial.println("Button D pressed");
    return 1;
    // 执行上按键按下时的操作
  }
  if (state_R == LOW) {
    return 2;
    // Serial.println("Button R pressed");
    // // 执行下按键按下时的操作
  }
  if (state_L == LOW) {
    // Serial.println("Button L pressed");
    return 3;
    // 执行左按键按下时的操作
  }
  if (state_U == LOW) {
    // Serial.println("Button U pressed");
    return 4;
    
    // 执行右按键按下时的操作
  }
  if (state_C == LOW) {
    // Serial.println("Button C pressed");
    return 5;
    // 执行中按键按下时的操作
  }

}

void loop(){
    // key_check();
    int choice = key_check();
    switch (choice)
    {
    case 1:
        helloworld();
        break;
    case 2:
        share();
        break;
    case 3:
        CPU();
        break;
    default:
        break;
    }



}