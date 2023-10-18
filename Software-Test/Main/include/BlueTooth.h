#pragma one
#include <BleKeyboard.h>
#include <Bounce2.h>
#include <Key.h>
BleKeyboard bleKeyboard("ESP32 Media", "Espressif", 100);

Bounce2::Button button_u = Bounce2::Button();
Bounce2::Button button_d = Bounce2::Button();
Bounce2::Button button_l = Bounce2::Button();
Bounce2::Button button_r = Bounce2::Button();
Bounce2::Button button_c = Bounce2::Button();
unsigned char keyValue = 0;

void BlueToothInit(){

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


}

unsigned char keyScan(void)
{
  button_u.update();
  button_d.update();
  button_l.update();
  button_r.update();
  button_c.update();

  if      (button_u.pressed()) return 1;
  else if (button_d.pressed()) return 3;
  else if (button_l.pressed()) return 4;
  else if (button_r.pressed()) return 2;
  else if (button_c.pressed()) return 5;
  else                         return 0;
}

void BlueKeyboardDriver(){

    while (1)
    {
        if (bleKeyboard.isConnected())
        {
            keyValue = keyScan();
            if (keyValue != 0) {
            switch (keyValue) {
            case 1: 
                bleKeyboard.write(KEY_MEDIA_VOLUME_DOWN);   
            break;
            case 2: 
                bleKeyboard.write(KEY_MEDIA_VOLUME_UP); 
            break;
            case 3: 
                bleKeyboard.write(KEY_MEDIA_WWW_HOME);
            break;
            case 4: 
                bleKeyboard.write(KEY_MEDIA_LOCAL_MACHINE_BROWSER);  
            break;
            case 5: 
                bleKeyboard.write(KEY_MEDIA_MUTE);        
            break;
            }
            }
        }
        int state_C = digitalRead(BTN_C);
        //在里面进行设定退出正方形选择方块
        if (state_C == LOW) {
        // Serial.println("Button C pressed");
            break ;
            // 执行中按键按下时的操作
        }


    }

 


}