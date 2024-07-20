#include "common.h"
#include "temperature.h"

void Delay1ms(unsigned y)
{
    unsigned x;
    for(y;y>0;y--)
        for(x=110; x > 0; x--);
}

uchar Ds18b20Init()
{
    uchar i = 0;
    DSPORT = 0;
    i = 70;
    while(i--);
    DSPORT = 1;
    i = 0;
    while(DSPORT)
    {
        i++;
        if(i > 5000)
            return 0;
    }
    return 1;
}

void Ds18b20WriteByte(uchar com)
{
    uchar i, j;
    for(j =0; j < 8; j++)
    {
        DSPORT = 0;
        i++;
        DSPORT = com & 0x01;
        i = 6;
        while(i--);
        DSPORT = 1;
        com >>= 1;
    }
}

uchar Ds18b20ReadByte()
{
    uchar i, j, byte_t, bit_t;
    for(j = 8; j >0; j--)
    {
        DSPORT = 0;
        i++;
        DSPORT = 1;
        i++;i++;
        bit_t = DSPORT;
        byte_t = (byte_t >> 1) | (bit_t << 7);
        i = 4;
        while(i--);
    }
    return byte_t;
}

void Ds18b20ChangTemp()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);
    Ds18b20WriteByte(0x44);
}

void  Ds18b20ReadTempCom()
{
    Ds18b20Init();
    Delay1ms(1);
    Ds18b20WriteByte(0xcc);
    Ds18b20WriteByte(0xbe);
}

int Ds18b20ReadTemp()
{
    int temp = 0;
    uchar tmh, tml;
    Ds18b20ChangTemp();
    Ds18b20ReadTempCom();
    tml = Ds18b20ReadByte();
    tmh = Ds18b20ReadByte();
    temp = tmh;
    temp <<=8;
    temp |=tml;

    return temp;
}

float get_temperature()
{
    float temp = 0.00;
    temp = Ds18b20ReadTemp()*0.0625;
    return temp;
}
