#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#include <Fonts/FreeMono12pt7b.h>
//
#include <TFT_eSPI.h>
#include <SPI.h>
#include <WiFi.h>
#include <TJpg_Decoder.h>
#include <pgmspace.h>
#include <square.h>


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



TFT_eSPI tftRight = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tftRight);
//左边的屏幕
Adafruit_ST7735 tftLeft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); 

#define BL_EN1 8

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

void helloworld(){
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置
    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F("Hello World")); //读不了中文

}

void share(){
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

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F(" CPU Info ")); //读不了中文


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

void square_for_2000(){
  

  for (size_t i = 0; i < 2000; i++)
  {
    square();
    int state_C = digitalRead(BTN_C);
    //在里面进行设定退出正方形选择方块
    if (state_C == LOW) {
    // Serial.println("Button C pressed");
          break ;
        // 执行中按键按下时的操作
    }
     
  }
  
  
}

void setup(){
    Serial.begin(9600); // 初始化串口通信


    pinMode(BL_EN1,OUTPUT);
    digitalWrite(BL_EN1,LOW);          //打开背光
    tftLeft.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tftLeft.setRotation(1);                //旋转屏幕
    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    


    pinMode(BTN_U, INPUT_PULLUP); // 使用内部上拉电阻，按钮未按下时为高电平
    pinMode(BTN_D, INPUT_PULLUP);
    pinMode(BTN_L, INPUT_PULLUP);
    pinMode(BTN_R, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);


}
void loop(){
    // key_check();
    int choice = key_check();
    switch (choice)
    {
    case 1:
        helloworld();
            //
        WifiInit();
        square_for_2000();
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