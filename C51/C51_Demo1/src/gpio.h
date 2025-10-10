#ifndef __GPIO_H__
#define __GPIO_H__
#include <REG52.H>

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

/**********DS1302 IO定义************/
sbit DSIO = P3^4;
sbit RST  = P3^5;
sbit SCLK = P3^6;

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;


/**********LCD1602 IO定义*************/
sbit LCD_RS = P2^6;
sbit LCD_RW = P2^5;
sbit LCD_EN = P2^7;
sfr  LCD_DATA = 0x80;

/************EEPROM读写 IO定义********/
sfr IAP_DATA = 0xE2;
sfr IAP_ADDRH = 0xE3;
sfr IAP_ADDRL = 0xE4;
sfr IAP_CMD = 0xE5;
sfr IAP_TRIG = 0xE6;
sfr IAP_CONTR = 0xE7;

/***************蜂鸣器 IO定义*********/
sbit BEEP = P1^5;

/***************DS18B20 IO定义*********/
sbit DSPORT = P3^7;

/********DHT11 IO定义******************/
sbit DHT11 = P1^0;

/**************按键IO定义*************/
sbit KEY_1 = P3^1;
sbit KEY_2 = P3^2;
sbit KEY_3 = P3^3;
sbit KEY_4 = P3^4;

/***********TFT st7735s spi IO定义*****/
sbit TFT_SCL = P1^0;
sbit TFT_SDA = P1^1;
sbit TFT_RST = P1^2;
sbit TFT_DC  = P1^3;
sbit TFT_CS  = P1^4;
sbit TFT_BK  = P1^5;
sbit TFT_K4  = P1^6;

sbit TOUCH_KEY = P1^7;
#endif // __GPIO_H__