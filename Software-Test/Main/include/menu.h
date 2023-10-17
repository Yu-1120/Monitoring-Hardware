#pragma one
#include <TFT_Left.h>
#include <Fonts/FreeMono12pt7b.h>
#include <TFT_Right.h>


void Helloworld(){
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置
    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F("Hello World")); //读不了中文
        

}




void Wifi_Menu(){
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置
    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F("Wifi")); //读不了中文

}


void BlueTooth(){
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F("Blue Tooth")); //读不了中文

}

void CPU(){

    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置
    tftLeft.print(F(" CPU Infor ")); //读不了中文


}



void Weather(){

    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置

    tftLeft.print(F("Weather")); 


}
