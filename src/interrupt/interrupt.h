#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "REG52.H"
#include "stdio.h"
#include "stdlib.h"

// 中断间隔 2*10*50ms = 1s
#define INTERRUPT_INTERVAL 2*10  // 1s
// 中断函数参数结构
typedef struct _intFunParam{
	int id;
	char name[16];
	void* func;
}intFunParam;

// 中断回调函数
typedef void (*intCallback)(void*);


// 全局中断变量
extern intCallback g_inerrupt_func;
extern intFunParam* g_intFunParam;

// 中断计数
extern unsigned g_count;
// 中断初始化
void T0_timerInit(intCallback timerOp);
#endif //__INTERRUPT_H__