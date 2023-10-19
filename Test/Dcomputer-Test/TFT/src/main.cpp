#include <Arduino.h>
#include <TFT_eSPI.h>
 
 
#define TFT_GREY 0x5AEB // New colour
TFT_eSPI tft = TFT_eSPI();
 
#define LCD_BL_PIN 8				// PWD 的 IO 引脚
#define LCD_BL_PWM_CHANNEL 0		// Channel  通道, 0 ~ 16，高速通道（0 ~ 7）由80MHz时钟驱动，低速通道（8 ~ 15）由 1MHz 时钟驱动
 
 
void displayes()
{
	Serial.begin(115200);
	/* 清屏函数，将背景颜色设置为灰色 */
    tft.fillScreen(TFT_GREY);
    tft.setRotation(3);
	
	tft.setCursor(0, 0);//* 将“光标”设置在显示器的左上角（0,0）
	/* 将“光标”设置在显示器的左上角（0,0），并选择字体2 */
	// tft.setCursor(0, 0,2);
	/* 将字体颜色设置为白色，背景为黑色，将文本大小倍增设置为1 */
	tft.setTextColor(TFT_WHITE,TFT_BLACK);  
	tft.setTextSize(1);
	// We can now plot text on screen using the "print" class
	tft.println("Hello World!");
	
	// Set the font colour to be yellow with no background, set to font 7
	tft.setTextColor(TFT_YELLOW,TFT_BLACK); tft.setTextFont(7);
	tft.println(1234.56);
	
	// Set the font colour to be green with black background, set to font 4
	tft.setTextColor(TFT_GREEN,TFT_BLACK);
	tft.setTextFont(4);
	tft.println("Groop");
	tft.println("I implore thee,");
 
	// Change to font 2
	tft.setTextFont(2);
	tft.println("my foonting turlingdromes.");
	tft.println("And hooptiously drangle me");
	tft.println("with crinkly bindlewurdles,");
	// This next line is deliberately made too long for the display width to test
	// automatic text wrapping onto the next line
	tft.println("Or I will rend thee in the gobberwarts with my blurglecruncheon, see if I don't!");
	
	// Test some print formatting functions
	float fnumber = 123.45;
	// Set the font colour to be blue with no background, set to font 4
	tft.setTextColor(TFT_BLUE);    tft.setTextFont(4);
	tft.print("Float = "); tft.println(fnumber);           // Print floating point number
	tft.print("Binary = "); tft.println((int)fnumber, BIN); // Print as integer value in binary
	tft.print("Hexadecimal = "); tft.println((int)fnumber, HEX); // Print as integer number in Hexadecimal
}
 
void setup() {
	// /* 配置LED PWM通道属性，PWD通道为 0，频率为1KHz */
    ledcSetup(LCD_BL_PWM_CHANNEL, 1000, 8);
 
	// /* 配置LED PWM通道属性 */
    ledcAttachPin(LCD_BL_PIN, LCD_BL_PWM_CHANNEL);
 
	ledcWrite(LCD_BL_PWM_CHANNEL, (int)(1 * 255));
 
	tft.init();
    tft.setRotation(0);
    tft.invertDisplay(0);
 
	displayes();
}
 
void loop() {
  // put your main code here, to run repeatedly:
}