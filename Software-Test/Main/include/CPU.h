#pragma once
#include <Arduino.h>
#include <TFT_Right.h>
#include <WiFi.h>
#include <Key.h>
#include <TFT_Right.h>
#include <TFT_eSPI.h>


WiFiServer server; //声明服务器对象


void CPU_Show(String GPU_Rate){

  
    tftRight.fillScreen(TFT_BLACK);//黑色
    // tftRight.setCursor(0, 0);//* 将“光标”设置在显示器的左上角（0,0）
	/* 将“光标”设置在显示器的左上角（0,0），并选择字体2 */
	tftRight.setCursor(0, 0,2);
	/* 将字体颜色设置为白色，背景为黑色，将文本大小倍增设置为1 */

	tftRight.setTextColor(TFT_GREEN,TFT_BLACK);
	tftRight.setTextFont(4);  //支持2，4号大小,5号大小不支持了
	tftRight.println(GPU_Rate);
    
}
void CPU_TCP(){
    server.begin(2333); //服务器启动，端口号2333
    while(1){
        
        WiFiClient client = server.available(); //尝试建立客户对象
        if (client) //如果当前客户可用
        {
            Serial.println("[Client connection present]");//存在客户端连接
            String readBuff;    //读取信息暂存
            while (client.connected()) //如果客户端处于连接状态
            {
                if (client.available()) //如果有可读数据
                {
                    char c = client.read(); //读取一个字节
                                            //也可以用readLine()等其他方法
                    readBuff += c;
                    if(c == '\r') //接收到回车符W
                    {
                        client.println("Received:" + readBuff); //向客户端发送
                        Serial.println("Received: " + readBuff); //从串口打印
                        CPU_Show(readBuff);
                        readBuff = "";
                        // break; //跳出循环
                    }
                }
            }
            
            int state_C = digitalRead(BTN_C);
            //在里面进行设定退出正方形选择方块
            if (state_C == LOW) {
               
                client.stop(); //结束当前连接:
                Serial.println("[No client connection]");//无客户端连接
                break ;
                
                // 执行中按键按下时的操作
            }

        }
        int state_C = digitalRead(BTN_C);
        //在里面进行设定退出正方形选择方块
        if (state_C == LOW) {
        // Serial.println("Button C pressed");
         Serial.println("exit CPU information");
            break ;
            // 执行中按键按下时的操作
        }


    }
   
}

