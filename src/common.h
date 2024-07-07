#ifndef __COMMON_H__
#define __COMMON_H__
#include "intrins.h"
static unsigned int g_time_count = 0;

/*******************系统时间*****************/
typedef struct _S_TIME{
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned long total; 
}S_TIME;

static S_TIME colock = {0, 0, 0, 0};
S_TIME* get_sys_time();
unsigned long initTime(unsigned h, unsigned m, unsigned s);
unsigned long updateTime();
/*延时函数*/ 
void delay_us(unsigned us);
void delay_ms(unsigned ms);
void delay_s(unsigned s);
#endif