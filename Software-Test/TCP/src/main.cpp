#include <WiFi.h>

const char *ssid = "ikun";
const char *password = "hongpeiyu";

WiFiServer server; //声明服务器对象

void setup()
{
    Serial.begin(115200);   //串口初始化
    Serial.println();

    WiFi.mode(WIFI_STA);
    WiFi.setSleep(false); //关闭STA模式下wifi休眠，提高响应速度
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)  
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Connected");
    Serial.print("IP Address:");
    Serial.println(WiFi.localIP());

    server.begin(2333); //服务器启动，端口号2333
}

void loop()
{
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
                    readBuff = "";
                    // break; //跳出循环
                }
            }
        }
        client.stop(); //结束当前连接:
        Serial.println("[No client connection]");//无客户端连接
    }
}