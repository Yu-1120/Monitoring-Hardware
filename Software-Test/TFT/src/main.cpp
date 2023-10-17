//名称：1.14.TFT彩屏投屏下位机程序
//作者：大超
//B站：super大大怪i
//时间：2021/7/14
//注意：上位机只能使用 彩屏投屏助手V1.0-1.2之间的版本
#include <TFT_eSPI.h>
#include <SPI.h>

#include <TJpg_Decoder.h>
#include <pgmspace.h>
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tft);





void setup() {
  clk.setColorDepth(8);
  
  clk.createSprite(200, 50);
  clk.fillSprite(0x0000);

  clk.drawRoundRect(0,0,200,16,8,0xFFFF);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_GREEN, 0x0000); 
  clk.drawString("Connecting to WiFi",100,40,2);
  clk.pushSprite(20,67);//20 110
  clk.deleteSprite();

}


void loop() {

}
