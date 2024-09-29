#include "common.h"

// delay function define

void delay_us(unsigned us)
{
    while(us!=0)
    {
        us--;
    }
}

void delay_10us()
{
    _nop_();_nop_();
    _nop_();_nop_();_nop_();
}

void delay_ms(unsigned ms)
{
    while(ms!=0)
    {
        delay_us(112);
        ms--;
    }
}

void delay_sec(unsigned sec)
{
    while(sec!=0)
    {
        delay_ms(1000);
        sec--;
    }
}