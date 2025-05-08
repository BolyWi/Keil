#include "common.h"
#include "uart.h"

#if ENABLE_UART_MOUDLE
// uart receive buf
static char recv_buf[128] = { 0 };

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
    EA = 1;
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

void uart_recv() interrupt 4
{
    int len = 0;
    int total_len = sizeof(recv_buf);
    len = strlen(recv_buf) % total_len;
    if(RI == 1)
    {
        if(len == 0)
            memset(recv_buf, 0, total_len);
        recv_buf[len] = SBUF;
        len++;
        RI = 0;
    }
}

int get_uart_info(char* buf, int buf_len)
{
    int len = strlen(recv_buf);
    if(recv_buf !=NULL && strlen(recv_buf) > 0)
    {
        if(buf_len <= len)
            len = buf_len;
        strncpy(buf, recv_buf, len);
        memset(recv_buf, 0, sizeof(recv_buf));
        return OK;
    }
    return ERROR;
}
#endif