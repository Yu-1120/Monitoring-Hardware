#include <Arduino.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <LED.h>
#include <TFT_BIG.h>

TFT_eSPI tft_small;  //小的LCD屏用官网给的库直接调

const char* ssid     = "ikun";      // 连接WiFi名（此处使用taichi-maker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "hongpeiyu";          // 连接WiFi密码（此处使用12345678为示例）



void setup() {


  SPI_BLK_1;

  IO_init();
  SPI_CS_1;
  TFT_init();
  TFT_full(RED);
  TFT_clear();
//=============================
  LED_Init();
  tft_small.init();
  tft_small.setRotation(1);
  tft_small.setTextFont(1);
  tft_small.fillScreen(TFT_BLACK);


  Serial.begin(9600);         // 启动串口通讯

  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  tft_small.println("Start Config WiFi!");
  Serial.print(ssid); 
  
  Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接




  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' '); 
    tft_small.print(".");

    PIN_LED2_HIGH; //BOOT按键那边的灯
  }                                            
  PIN_LED2_LOW;
  PIN_LED1_HIGH; //BOOT按键那边的灯

  tft_small.drawString("Your ip:", 0, 40);  //屏幕是80x160的              
  tft_small.drawString(WiFi.localIP().toString(), 0, 60);  //屏幕是80x160的
}


void loop() {
  
  
}