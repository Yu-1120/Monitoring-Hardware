#include <Arduino.h>
#include <BleKeyboard.h>
#include <Bounce2.h>
#include <TFT_eSPI.h>
#include <SPI.h>

#define BTN_U 8
#define BTN_D 5
#define BTN_L 9
#define BTN_R 13
#define BTN_C 4

TFT_eSPI tft = TFT_eSPI();
BleKeyboard bleKeyboard("ESP32 Media", "Espressif", 100);

Bounce2::Button button_u = Bounce2::Button();
Bounce2::Button button_d = Bounce2::Button();
Bounce2::Button button_l = Bounce2::Button();
Bounce2::Button button_r = Bounce2::Button();
Bounce2::Button button_c = Bounce2::Button();

unsigned char keyValue = 0;

void setup()
{
  Serial.begin(115200);
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
  tft.init();
  //tft.setRotation(2);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_BLUE, TFT_BLACK);
}

void loop()
{
  if (bleKeyboard.isConnected())
  {
    keyValue = keyScan();
    if (keyValue != 0) {
      switch (keyValue) {
      case 1: bleKeyboard.write(KEY_MEDIA_VOLUME_UP);   break;
      case 2: bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN); break;
      case 3: bleKeyboard.write(KEY_MEDIA_PREVIOUS_TRACK); break;
      case 4: bleKeyboard.write(KEY_MEDIA_NEXT_TRACK);  break;
      case 5: bleKeyboard.write(KEY_MEDIA_MUTE);        break;
      }
    }
  }
}

unsigned char keyScan(void)
{
  button_u.update();
  button_d.update();
  button_l.update();
  button_r.update();
  button_c.update();

  if      (button_u.pressed()) {return 1; tft.drawString("UP", 0, 0, 2);}
  else if (button_d.pressed()) {return 3; tft.drawString("DOWN", 0, 0, 2);}
  else if (button_l.pressed()) {return 4; tft.drawString("LEFT", 0, 0, 2);}
  else if (button_r.pressed()) {return 2; tft.drawString("RIGHT", 0, 0 , 2);}
  else if (button_c.pressed()) {return 5; tft.drawString("CENTER", 0, 0 , 2);}
  else                         return 0;
}