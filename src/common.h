#ifndef __COMMON_H__
#define __COMMON_H__
#include "intrins.h"
static unsigned int g_time_count = 0;

/*******************系统时间*****************/
typedef struct _TIME{
    unsigned char hour;
    unsigned char min;
    unsigned char sec;
    unsigned long total; 
}Time;

static Time colock = {0, 0, 0, 0};

unsigned long initTime(unsigned h, unsigned m, unsigned s);
unsigned long updateTime();
/*延时函数*/ 
void sleep(unsigned ms);
#endif