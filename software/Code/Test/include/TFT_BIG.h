/********************金逸晨**************************
*****************GMT024-01   模块 2.4寸  7PIN SPI TFT FOR Arduino*************
*****3----3SCL,   4----4SDA,      5---5RST,
      6---6AO,      7----7CS    8---8BL
*********ST7789V2

从左往右，从上往下    240*320  16bit 5 6 5 RGB 模式  高位模式
********************************************************/
#include <Arduino.h>
#define SPI_SCK_0  digitalWrite(0,LOW)             
#define SPI_SCK_1  digitalWrite(0,HIGH) 
#define SPI_SDA_0  digitalWrite(1,LOW)               
#define SPI_SDA_1  digitalWrite(1,HIGH)
#define SPI_RST_0  digitalWrite(12,LOW)               
#define SPI_RST_1  digitalWrite(12,HIGH)
#define SPI_DC_0  digitalWrite(18,LOW)               
#define SPI_DC_1  digitalWrite(18,HIGH)
#define SPI_CS_0  digitalWrite(19,LOW)               
#define SPI_CS_1 digitalWrite(19,HIGH)
#define SPI_BLK_0 digitalWrite(8,LOW)
#define SPI_BLK_1 digitalWrite(8,HIGH)

#define     RED          0XF800    //红色
#define     GREEN        0X07E0   //绿色
#define     BLUE         0X001F   //蓝色
#define     WHITE        0XFFFF   //白色

#define TFT_COLUMN_NUMBER 240
#define TFT_LINE_NUMBER 320
#define TFT_COLUMN_OFFSET 0

#define PIC_NUM 28800     //图片数据大小

const unsigned char  *point;
const unsigned char chines_word[][32]=       //
{
    {0x00,0x00,0xE4,0x3F,0x28,0x20,0x28,0x25,0x81,0x08,0x42,0x10,0x02,0x02,0x08,0x02,
    0xE8,0x3F,0x04,0x02,0x07,0x07,0x84,0x0A,0x44,0x12,0x34,0x62,0x04,0x02,0x00,0x02},/*"深",0*/
    {0x88,0x20,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xBF,0x24,0x88,0x24,0x88,0x24,
    0x88,0x24,0x88,0x24,0x88,0x24,0xB8,0x24,0x87,0x24,0x42,0x24,0x40,0x20,0x20,0x20},/*"圳",1*/
{0x00,0x00,0xE4,0x3F,0x28,0x20,0x28,0x25,0x81,0x08,0x42,0x10,0x02,0x02,0x08,0x02,0xE8,0x3F,0x04,0x02,0x07,0x07,0x84,0x0A,0x44,0x12,0x34,0x62,0x04,0x02,0x00,0x02}//"深",0
,{0x88,0x20,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xBF,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xB8,0x24,0x87,0x24,0x42,0x24,0x40,0x20,0x20,0x20}//"圳",1



};



void  IO_init(void )
{
    pinMode(0,OUTPUT);//设置数字脚为输出
    pinMode(1,OUTPUT);//设置数字脚为输出
    pinMode(12,OUTPUT);//设置数字脚为输出
    pinMode(18,OUTPUT);//设置数字脚为输出
    pinMode(19,OUTPUT);//设置数字脚为输出
    pinMode(8,OUTPUT);//设置数字脚为输出
}

void delay_us(unsigned int _us_time)
{       
  unsigned char x=0;
  for(;_us_time>0;_us_time--)
  {
    x++;
  }
}

/*************SPI配置函数*******************
SCL空闲时低电平，第一个上升沿采样
模拟SPI
******************************************/

/**************************SPI模块发送函数************************************************

 *************************************************************************/
void SPI_SendByte(unsigned  char byte)        //向液晶屏写一个8位数据
{
  
  unsigned char counter;
  SPI_CS_0;
   
  for(counter=0;counter<8;counter++)
  { 
    SPI_SCK_0;    
    if((byte&0x80)==0)
    {
      SPI_SDA_0;
    }
    else SPI_SDA_1;
    byte=byte<<1; 
    SPI_SCK_1;      
  }
  
  SPI_SCK_0;
}

