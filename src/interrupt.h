#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "stdio.h"
#include "stdlib.h"
// �жϻص�����
typedef void (*intCallback)(void*);

typedef void (*function)(void);

// �жϺ��������ṹ
typedef struct _intFunParam{
	unsigned interval;
	void* param;
}intFunParam;

// �жϼ���
unsigned char g_count = 0;
// �жϺ���ָ��
intCallback g_inerrupt_func = NULL;
intFunParam g_intFunParam = { 0, NULL };

// �ж�ִ�к���
void ledTurnOn(void* param);

// �жϳ�ʼ��
void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData);

#endif //__INTERRUPT_H__