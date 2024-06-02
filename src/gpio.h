#ifndef __GPIO_H__
#define __GPIO_H__
#include "REG52.H"

/************IO引脚定义*****************/
sfr GPIO_0 = 0x80;
sfr GPIO_1 = 0x90;
sfr GPIO_2 = 0xA0;
sfr GPIO_3 = 0xB0;

/*******LED灯控制位定义*****************/
sbit LED_0 = P2^0;
sbit LED_1 = P2^1;
sbit LED_2 = P2^2;
sbit LED_3 = P2^3;
sbit LED_4 = P2^4;
sbit LED_5 = P2^5;
sbit LED_6 = P2^6;
sbit LED_7 = P2^7;

sfr LED = 0xA0;

#endif // __GPIO_H__