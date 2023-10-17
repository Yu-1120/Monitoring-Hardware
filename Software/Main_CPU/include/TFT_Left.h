#pragma once

#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
// #include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
//左边的屏幕
#define TFT_CS      7        //管脚定义，左边的屏幕
#define TFT_RST    10
#define TFT_DC      6
#define TFT_SCLK    2
#define TFT_MOSI    3

#define BL_EN1 8
Adafruit_ST7735 tftLeft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST); 