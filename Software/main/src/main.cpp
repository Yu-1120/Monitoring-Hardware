#include <Arduino.h>
#include <Fonts/FreeMono12pt7b.h>
#include <TJpg_Decoder.h>
#include <pgmspace.h>
#include <square.h>
#include <key.h>
#include <TFT_Left.h>
#include <TFT_Right.h>
#include <menu.h>
#include <TFT_clock.h>


void setup(){
    Serial.begin(9600); // 初始化串口通信
    pinMode(BL_EN1,OUTPUT);
    digitalWrite(BL_EN1,LOW);          //打开背光
    tftLeft.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tftLeft.setRotation(1);                //旋转屏幕
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    Key_Init();

}
void loop(){
    // Key_check();
    int choice = Key_check();
    switch (choice)
    {
    case 1:
        helloworld();
            //
        WifiInit();
        square_for_2000();
        break;
    case 2:
        BlueTooth();
        break;
    case 3:
        CPU();
        break;
    case 4:
        Clock();
        ClockInit();
        WifiInit();
        ClockTime();
        break;
    default:
        break;
    }



}