void TFT_SEND_CMD(unsigned char o_command)
{
    SPI_DC_0;
    SPI_CS_0;
    SPI_SendByte(o_command);
    SPI_CS_1;

    //SPI_DC_1;
}
//向液晶屏写一个8位数据
void TFT_SEND_DATA(unsigned  char o_data)
{ 
    SPI_DC_1;
    SPI_CS_0;
    SPI_SendByte(o_data);
    SPI_CS_1;

}
void TFT_clear(void)
{
    unsigned int ROW,column;
    TFT_SEND_CMD(0x2a);     //Column address set
    TFT_SEND_DATA(0x00);    //start column
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x00);    //end column
    TFT_SEND_DATA(0xF0);

    TFT_SEND_CMD(0x2b);     //Row address set
    TFT_SEND_DATA(0x00);    //start row
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x01);    //end row
    TFT_SEND_DATA(0x40);
    TFT_SEND_CMD(0x2C);     //Memory write
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
    { 

        for(column=0;column<TFT_COLUMN_NUMBER;column++)  //column loop
        {
            
            TFT_SEND_DATA(0xFF);
            TFT_SEND_DATA(0xFF);
        }
    }
}
void TFT_full(unsigned int color)
{
    unsigned int ROW,column;
    TFT_SEND_CMD(0x2a);     //Column address set
    TFT_SEND_DATA(0x00);    //start column
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x00);    //end column
    TFT_SEND_DATA(0xF0);

    TFT_SEND_CMD(0x2b);     //Row address set
    TFT_SEND_DATA(0x00);    //start row
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x01);    //end row
    TFT_SEND_DATA(0x40);
    TFT_SEND_CMD(0x2C);     //Memory write
    for(ROW=0;ROW<TFT_LINE_NUMBER;ROW++)             //ROW loop
    { 
    
        for(column=0;column<TFT_COLUMN_NUMBER ;column++) //column loop
        {

            TFT_SEND_DATA(color>>8);
            TFT_SEND_DATA(color);
        }
    }
}
void TFT_init(void)        
{
    SPI_RST_0;
    delay(10);
    SPI_RST_1;
    delay    (120);
    //-----------------------ST7789V Frame rate setting-----------------//

    TFT_SEND_CMD(0x3A);        //65k mode
    TFT_SEND_DATA(0x05);
    TFT_SEND_CMD(0xC5);     //VCOM
    TFT_SEND_DATA(0x1A);
    TFT_SEND_CMD(0x36);                 // 屏幕显示方向设置
    TFT_SEND_DATA(0x00);
    //-------------ST7789V Frame rate setting-----------//
    TFT_SEND_CMD(0xb2);   //Porch Setting
    TFT_SEND_DATA(0x05);
    TFT_SEND_DATA(0x05);
    TFT_SEND_DATA(0x00);
    TFT_SEND_DATA(0x33);
    TFT_SEND_DATA(0x33);

    TFT_SEND_CMD(0xb7);     //Gate Control
    TFT_SEND_DATA(0x05);      //12.2v   -10.43v
    //--------------ST7789V Power setting---------------//
    TFT_SEND_CMD(0xBB);//VCOM
    TFT_SEND_DATA(0x3F);

    TFT_SEND_CMD(0xC0); //Power control
    TFT_SEND_DATA(0x2c);

    TFT_SEND_CMD(0xC2);   //VDV and VRH Command Enable
    TFT_SEND_DATA(0x01);

    TFT_SEND_CMD(0xC3);     //VRH Set
    TFT_SEND_DATA(0x0F);    //4.3+( vcom+vcom offset+vdv)

    TFT_SEND_CMD(0xC4);     //VDV Set
    TFT_SEND_DATA(0x20);        //0v

    TFT_SEND_CMD(0xC6);       //Frame Rate Control in Normal Mode
    TFT_SEND_DATA(0X01);      //111Hz

    TFT_SEND_CMD(0xd0);       //Power Control 1
    TFT_SEND_DATA(0xa4);
    TFT_SEND_DATA(0xa1);

    TFT_SEND_CMD(0xE8);       //Power Control 1
    TFT_SEND_DATA(0x03);

    TFT_SEND_CMD(0xE9);       //Equalize time control
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x08);
    //---------------ST7789V gamma setting-------------//
    TFT_SEND_CMD(0xE0); //Set Gamma
    TFT_SEND_DATA(0xD0);
    TFT_SEND_DATA(0x05);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x08);
    TFT_SEND_DATA(0x14);
    TFT_SEND_DATA(0x28);
    TFT_SEND_DATA(0x33);
    TFT_SEND_DATA(0x3F);
    TFT_SEND_DATA(0x07);
    TFT_SEND_DATA(0x13);
    TFT_SEND_DATA(0x14);
    TFT_SEND_DATA(0x28);
    TFT_SEND_DATA(0x30);

    TFT_SEND_CMD(0XE1); //Set Gamma
    TFT_SEND_DATA(0xD0);
    TFT_SEND_DATA(0x05);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x09);
    TFT_SEND_DATA(0x08);
    TFT_SEND_DATA(0x03);
    TFT_SEND_DATA(0x24);
    TFT_SEND_DATA(0x32);
    TFT_SEND_DATA(0x32);
    TFT_SEND_DATA(0x3B);
    TFT_SEND_DATA(0x14);
    TFT_SEND_DATA(0x13);
    TFT_SEND_DATA(0x28);
    TFT_SEND_DATA(0x2F);

    TFT_SEND_CMD(0x20);     //反显
    TFT_SEND_CMD(0x11); //Exit Sleep // 退出睡眠模式
    delay    (120); 
    TFT_SEND_CMD(0x29); //Display on // 开显示
}
void display_char16_16(unsigned int x,unsigned int y,unsigned long color,unsigned char word_serial_number)
{
    unsigned int column;
    unsigned char tm=0,temp=0,xxx=0;

    TFT_SEND_CMD(0x2a);    //Column address set
    TFT_SEND_DATA(x>>8);    //start column
    TFT_SEND_DATA(x);
    x=x+15;
    TFT_SEND_DATA(x>>8);    //end column
    TFT_SEND_DATA(x);

    TFT_SEND_CMD(0x2b);     //Row address set
    TFT_SEND_DATA(y>>8);    //start row
    TFT_SEND_DATA(y); 
    y=y+15;
    TFT_SEND_DATA(y>>8);    //end row
    TFT_SEND_DATA(y);
    TFT_SEND_CMD(0x2C);     //Memory write

    
        for(column=0;column<32;column++)  //column loop
        {
        temp=chines_word[  word_serial_number ][xxx];
            for(tm=0;tm<8;tm++)
            {
                if(temp&0x01)
                {
                    TFT_SEND_DATA(color>>8);
                    TFT_SEND_DATA(color);
                }
                else 
                {
                    TFT_SEND_DATA(0XFF);
                    TFT_SEND_DATA(0XFF);
                }
                temp>>=1;
            }
            xxx++;
        }
}

