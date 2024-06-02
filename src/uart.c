#include "uart.h"
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

void uart_send(unsigned char buf)
{
    SBUF = buf;
    while(!TI);
    TI = 0;
}

char putchar(char c)
{
    ES = 0;
    SBUF = c;
    while(TI==0);
    TI = 0;
    ES = 1;
    return c;
}
