# Luatos_C3 80x160 TFT_eSPI 

## demo
![demo](https://gitee.com/lai-shanhai/luatos_esp32c3_ble_media_keyboard/raw/master/luatos_esp32c3_ble_media_keyboard.jpg)  
## User.Setup.h
```
47  #define ST7735_DRIVER
77  #define TFT_RGB_ORDER TFT_BGR    // Colour order Blue-Green-Red
84  #define TFT_WIDTH 80
88  #define TFT_HEIGHT 160
109 #define ST7735_REDTAB160x80 // For 160 x 80 display with 24 pixel offset
216 #define TFT_MOSI 3
217 #define TFT_SCLK 2
218 #define TFT_CS   7
219 #define TFT_DC   6
220 #define TFT_RST  10
223 #define TOUCH_CS -1 
