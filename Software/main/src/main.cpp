//名称：1.14.TFT彩屏投屏下位机程序
//作者：大超
//B站：super大大怪i
//时间：2021/7/14
//注意：上位机只能使用 彩屏投屏助手V1.0-1.2之间的版本
#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <TJpg_Decoder.h>
#include <pgmspace.h>
#include <square.h>
TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tft);

char* ssid     = "ikun"; //填写你的wifi名字
char* password = "hongpeiyu"; //填写你的wifi密码
// char* service_ip= "172.20.10.7";//上位机IP
char* service_ip= "100.2.133.0";//上位机IP
int httpPort = 8088; //设置上位机端口


WiFiClient client; //初始化一个客户端对象


bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t* bitmap)//jpg解码回调函数
{
  if ( y >= tft.height() ) return 0;
  tft.pushImage(x, y, w, h, bitmap);
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
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(TFT_BLACK);//黑色
  tft.setTextColor(TFT_BLACK,TFT_WHITE);
  
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

    tft.fillScreen(TFT_BLACK);
    

    Serial.println("wifi is connected!");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    IPAddress ip = WiFi.localIP();
    String ipString = ip.toString();
    Serial.print("IP Address: ");
    Serial.println(ip);

    




  }
  TJpgDec.setJpgScale(1);
  TJpgDec.setSwapBytes(true);
  TJpgDec.setCallback(tft_output);//解码成功回调函数
  Serial.println("TJpgDec.setCallback(tft_output);//解码成功回调函数");
  client.write("ok");//向上位机发送下一帧发送指令
}


void loop() {
  square();
 

}
