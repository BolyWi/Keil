#include "interrupt.h"

unsigned g_count = 0;
intCallback g_inerrupt_func = NULL;
intFunParam* g_intFunParam = NULL;

void T0_timerInit(intCallback timerOp)
{
	TMOD = 0x01;              //设置定时器0为工作方式1
    TH0  = (65536-45872)/256;
    TL0  = (65536-45872)%256; //装初值
    EA   = 1;                 //开总中断
    ET0  = 1;                 //开启定时器0中断
    TR0  = 1;                 //启动定时器0
    g_intFunParam = (intFunParam*)malloc(sizeof(intFunParam));
    g_intFunParam->id = 1;
    sprintf(g_intFunParam->name, "%s", "timerId");
	g_inerrupt_func = timerOp;
}


// T0中断
void T0_time() interrupt 1
{
	// 50ms 进入一次
	EA = 0;
    TH0 = (65536-45872)/256;
    TL0 = (65536-45872)%256; //进入中断程序说明计数计满，TL0，TH0归零，需要装初值
	g_count++;
	if(g_count == INTERRUPT_INTERVAL && g_inerrupt_func)
	{
		g_count = 0;
		g_inerrupt_func(g_intFunParam);
	}
	EA = 1;
}