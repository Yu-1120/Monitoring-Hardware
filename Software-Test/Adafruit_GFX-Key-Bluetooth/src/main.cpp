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

#include <BleKeyboard.h>
#include <Bounce2.h>

unsigned char keyValue = 0;

#define TFT_CS      7        //管脚定义，左边的屏幕
#define TFT_RST    10
#define TFT_DC      6
#define TFT_SCLK    2
#define TFT_MOSI    3

BleKeyboard bleKeyboard("ESP32蓝牙键盘","Espressif",100);//其中“ESP32蓝牙键盘”为键盘名称；"Espressif"为制造商

Bounce2::Button button_u = Bounce2::Button();
Bounce2::Button button_d = Bounce2::Button();
Bounce2::Button button_l = Bounce2::Button();
Bounce2::Button button_r = Bounce2::Button();
Bounce2::Button button_c = Bounce2::Button(); 


#define BTN_U 13
#define BTN_D 8
#define BTN_L 9
#define BTN_R 5
#define BTN_C 4


#define BL_EN1 8

TFT_eSPI tftRight = TFT_eSPI(); 
TFT_eSprite clk = TFT_eSprite(&tftRight);
//左边的屏幕
Adafruit_ST7735 tftLeft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); 

char* ssid     = "ikun"; //填写你的wifi名字
char* password = "hongpeiyu"; //填写你的wifi密码
void BluetoothInit()
{

  Serial.println("Starting BLE Work!");
  
  button_u.attach(BTN_U, INPUT_PULLUP);
  button_d.attach(BTN_D, INPUT_PULLUP);
  button_l.attach(BTN_L, INPUT_PULLUP);
  button_r.attach(BTN_R, INPUT_PULLUP);
  button_c.attach(BTN_C, INPUT_PULLUP);
  
  button_u.interval(5);
  button_d.interval(5);
  button_l.interval(5);
  button_r.interval(5);
  button_c.interval(5);

  button_u.setPressedState(LOW);
  button_d.setPressedState(LOW);
  button_l.setPressedState(LOW);
  button_r.setPressedState(LOW);
  button_c.setPressedState(LOW);

  bleKeyboard.begin();
  tftRight.init();
  tftRight.setRotation(3);
  
  tftRight.fillScreen(TFT_BLACK);
  tftRight.setTextColor(TFT_BLUE, TFT_BLACK);
  tftRight.drawString("Bluetooth", 0, 0, 2);
  tftRight.setTextColor(TFT_YELLOW, TFT_BLACK);
  tftRight.drawString("up - V+  down - V-", 0, 16, 2);
  tftRight.drawString("left - >   right - <", 0, 32, 2);
  tftRight.drawString("center - Vol  mute", 0, 48, 2);


}
void Bluetooth(){

    tftLeft.fillRect(0,0,160,80,ST77XX_BLACK);
    tftLeft.setTextSize(2);  // 设置字体大小
    tftLeft.setFont(&FreeMono12pt7b);
    tftLeft.setTextColor(ST77XX_WHITE); // 设置字体颜色
    tftLeft.setCursor(0, 30); // 设置文本位置

    // 在左边的屏幕上显示中文
    // tft.print(F("你好，世界！hell,world")); //读不了中文
    tftLeft.print(F("Blue tooth")); //读不了中文
    
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

void BluetoothDriver()
{

  if(bleKeyboard.isConnected()) {
    //多媒体测试
    Serial.println("Sending Play/Pause media key...");
    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
 
    delay(1000);
 
    //Ctrl+Alt+Delete任务管理器，并进行锁屏操作
    Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
 
    //输入密码并开机
    Serial.println("下面填入你的开机密码↓");
    bleKeyboard.print("--你的开机密码，注意大小写--");
    delay(100);
    Serial.println("Enter");
    bleKeyboard.write(KEY_RETURN);
  }
  Serial.println("Waiting 5 seconds...");



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

void setup(){
    Serial.begin(9600); // 初始化串口通信


    pinMode(BL_EN1,OUTPUT);
    digitalWrite(BL_EN1,LOW);          //打开背光
    tftLeft.initR(INITR_MINI160x80);      // Init ST7735S chip, black tab
    tftLeft.setRotation(1);                //旋转屏幕
    tftLeft.fillRect(0,0,160,80,ST77XX_BLUE);
    


    pinMode(BTN_U, INPUT_PULLUP); // 使用内部上拉电阻，按钮未按下时为高电平
    pinMode(BTN_D, INPUT_PULLUP);
    pinMode(BTN_L, INPUT_PULLUP);
    pinMode(BTN_R, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);

    BluetoothInit();
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
        Bluetooth();
        BluetoothDriver();
        break;
    case 3:

        break;
    default:
        break;
    }



}