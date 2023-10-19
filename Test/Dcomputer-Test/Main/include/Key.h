
#pragma once
#include <Arduino.h>
#define BTN_U 13
#define BTN_D 8
#define BTN_L 9
#define BTN_R 5
#define BTN_C 4


void Key_Init(){
    
    pinMode(BTN_U, INPUT_PULLUP); // 使用内部上拉电阻，按钮未按下时为高电平
    pinMode(BTN_D, INPUT_PULLUP);
    pinMode(BTN_L, INPUT_PULLUP);
    pinMode(BTN_R, INPUT_PULLUP);
    pinMode(BTN_C, INPUT_PULLUP);

}


int Key_check(){
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