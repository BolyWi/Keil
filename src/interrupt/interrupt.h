#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "REG52.H"
#include "stdio.h"
#include "stdlib.h"

// 中断函数参数结构
typedef struct _intFunParam{
	unsigned interval;
	void* param;
}intFunParam;

// 中断回调函数
typedef void (*intCallback)(void*);


// 全局中断变量
//extern intCallback g_inerrupt_func;
//extern intFunParam g_intFunParam;

// 中断计数
extern unsigned char g_count;
// 中断初始化
void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData);
#endif //__INTERRUPT_H__