#include "common.h"

unsigned long initTime(unsigned h, unsigned m, unsigned s)
{
    colock.hour = h;
    colock.min = m;
    colock.sec = s;
    colock.total = h * 60+ m * 60 + s;
    return colock.total;
}

unsigned long updateTime()
{
    unsigned long time = colock.total;
    colock.hour = time / (60 * 60);
    colock.min = (time / 60) % 60;
    colock.sec = time % 60;
    return time;
}

void sleep(unsigned ms)
{
    unsigned i = 0;
    while(i < 1000*ms)
    {
        _nop_();
        i++;
    }
}