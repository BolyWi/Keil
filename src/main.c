#include "reg51.h"
#include "stdio.h"
#include "stdlib.h"
#include "intrins.h" 
/************引脚定义*****************/
sfr GPIO_0 = 0x80;
sfr GPIO_1 = 0x90;
sfr GPIO_2 = 0xA0;
sfr GPIO_3 = 0xB0;

/************中断实验*****************/
#if 0
// 中断回调函数
typedef void (*intCallback)(void*);

typedef void (*function)(void);

// 中断函数参数结构
typedef struct _intFunParam{
	unsigned interval;
	void* param;
}intFunParam;

// 中断计数
unsigned char g_count = 0;
// 中断函数指针
intCallback g_inerrupt_func = NULL;
intFunParam g_intFunParam = { 0, NULL };

// 中断执行函数
void ledTurnOn(void* param);

// 中断初始化
void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData);

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

void ledTurnOn(void* param)
{
    if(param)
    {
       ((function)param)();
    }
    led = ~led;
}
/************中断实验END****************/
#endif
/*************串口收发实验*************************/
#if 0
static unsigned int g_time_count = 0; 
// 初始化串口
void uart_config()
{
    SCON = 0x50;
    TMOD |= 0x21;
    TMOD &= ~0x10;
    TH1 = 0xFA;
    TL1 = 0xFA;
    PCON |= 0x80;
    TR1 = 1;
    TI = 0;
    RI = 0;
    ES = 1;
}

// 串口发送数据
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

// 定时发送数据

void sendDataOp()
{
	int i = 0;
	char buf[64] = {0};
	uart_config();
	while(1)
	{
		i = 0;
		while(i < 10000)
		{
			i++;
		}
		g_time_count++;
		sprintf(buf, "This is No. %u", g_time_count);
		sendStr(buf);
	}
}
#endif
/*************************************/

/*延时函数*/ 
void sleep(unsigned ms)
{
    unsigned i = 0;
    while(i < 1000*ms)
    {
        _nop_();
        i++;
    }
}


//主程序入口
void main()
{
	// T0_timerInit(500, ledTurnOn, NULL);
	// sendDataOp();
    while(1)
    {
        sleep(500);
    }
}