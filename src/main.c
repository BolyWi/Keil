#include "REG52.H"
#include "./include/io.h"
#include "stdio.h"
#include "stdlib.h"
#include "./interrupt/interrupt.h"
#define USE_SCOMM_LOG
#include "scomm/scomm.h"

// 引脚定义
sbit led=P2^0;

void ledTurnOn(void* param)
{
    if(param)
    {
        ;
    }
    led = ~led;
}

//主程序入口
void main()
{
	T0_timerInit(ledTurnOn);
    while(1)
    {
        ;
    }
}