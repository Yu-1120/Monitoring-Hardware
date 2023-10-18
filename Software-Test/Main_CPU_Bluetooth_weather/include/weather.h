#pragma once
#include <Arduino.h>
#include <TFT_Right.h>
#include <ArduinoJson.h>
#include <WiFi.h>

#include <Key.h>

const char* host = "api.seniverse.com";     // 将要连接的服务器地址  
const int httpPort = 80;                    // 将要连接的服务器端口      
 
// 心知天气HTTP请求所需信息
String reqUserKey = "SfGSzf23A2Ftdkzei";   // 私钥
String reqLocation = "Jiangmen";            // 城市
String reqUnit = "c";                      // 摄氏/华氏
// 利用ArduinoJson库解析心知天气响应信息
void parseInfo(WiFiClient client){
    const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
    DynamicJsonDocument doc(capacity);
    deserializeJson(doc, client);
    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_now = results_0["now"];
    const char* results_0_now_text = results_0_now["text"]; // "Sunny"
    const char* results_0_now_temperature = results_0_now["temperature"]; // "32"

    // 通过串口监视器显示以上信息
    String results_0_now_text_str = results_0_now["text"].as<String>(); 
    String results_0_now_temperature_str = "Tem:"+results_0_now["temperature"].as<String>();  

    Serial.println(F("======Weahter Now======="));
    Serial.print(F("Weather Now: "));
    Serial.println(results_0_now_text_str);
    Serial.print(F("Temperature: "));
    Serial.println(results_0_now_temperature_str);
    Serial.println(F("========================"));
    //city
    JsonObject results_location = results_0["location"];
    String results_location_name = results_location["name"]; // "Sunny"
    Serial.print(F("City: "));
    Serial.println(results_location_name);
    Serial.println(F("========================"));

    tftRight.fillScreen(TFT_BLACK);
    // tftRight.setCursor(0, 0);//* 将“光标”设置在显示器的左上角（0,0）
	/* 将“光标”设置在显示器的左上角（0,0），并选择字体2 */
	tftRight.setCursor(0, 0,2);
	/* 将字体颜色设置为白色，背景为黑色，将文本大小倍增设置为1 */
	tftRight.setTextColor(TFT_GREEN,TFT_BLACK);
	tftRight.setTextFont(4);  //支持2，4号大小,5号大小不支持了

    tftRight.println("City城市"+results_location_name);     //打印文字（字体有设置才有用）  这个天气返回的时候会中文乱码 
    tftRight.println(results_0_now_temperature_str);//Tem:xxx
    //体感温度:

    String results_0_now_feels_like_str = results_0_now["feels_like"];  
    Serial.print(F("feels_like: "));
    Serial.println(results_0_now_feels_like_str);
    Serial.println(F("========================"));
    //相对湿度
    String results_0_now_humidity = results_0_now["humidity"]; 
    // String results_0_now_feels_like_str = resul/ts_0_now_feels_like["feels_like"].as<String>();  
    Serial.print(F("results_0_now_humidity: "));
    Serial.println(results_0_now_humidity);
    Serial.println(F("========================"));
    //code天气代码
    String results_0_now_code = results_0_now["code"].as<String>(); 
    // String results_0_now_feels_like_str = resul/ts_0_now_feels_like["feels_like"].as<String>();  
    Serial.print(F("results_0_now_code: "));
    Serial.println(results_0_now_code);
    Serial.println(F("========================"));
    // https://docs.seniverse.com/api/weather/now.html
    // 获取指定城市的天气实况。付费用户可获取全部数据，免费用户只返回天气现象文字、代码和气温 3 项数据。注：中国城市暂不支持云量和露点温度。


}
// 向心知天气服务器服务器请求信息并对信息进行解析
void httpRequest(String reqRes){
    WiFiClient client;

    // 建立http请求信息
    String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                                "Host: " + host + "\r\n" + 
                                "Connection: close\r\n\r\n";
    Serial.println(""); 
    Serial.print("Connecting to "); 
    Serial.print(host);

    // 尝试连接服务器
    if (client.connect(host, 80)){
        Serial.println(" Success!");
     
        client.print(httpRequest);
        Serial.println("Sending request: ");
        Serial.println(httpRequest);  

        // 获取并显示服务器响应状态行 
        String status_response = client.readStringUntil('\n');
        Serial.print("status_response: ");
        Serial.println(status_response);

        // 使用find跳过HTTP响应头
        if (client.find("\r\n\r\n")) {
            Serial.println("Found Header End. Start Parsing.");
        }
       
        // 利用ArduinoJson库解析心知天气响应信息
        parseInfo(client); 
    } else {
         Serial.println(" connection failed!");
    }   
    //断开客户端与服务器连接工作
    


    client.stop(); 
}

void  WeatherTime(){
    while (1)
    {
        Serial.println("WeatherTime()");
        int state_C = digitalRead(BTN_C);
        //在里面进行设定退出正方形选择方块
        if (state_C == LOW) {
            Serial.println("client.stop()");
            tftRight.fillScreen(TFT_BLACK);
            // tftRight.setCursor(0, 0);//* 将“光标”设置在显示器的左上角（0,0）
            /* 将“光标”设置在显示器的左上角（0,0），并选择字体2 */
            tftRight.setCursor(0, 0,2);
            /* 将字体颜色设置为白色，背景为黑色，将文本大小倍增设置为1 */
            tftRight.setTextColor(TFT_GREEN,TFT_BLACK);
            tftRight.setTextFont(4);  //支持2，4号大小,5号大小不支持了

            tftRight.println("Exit weather");     //打印文字（字体有设置才有用）  这个天气返回的时候会中文乱码 
            break ;
            // 执行中按键按下时的操作
        }
        tftRight.fillScreen(TFT_BLACK);
        // tftRight.setCursor(0, 0);//* 将“光标”设置在显示器的左上角（0,0）
        /* 将“光标”设置在显示器的左上角（0,0），并选择字体2 */
        tftRight.setCursor(0, 0,2);
        // 建立心知天气API当前天气请求资源地址
        String reqRes = "/v3/weather/now.json?key=" + reqUserKey +
                        + "&location=" + reqLocation + 
                        "&language=en&unit=" +reqUnit;
        
        // 向心知天气服务器服务器请求信息并对信息进行解析
        httpRequest(reqRes);
        delay(500);

 

    }
    
}