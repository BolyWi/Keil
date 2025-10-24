#include "io_uart.h"
// 通过IO模拟串口收发数据
sbit PIN_RXD = P3 ^ 0;
sbit PIN_TXD = P3 ^ 1;

bit RxdOrTxd = 0;
bit RxdEnd = 0;
bit TxdEnd = 0;
unsigned char RxdBuf = 0;
unsigned char TxdBuf = 0;

void ConfigUART(unsigned int baud)
{
    TMOD &= 0xf0;
    TMOD |= 0x02;
    TH0 = 256 - (11059200 / 12) / baud;
}

void StartTXD(unsigned char dat)
{
    TxdBuf = dat;
    TL0 = TH0;
    ET0 = 1;
    TR0 = 1;
    PIN_TXD = 0;  // 发送起始位
    TxdEnd = 0;   // 清零发送结束标志
    RxdOrTxd = 1; // 设置当前状态为发送
}

void StartRXD()
{
    TL0 = 256 - ((256 - TH0) >> 1);
    ET0 = 1;
    TR0 = 1;
    RxdEnd = 0;
    RxdOrTxd = 0;
}

void SendDemo()
{
    while (PIN_RXD)
        ; // 等待接收端低电平 起始位
    StartRXD();
    while (!RxdEnd)
        ; // 等待接受完成 停止位
    StartTXD(RxdBuf + 1);
    while (!TxdEnd)
        ; // 等待发送完成
}

void InterruptTimer0() interrupt 1
{
    static unsigned char cnt = 0;
    if (RxdOrTxd) // 串行发送处理
    {
        cnt++;
        if (cnt <= 8) // 低位在先依次发送8bit数据位
        {
            PIN_TXD = TxdBuf & 0x01;
            TxdBuf >>= 1;
        }
        else if (cnt == 9) // 发送停止位
        {
            PIN_TXD = 1;
        }
        else // 发送结束
        {
            cnt = 0;
            TR0 = 0;
            TxdEnd = 1;
        }
    }
    else // 串行接收数据
    {
        if (cnt == 0) // 处理起始位
        {
            if (!PIN_RXD) // 起始位为0时，清零接收位缓冲器，准备接收数据位
            {
                RxdBuf = 0;
                cnt++;
            }
            else // 起始位不为0时 终止接收
            {
                TR0 = 0;
            }
        }
        else if (cnt <= 8) // 处理8bit数据位
        {
            RxdBuf >>= 1; // 低位在先 所以将之前接收的位向右移
            if (PIN_RXD)  // 接收脚为1时 缓冲器最高最高位置1
            {             // 而为0时不处理即保持位移后的0
                RxdBuf |= 0x80;
            }
            cnt++;
        }
        else
        {
            cnt = 0;
            TR0 = 0;
            if (PIN_RXD) // 停止位为1时，方能认为数据有效
            {
                RxdEnd = 1;
            }
        }
    }
}