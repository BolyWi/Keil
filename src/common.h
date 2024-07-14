#ifndef __COMMON_H__
#define __COMMON_H__
#include <intrins.h>
#include <stdio.h>
#include "gpio.h"

static xdata unsigned int g_time_count = 0;
typedef unsigned char uchar;
/*******************系统时间*****************/
typedef struct _S_TIME{
    unsigned char year;
    unsigned char month;
    unsigned char day;
    unsigned char week;
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned long total; 
}S_TIME;

static xdata S_TIME colock = {0, 0, 0, 0};
S_TIME* get_sys_time();
unsigned long initTime(unsigned h, unsigned m, unsigned s);
unsigned long updateTime();

void Ds1302Init();
void Ds1302ReadTime();

/*延时函数*/ 
void delay_us(unsigned us);
void delay_ms(unsigned ms);
void delay_s(unsigned s);
#endif