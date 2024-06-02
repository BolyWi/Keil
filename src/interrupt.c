#include "interrupt.h"
#include "gpio.h"

void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData)
{
	TMOD = 0x01;              //设置定时器0为工作方式1
    TH0  = (65536-45872)/256;
    TL0  = (65536-45872)%256; //装初值
    EA   = 1;                 //开总中断
    ET0  = 1;                 //开启定时器0中断
    TR0  = 1;                 //启动定时器0
	g_intFunParam.interval = interval;
	g_intFunParam.param = callBackData;
	g_inerrupt_func = timerCallBack;
}

// T0中断
#if 0
void T0_time() interrupt 1
{
	// 50ms 进入一次
	EA = 0;
    TH0 = (65536-45872)/256;
    TL0 = (65536-45872)%256; //进入中断程序说明计数计满，TL0，TH0归零，需要装初值
	g_count++;
	// 最小50ms为单位
	if( (g_count*50 >= g_intFunParam.interval) && g_inerrupt_func )
	{
		g_count = 0;
		g_inerrupt_func(g_intFunParam.param);
	}
	EA = 1;
}
#endif

void ledTurnOn(void* param)
{
    if(param)
    {
       ((function)param)();
    }
    LED = ~LED;
}