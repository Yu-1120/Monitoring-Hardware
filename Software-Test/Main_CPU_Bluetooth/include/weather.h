#pragma once
#include <Arduino.h>
#include <TFT_Right.h>

#include <WiFi.h>

#include <Key.h>


void  WeatherTime(){
    while (1)
    {
        Serial.println("ClockTime()");
        int state_C = digitalRead(BTN_C);
        //在里面进行设定退出正方形选择方块
        if (state_C == LOW) {
        // Serial.println("Button C pressed");
            break ;
            // 执行中按键按下时的操作
        }

    }
    
}