#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "stdio.h"
#include "stdlib.h"
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

#endif //__INTERRUPT_H__