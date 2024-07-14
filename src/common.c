#include "common.h"

//---DS1302 写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b,
                               0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a,
                                0x8c};
//---DS1302 时钟初始化 2016 年 5 月 7 日星期六 12 点 00 分 00 秒。---//
//---存储顺序是秒分时日月周年,存储格式是用 BCD 码---//
xdata uchar TIME[7] = {0, 0, 0x12, 0x13, 0x07, 0x06, 0x24};

unsigned char BCD_to_uchar(uchar dat)
{
    return (dat >> 4) * 10 + (dat & 0x0f);
}

S_TIME *get_sys_time()
{
    return &colock;
}

unsigned long initTime(unsigned h, unsigned m, unsigned s)
{
    colock.hour = h;
    colock.min = m;
    colock.sec = s;
    colock.total = h * 60 + m * 60 + s;
    return colock.total;
}

unsigned long updateTime()
{
    xdata unsigned long time = 0;
    time = ++colock.total;
    colock.hour = time / (60 * 60);
    colock.min = (time / 60) % 60;
    colock.sec = time % 60;
    return time;
}

void delay_us(unsigned us)
{
    xdata unsigned i = 0;
    while (i < us)
    {
        i++;
        _nop_();
    }
}

void delay_ms(unsigned ms)
{
    xdata unsigned i = 0;
    while (i < ms)
    {
        i++;
        delay_us(65);
    }
}

void delay_s(unsigned s)
{
    xdata unsigned i = 0;
    while (i < s)
    {
        i++;
        delay_ms(1000);
    }
}

void Ds1302Write(uchar addr, uchar dat)
{
    uchar n;
    RST = 0;
    _nop_();
    SCLK = 0; // 先将 SCLK 置低电平

    _nop_();
    RST = 1; // 然后将 RST(CE)置高电平。
    _nop_();
    for (n = 0; n < 8; n++) // 开始传送八位地址命令
    {
        DSIO = addr & 0x01; // 数据从低位开始传送
        addr >>= 1;
        SCLK = 1; // 数据在上升沿时，DS1302 读取数据
        _nop_();
        SCLK = 0;
        _nop_();
    }
    for (n = 0; n < 8; n++) // 写入 8 位数据
    {
        DSIO = dat & 0x01;
        dat >>= 1;
        SCLK = 1; // 数据在上升沿时，DS1302 读取数据
        _nop_();
        SCLK = 0;
        _nop_();
    }
    RST = 0; // 传送数据结束
    _nop_();
}

uchar Ds1302Read(uchar addr)
{
    uchar n, dat, dat1;
    RST = 0;
    _nop_();
    SCLK = 0; // 先将 SCLK 置低电平。
    _nop_();
    RST = 1; // 然后将 RST(CE)置高电平。
    _nop_();
    for (n = 0; n < 8; n++) // 开始传送八位地址命令
    {
        DSIO = addr & 0x01; // 数据从低位开始传送
        addr >>= 1;
        SCLK = 1; // 数据在上升沿时，DS1302 读取数据
        _nop_();
        SCLK = 0; // DS1302 下降沿时，放置数据
        _nop_();
    }
    _nop_();
    for (n = 0; n < 8; n++) // 读取 8 位数据
    {
        dat1 = DSIO; // 从最低位开始接收
        dat = (dat >> 1) | (dat1 << 7);
        SCLK = 1;
        _nop_();
        SCLK = 0; // DS1302 下降沿时，放置数据
        _nop_();
    }
    RST = 0;
    _nop_(); // 以下为 DS1302 复位的稳定时间,必须的。
    SCLK = 1;
    _nop_();
    DSIO = 0;
    _nop_();
    DSIO = 1;
    _nop_();
    return dat;
}

void Ds1302Init()
{
    uchar n;
    Ds1302Write(0x8E, 0X00); // 禁止写保护，就是关闭写保护功能
    for (n = 0; n < 7; n++)  // 写入 7 个字节的时钟信号：分秒时日月周年
    {
        Ds1302Write(WRITE_RTC_ADDR[n], TIME[n]);
    }
    Ds1302Write(0x8E, 0x80); // 打开写保护功能
}

void Ds1302ReadTime()
{
    uchar n;
    for (n = 0; n < 7; n++) // 读取 7 个字节的时钟信号：分秒时日月周年
    {
        TIME[n] = Ds1302Read(READ_RTC_ADDR[n]);
    }
    colock.year  = BCD_to_uchar(TIME[6]);
    colock.week  = BCD_to_uchar(TIME[5]);
    colock.month = BCD_to_uchar(TIME[4]);
    colock.day   = BCD_to_uchar(TIME[3]);
    colock.hour  = BCD_to_uchar(TIME[2]);
    colock.min   = BCD_to_uchar(TIME[1]);
    colock.sec   = BCD_to_uchar(TIME[0]);
}