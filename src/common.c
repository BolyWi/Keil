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

#if ENABLE_RTXOS_MOUDLE
void delay_ms(unsigned ms)
{
    os_wait(K_IVL, ms, 0);
}
#else
void delay_ms(unsigned ms)
{
    unsigned i = 0;
    while (i < ms)
    {
        i++;
        delay_us(65);
    }
}
#endif