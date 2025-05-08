#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include <stdio.h>
#include <stdlib.h>
// �жϻص�����
typedef void (*intCallback)(void*);

typedef void (*function)(void);

// �жϺ��������ṹ
typedef struct _intFunParam{
	unsigned interval;
	void* param;
}intFunParam;

// �ж�ִ�к���
void ledTurnOn(void* param);

// �жϳ�ʼ��
void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData);

#endif //__INTERRUPT_H__