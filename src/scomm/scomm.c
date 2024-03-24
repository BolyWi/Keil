#include "scomm.h"
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