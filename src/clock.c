#include "common.h"
#include "clock.h"

#if ENABLE_CLOCK_MOUDLE
//---��ʼ��ϵͳʱ�� 2024.07.20 ���� 12:00:00
#define INIT_TIME_YEAR      24
#define INIT_TIME_MONTH     7
#define INIT_TIME_DAY       20
#define INIT_TIME_WEEK      6
#define INIT_TIME_HOUR      12
#define INIT_TIME_MINUTE    0
#define INIT_TIME_SECOND    0

//---DS1302 д��Ͷ�ȡʱ����ĵ�ַ����---//
//---���ʱ�������� ���λ��дλ;-------//
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
    SCLK = 0; // �Ƚ� SCLK �õ͵�ƽ

    _nop_();
    RST = 1; // Ȼ�� RST(CE)�øߵ�ƽ��
    _nop_();
    for (n = 0; n < 8; n++) // ��ʼ���Ͱ�λ��ַ����
    {
        DSIO = addr & 0x01; // ���ݴӵ�λ��ʼ����
        addr >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0;
        _nop_();
    }
    for (n = 0; n < 8; n++) // д�� 8 λ����
    {
        DSIO = dat & 0x01;
        dat >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0;
        _nop_();
    }
    RST = 0; // �������ݽ���
    _nop_();
}

static uchar Ds1302Read(uchar addr)
{
    uchar n, dat, dat1;
    RST = 0;
    _nop_();
    SCLK = 0; // �Ƚ� SCLK �õ͵�ƽ��
    _nop_();
    RST = 1; // Ȼ�� RST(CE)�øߵ�ƽ��
    _nop_();
    for (n = 0; n < 8; n++) // ��ʼ���Ͱ�λ��ַ����
    {
        DSIO = addr & 0x01; // ���ݴӵ�λ��ʼ����
        addr >>= 1;
        SCLK = 1; // ������������ʱ��DS1302 ��ȡ����
        _nop_();
        SCLK = 0; // DS1302 �½���ʱ����������
        _nop_();
    }
    _nop_();
    for (n = 0; n < 8; n++) // ��ȡ 8 λ����
    {
        dat1 = DSIO; // �����λ��ʼ����
        dat = (dat >> 1) | (dat1 << 7);
        SCLK = 1;
        _nop_();
        SCLK = 0; // DS1302 �½���ʱ����������
        _nop_();
    }
    RST = 0;
    _nop_(); // ����Ϊ DS1302 ��λ���ȶ�ʱ��,����ġ�
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
    Ds1302Write(0x8E, 0X00); // ��ֹд���������ǹر�д��������
    for (n = 0; n < 7; n++)  // д�� 7 ���ֽڵ�ʱ���źţ�����ʱ��������
    {
        Ds1302Write(WRITE_RTC_ADDR[n], uchar_to_BCD(temp[n]));
    }
    Ds1302Write(0x8E, 0x80); // ��д��������
}

void clock_init()
{
    Ds1302Init();
}

void Ds1302ReadTime()
{
    uchar n;
    uchar temp[7] = { 0 };
    for (n = 0; n < 7; n++) // ��ȡ 7 ���ֽڵ�ʱ���źţ�����ʱ��������
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