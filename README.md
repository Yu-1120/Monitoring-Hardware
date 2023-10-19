# 更新记录



| 时间                   |                                                              |
| ---------------------- | ------------------------------------------------------------ |
| 2023年10月16日18点33分 | 成功运行                                                     |
| 2023-10-18-12点54分    | 集成了天气，上位机TCP通信传输数据到单片机                    |
| 2023年10月19日13点14分 | 集成了天气，上位机TCP通信传输数据到单片机，**集成到蓝牙（做为一个模拟键盘）** |
|                        |                                                              |







# 基于Socket通信的电脑智能监控硬件

## 项目介绍

​	本项目是基于ESP32C3的软硬件结合的项目，单片机的控制程序和上位机的TCP 传输数据程序，相比之下,上位机的编写是较为简单的，做一个关于显示电脑参数的硬件，可以通过TCP传回显示CPU的运行速度，可以通过Wifi获取到Http上的天气数据，也可以把当成蓝牙键盘来进行操作电脑。







## 技术实现



![ESP32-C3](Readme.assets/ESP32-C3.png)

## 主要功能











## 1-硬件



### 实物图



![image-20231017162509148](Readme.assets/image-20231017162509148.png)





![image-20231017162528778](Readme.assets/image-20231017162528778.png)



### 电路图



### PCB仿真图

#### 2023-10-9

![实物仿真图1](Readme.assets/实物仿真图1.png)



![实物仿真图](Readme.assets/实物仿真图.png)

### Gerber文件

https://github.com/Yu-1120/Monitoring-Hardware/blob/master/hareware/V1_2023-10-13/Gerber_PCB1_2023-10-13.zip

### 可以优化的地方



#### 







## 2-软件

















![image-20231018014341436](Readme.assets/image-20231018014341436.png)









## 参考链接（调用的库）



- https://blog.csdn.net/u013742125/article/details/130592427     TFT_eSPI库之相关API

- https://blog.csdn.net/qq_43415898/article/details/129126193    驱动两个spi屏的问题

- Adafruit_GFX（小的屏幕驱动)

- 










