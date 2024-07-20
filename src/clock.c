#include "common.h"
#include "clock.h"

#if ENABLE_CLOCK_MOUDLE
//---初始化系统时间 2024.07.20 周六 12:00:00
#define INIT_TIME_YEAR      24
#define INIT_TIME_MONTH     7
#define INIT_TIME_DAY       20
#define INIT_TIME_WEEK      6
#define INIT_TIME_HOUR      12
#define INIT_TIME_MINUTE    0
#define INIT_TIME_SECOND    0

//---DS1302 写入和读取时分秒的地址命令---//
//---秒分时日月周年 最低位读写位;-------//
uchar code READ_RTC_ADDR[7] = {0x81, 0x83, 0x85, 0x87, 0x89, 0x8b,
                               0x8d};
uchar code WRITE_RTC_ADDR[7] = {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a,
                                0x8c};
S_TIME code INIT_SYSTEM_TIME = { INIT_TIME_SECOND, INIT_TIME_MINUTE, INIT_TIME_HOUR, INIT_TIME_DAY, INIT_TIME_MONTH, INIT_TIME_WEEK, INIT_TIME_YEAR };

static S_TIME s_clock;

uchar BCD_to_uchar(uchar dat)
{
    return (dat >> 4) * 10 + (dat & 0x0f);
}

uchar uchar_to_BCD(uchar dat)
{
    return dat / 10 << 4 | dat % 10;
}

static void Ds1302Write(uchar addr, uchar dat)
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

static uchar Ds1302Read(uchar addr)
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

static void Ds1302Init()
{
    uchar n;
    uchar temp[7] = { 0 };
    memcpy(temp, &INIT_SYSTEM_TIME, sizeof(INIT_SYSTEM_TIME));
    Ds1302Write(0x8E, 0X00); // 禁止写保护，就是关闭写保护功能
    for (n = 0; n < 7; n++)  // 写入 7 个字节的时钟信号：分秒时日月周年
    {
        Ds1302Write(WRITE_RTC_ADDR[n], uchar_to_BCD(temp[n]));
    }
    Ds1302Write(0x8E, 0x80); // 打开写保护功能
}

void clock_init()
{
    Ds1302Init();
}

void Ds1302ReadTime()
{
    uchar n;
    uchar temp[7] = { 0 };
    for (n = 0; n < 7; n++) // 读取 7 个字节的时钟信号：分秒时日月周年
    {
        temp[n] = BCD_to_uchar(Ds1302Read(READ_RTC_ADDR[n]));
    }
    memcpy(&s_clock, temp, sizeof(temp));
}

void get_time_string(char* date, char* time)
{
    Ds1302ReadTime();
    sprintf(date, "Date:20%02bd-%02bd-%02bd", s_clock.year, s_clock.month, s_clock.day);
    sprintf(time, "Time:%02bd:%02bd:%02bd %bd", s_clock.hour, s_clock.min, s_clock.sec, s_clock.week);
}

#endif