void Picture_Display(const unsigned char *ptr_pic)
{
    unsigned long  number;
    TFT_SEND_CMD(0x2a);     //Column address set
    TFT_SEND_DATA(0x00);    //start column
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x00);    //end column
    TFT_SEND_DATA(0x77);

    TFT_SEND_CMD(0x2b);     //Row address set
    TFT_SEND_DATA(0x00);    //start row
    TFT_SEND_DATA(0x00); 
    TFT_SEND_DATA(0x00);    //end row
    TFT_SEND_DATA(0x78);
    TFT_SEND_CMD(0x2C);     //Memory write

    for(number=0;number<PIC_NUM;number++) 
    {
//            data=*ptr_pic++;
//            data=~data;
            TFT_SEND_DATA(*ptr_pic++);
  
      
    }
}


// void  setup(){
// 	SPI_BLK_1;

// 	IO_init();
// 	SPI_CS_1;
// 	TFT_init();
// 	TFT_full(RED);
// 	delay(100);
// 	TFT_full(GREEN);
// 	delay(100);
// 	TFT_full(BLUE);
// 	delay(100);
// 	TFT_clear();
// }

// void  loop(){
 
// 	//Picture_Display(point);
// 	delay(1000);
// 	TFT_clear();


// 	delay(1000);
// }
