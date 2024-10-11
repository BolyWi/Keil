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

static unsigned s_timer_count = 0;
static bit s_timer_bLoop = 0;
static timer_callback s_timer_cb = NULL;
static void* s_timer_param = NULL;

void register_timer(unsigned ticks, bit bLoop, timer_callback timer_cb, void* timer_param)
{
    unsigned value = OS_TIMER0_INIT_VALUE;
    
    s_timer_count = ticks;
    s_timer_bLoop = bLoop;
    s_timer_cb = timer_cb;
    s_timer_param = timer_param;

    TMOD = 0x01;
    TH0 = value >> 8;
    TL0 = value & 0xFF;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void remove_timer()
{
    EA = 0;
    ET0 = 0;
    TR0 = 0;
}

void timer0_interrupt() interrupt 1 using 1
{
    static unsigned count = 0;
    unsigned value = OS_TIMER0_INIT_VALUE;
    
    TH0 = value >> 8;
    TL0 = value & 0xFF;
    count++;

    if(count >= s_timer_count)
    {
        count = 0;
        if(s_timer_cb != NULL)
        {
            s_timer_cb(s_timer_param);
        }
        if(!s_timer_bLoop)
        {
            EA = 0;
            ET0 = 0;
            TR0 = 0;
        }
    }
}