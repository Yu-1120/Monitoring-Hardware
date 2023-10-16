//获取网络时间相关库
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>

//TFT显示库
#include <TFT_eSPI.h>

//导入图片
#include "clock1.h"

//导入字库
#include "noto10.h"
#include "noto20.h"

//网络时间相关定义
const char *ssid = "自己的Wi-Fi账号";      // WiFi账号
const char *password = "自己的Wi-Fi密码";  // WiFi密码
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com");  // NTP服务器地址

//TFT相关定义
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);  // 创建一个 TFT_eSprite 对象，tft 是你的 TFT 显示对象

void setup() {
  //===网络时间初始化设定===
  Serial.begin(115200);  // 初始化串口通信，波特率为115200
  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {  // 等待WiFi连接成功
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();               // 初始化NTPClient
  timeClient.setTimeOffset(28800);  // 设置时间偏移为28800秒（8小时）

  // ===TFT初始化设定===
  tft.begin();                    // 初始化显示寄存器
  tft.setRotation(0);             // 设置显示屏旋转角度（0表示不旋转，根据需要调整）
  sprite.setColorDepth(16);       // 设置颜色深度（根据你的需求）
  sprite.setSwapBytes(true);      // 设置字节顺序，将RGB颜色顺序转换为BGR以正确显示颜色。
  sprite.createSprite(128, 128);  // 创建一个128x128像素的绘图窗口
}

void loop() {
  timeClient.update();                                  // 更新时间信息
  unsigned long epochTime = timeClient.getEpochTime();  // 获取当前时间的时间戳


  // 将epochTime换算成年月日
  struct tm *ptm = gmtime((time_t *)&epochTime);  // 将时间戳转换为tm结构体
  struct tm *ptm = gmtime((time_t*)&epochTime);
  int currentYear = ptm->tm_year + 1900;          //获取年份
  int currentMonth = ptm->tm_mon + 1;             // 获取月份
  int currentMonthDay = ptm->tm_mday;             // 获取月份中的日期
  int currentWeekDay = ptm->tm_wday;              // 获取星期几
  int currentHour = ptm->tm_hour;                 //获取时
  int currentMin = ptm->tm_min;                   //获取分
  int currentSec = ptm->tm_sec;                   //获取秒

  // 定义一个字符串数组，用于存储星期描述，将星期几换成中文
  const char weekdays[8][10] = { "0", "周一", "周二", "周三", "周四", "周五", "周六", "周日" };


  // 打印时间
  Serial.println("Epoch Time: " + String(epochTime));  //打印时间戳
  Serial.println(timeClient.getFormattedTime());       //打印时间格式

  //tft显示时间

  sprite.fillScreen(TFT_BLACK);              //清屏
  sprite.pushImage(0, 0, 128, 128, clock1);  //显示底图

  sprite.setCursor(55, 35);                //设定打印位置
  sprite.loadFont(noto10);                 //设定显示字体
  sprite.print(weekdays[currentWeekDay]);  //打印 星期几

  sprite.setCursor(55, 45);                                            //设定打印位置
  sprite.print(String(currentMonth) + "/" + String(currentMonthDay));  //打印 月/日

  sprite.setCursor(40, 60);                                      //设定打印位置
  sprite.loadFont(noto20);                                       //设定显示字体
  sprite.print(String(currentHour) + ":" + String(currentMin));  //打印 时：分

  sprite.setCursor(60, 80);          //设定打印位置
  sprite.loadFont(noto10);           //设定显示字体
  sprite.print(String(currentSec));  //打印 秒

  sprite.pushSprite(0, 0);  // 将 sprite 显示在指定的屏幕位置 (0, 0)


  delay(1000);  // 延迟1秒，每秒更新一次
}
