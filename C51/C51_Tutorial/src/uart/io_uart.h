#if !defined(__IO_UART_H__)
#define __IO_UART_H__
#include <reg52.h>

void ConfigUART(unsigned int baud);
void StartTXD(unsigned char dat);
void StartRXD();

void SendDemo();

#endif // __IO_UART_H__
