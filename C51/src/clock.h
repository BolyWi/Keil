#ifndef __COLOK_H__
#define __CLOCK_H__
#include <intrins.h>
#include <stdio.h>

//#define unsigned char uchar;
/*******************系统时间*****************/
typedef struct _S_TIME{
    uchar sec;
    uchar min;
    uchar hour;
    uchar day;
    uchar month;
    uchar week;
    uchar year;
}S_TIME;

static void Ds1302Init();
static void Ds1302ReadTime();
void clock_init();
void get_time_string(char* date, char* time);
#endif // __CLOCK_H__