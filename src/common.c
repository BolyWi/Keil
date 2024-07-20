#include "common.h"

void delay_us(unsigned us)
{
    unsigned i = 0;
    while (i < us)
    {
        i++;
        _nop_();
    }
}

void delay_ms(unsigned ms)
{
    unsigned i = 0;
    while (i < ms)
    {
        i++;
        delay_us(65);
    }
}