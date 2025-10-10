#include "common.h"
#include "interrupt.h"

#if ENABLE_INTERRUPY_MOUDLE
// �жϼ���
unsigned char g_count = 0;
// �жϺ���ָ��
intCallback g_inerrupt_func = NULL;
intFunParam g_intFunParam = { 0, NULL };

void T0_timerInit(unsigned interval, intCallback timerCallBack, void* callBackData)
{
	TMOD = 0x01;              //���ö�ʱ��0Ϊ������ʽ1
    TH0  = (65536-45872)/256;
    TL0  = (65536-45872)%256; //װ��ֵ
    EA   = 1;                 //�����ж�
    ET0  = 1;                 //������ʱ��0�ж�
    TR0  = 1;                 //������ʱ��0
	g_intFunParam.interval = interval;
	g_intFunParam.param = callBackData;
	g_inerrupt_func = timerCallBack;
}

// T0�ж�
void T0_time() interrupt 1
{
	// 50ms ����һ��
	EA = 0;
    TH0 = (65536-45872)/256;
    TL0 = (65536-45872)%256; //�����жϳ���˵������������TL0��TH0���㣬��Ҫװ��ֵ
	g_count++;
	// ��С50msΪ��λ
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
    LED = ~LED;
}
#endif