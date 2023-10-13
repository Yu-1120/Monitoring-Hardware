#include <Arduino.h>
#include <TFT_eSPI.h>
#include <TFT_Big,h> //大的屏我直接写SPI来控制
#include <WiFi.h>
#include <LED.h>


TFT_eSPI tft_small;  //小的LCD屏用官网给的库直接调

const char* ssid     = "ikun";      // 连接WiFi名（此处使用taichi-maker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "hongpeiyu";          // 连接WiFi密码（此处使用12345678为示例）

void  TFT_BIN_INTT(){
        SPI_BLK_1;

        IO_init();
        SPI_CS_1;
        TFT_init();
        TFT_full(RED);
        delay(100);
        TFT_clear();
}



void setup() {


  tft_small.init();
  tft_small.setRotation(1);
  tft_small.setTextFont(2);
  tft_small.fillScreen(TFT_BLACK);


  Serial.begin(9600);         // 启动串口通讯

  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  tft_small.drawString("Start Config WiFi!", 0, 0);
  Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
    LED_LED1_Blink();

  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。
  PIN_LED1_LOW;           
  PIN_LED2_HIGH;                                    
  Serial.println("");                          // WiFi连接成功后
  Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
  Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
  Serial.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。
  tft_small.drawString(WiFi.localIP().toString(), 1, 2);
}


void loop() {
  TFT_BIN_INTT();





}