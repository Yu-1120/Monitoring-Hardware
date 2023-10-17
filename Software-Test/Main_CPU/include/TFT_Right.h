#pragma once
#include <TFT_eSPI.h>
#include <WiFi.h>
TFT_eSPI tftRight = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tftRight);

char* ssid     = "ikun"; //填写你的wifi名字
char* password = "hongpeiyu"; //填写你的wifi密码

bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)//jpg解码回调函数
{
  if ( y >= tftRight.height() ) return 0;
  tftRight.pushImage(x, y, w, h, bitmap);
  // Return 1 to decode next block
  return 1;
}

byte loadNum = 6;
void loading(byte delayTime)
{//启动动画
  
  clk.setColorDepth(8);
  
  clk.createSprite(200, 50);
  clk.fillSprite(0x0000);

  clk.drawRoundRect(0,0,200,16,8,0xFFFF);
  clk.fillRoundRect(3,3,loadNum,10,5,0xFFFF);
  clk.setTextDatum(CC_DATUM);
  clk.setTextColor(TFT_GREEN, 0x0000); 
  clk.drawString("Connecting to WiFi",100,40,2);
  clk.pushSprite(20,67);//20 110
  clk.deleteSprite();


  loadNum += 1;
  if(loadNum>=195)
  {
      loadNum = 195;
  }
  delay(delayTime);
}

void WifiInit(){

  tftRight.begin();
  tftRight.setRotation(3);
  tftRight.fillScreen(TFT_BLACK);//黑色
  tftRight.setTextColor(TFT_BLACK,TFT_WHITE);
  // delate don't   worry
  WiFi.mode(WIFI_STA);
  WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
  //

  WiFi.begin(ssid, password); //连接wifi
  delay(1000); //等待1秒
  while (WiFi.status() != WL_CONNECTED) {
    for(byte n=0;n<10;n++){ //每500毫秒检测一次状态
      loading(50);
    }
  }
   while(loadNum < 195){ //让动画走完
    loading(3);
   }
  if (WiFi.status() == WL_CONNECTED) //判断如果wifi连接成功
  { 
    tftRight.fillScreen(TFT_BLACK);
    Serial.println("wifi is connected!");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    String ipString = ip.toString();
    Serial.print("IP Address: ");
    Serial.println(ip);

  }


}


