#include "common.h"

S_TIME* get_sys_time()
{
	return &colock;
}

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
    unsigned long time = 0;
	time = ++colock.total;
    colock.hour = time / (60 * 60);
    colock.min = (time / 60) % 60;
    colock.sec = time % 60;
    return time;
}

void delay_us(unsigned us)
{
	unsigned i = 0;
	while(i < us)
	{
		i++;
		_nop_();
	}
}

void delay_ms(unsigned ms)
{
    unsigned i = 0;
    while(i < ms)
    {
        i++;
        delay_us(65);
    }
}

void delay_s(unsigned s)
{
    unsigned i = 0;
    while(i < s)
    {        
		i++;
        delay_ms(1000);
    }
}