#include "gpio.h"
#include "stdio.h"
#include "stdlib.h"
#include "intrins.h"
#include "string.h"
typedef int fun(int);

void setLed(int index)
{
    LED=~LED;
}

int regTimer(void* callback)
{
    int count = 0;
    fun *op = callback;
    TMOD = 0x01;
    TH0 = 0xB8;
    TL0 = 0x00;
    TR0 = 0x01;

    while(1)
    {
        if(TF0 == 1)
        {
            TF0 = 0;
            TH0 = 0xB8;
            count++;
            if(count == 50)
            {
                count = 0;
                op(0);
            }
        }
    }
}

sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;


void DELAY_nMS(unsigned int time)
{
    unsigned i = 0;
    while (i < time * 1000)
    {
        _nop_();
        i++;
    }
}

void wcode(unsigned char t)
{
  LCD_RS=0;           // 写的是命令
  LCD_RW=0;           // 写状态
  LCD_EN=1;           // 使能
  P0=t;               // 写入命令 
  DELAY_nMS(2);       // 等待写入,如果时间太短，会导致液晶无法显示
  LCD_EN=0;           // 数据的锁定
}

//向LCD写一数据
void wdata(unsigned char t)
{
  LCD_RS=1;             // 写的是数据
  LCD_RW=0;             // 写状态
  LCD_EN=1;             // 使能
  P0=t;                 // 写入数据
  DELAY_nMS(2);         // 等待写入,如果时间太短，会导致液晶无法显示
  LCD_EN=0;             // 数据的锁定
}

//LCD设置坐标位置
void LCD1602_SetArea(unsigned char X,unsigned char Y)
{
    if (X > 16 && Y < 1)
    {
        X = 0;Y = 1;
    }
    if(Y > 1)
        Y = 0;
    if(X >= 16 && Y > 1)
    {
        X =0; Y = 0;
    }
    switch(Y)
    {
        case 0: wcode(0x80 + X); break;
        case 1: wcode(0xC0 + X); break;
        default:break;
    }
}

//LCD显示字符
void LCD1602_ShowChar(unsigned char X,unsigned char Y,unsigned char Char)
{
    LCD1602_SetArea(X,Y);                           // 设置显示坐标
    wdata(Char);                        // 显示指定字符
}

//LCD显示字符串
void LCD1602_ShowString(unsigned char X,unsigned char Y,unsigned char *String)
{
    LCD1602_SetArea(X,Y);                           // 设置显示坐标
    while(*String)
    {
        wdata(*String);
        String++;
    }
}

//LCD初始化
void InitLCD()
{  		 
   wcode(0x01);	  //清屏
   wcode(0x06);   //输入方式控制,增量光标不移位
   wcode(0x0e);   //显示开关控制
   wcode(0x38);   //功能设定:设置16x2显示，5x7显示,8位数据接口     	
}

void displayMain()
{
    int i = 0;
    int x = 0, y =0;
    char* temp = "Hello world!";
    int len = strlen(temp);
    InitLCD();
    while(i < len)
    {
        LCD1602_ShowChar(x, y, temp[i]);
        i++;
        x++;
    }
}

//主程序入口
void main()
{
	int i = 0, j = 0;;
	//displayMain();
	while(1)
	{
		LED = 0x03;
	}
    while(1);
}