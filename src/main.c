#include "include/inc52.h"

//主程序入口
void main()
{

	T0_timerInit(500, ledTurnOn, NULL);
    LED = 0;
}