#include "REG52.H"
#include "io.h"
#include "stdio.h"

sbit led=P2^0;
unsigned char num;

void uart_config()
{
    SCON = 0x50;
    TMOD |= 0x20;
    TMOD &= ~0x10;
    TH1 = 0xFA;
    TL1 = 0xFA;
    PCON |= 0x80;
    TR1 = 1;
    TI = 0;
    RI = 0;
    ES = 1;
}

void sendStr(char* str)
{
    ES = 0;
    while(*str != 0)
    {
        SBUF = *str;
        while(TI==0);
        TI=0;
        str++;
    }
    ES=1;
}

void sleep(unsigned ms)
{
    int i = 0;
    while(i < ms*1000)
    {
        i++;
    }
}


void main()
{
    char buf[16] = {0};
    uart_config();
    while(1)
    {
        GPIO2_0=~GPIO2_0;
        sprintf(buf,"%x", P2);
        sendStr(buf);
        sleep(10);
    }
    /*
    TMOD=0x01; //设置定时器0为工作方式1
    TH0=(65536-45872)/256;
    TL0=(65536-45872)%256; //装初值
    EA=1;//开总中断
    ET0=1;//开启定时器0中断
    TR0=1;//启动定时器0

    while(1);//程序在这里等待中断发生
    */
}

void T0_time() interrupt 1
{
    TH0=(65536-45872)/256;
    TL0=(65536-45872)%256; //进入中断程序说明计数计满，TL0，TH0归零，需要装初值
    num++;
    if(num==20)  //每计够20次可以进入一次if语句，改变一次LED灯的状态
    {          //进入一次需要50ms，进入20次就经历了1s
        num=0;
        led=~led;
    }
}