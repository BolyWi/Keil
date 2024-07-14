#include <intrins.h>
#include <stdio.h>
#include "gpio.h"
#include "nv_flash.h"
#include "display.h"

void IapIdle()
{
	IAP_CONTR = 0;
	IAP_CMD = 0;
	IAP_TRIG = 0;
	IAP_ADDRH = 0x80;
	IAP_ADDRL = 0;
}

BYTE IapReadByte(WORD addr)
{
	BYTE dat;
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_READ;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x46;
	IAP_TRIG = 0xb9;
	_nop_();
	dat = IAP_DATA;
	IapIdle();
	return dat;
}

void IapProgramByte(WORD addr, BYTE dat)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_PROGRAM;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_DATA = dat;
	IAP_TRIG = 0x46;
	IAP_TRIG = 0xb9;
	_nop_();
	IapIdle();
}

void IapEraseSector(WORD addr)
{
	IAP_CONTR = ENABLE_IAP;
	IAP_CMD = CMD_ERASE;
	IAP_ADDRL = addr;
	IAP_ADDRH = addr >> 8;
	IAP_TRIG = 0x46;
	IAP_TRIG = 0xb9;
	_nop_();
	IapIdle();
}

BYTE ReadByte(WORD addr)
{
	return IapReadByte(addr);
}

void WriteByte(WORD addr, BYTE dat)
{
	IapEraseSector(addr);
	IapProgramByte(addr, dat);
}

unsigned ReadShortValue(WORD addr)
{
	xdata unsigned buf = 0;
	buf = IapReadByte(addr);
	buf = buf << 8 | IapReadByte(addr+1);
	return buf;
}

void WriteShortValue(WORD addr, unsigned dat)
{
	xdata BYTE buf = dat >> 8;
	IapEraseSector(addr);
	IapProgramByte(addr, buf);
	buf = dat & 0xff;
	IapProgramByte(addr+1, buf);
}

void WriteRecord(WORD addr, BYTE size, BYTE *dat)
{
	xdata i = 0;
	IapEraseSector(addr);
	while (i < size)
	{
		IapProgramByte(addr+i, dat[i]);
		i++;
	}
}

void ReadRecord(WORD addr, BYTE size, BYTE *dat)
{
	xdata BYTE i = 0;
	while (i < size)
	{
		dat[i] = IapReadByte(addr+i);
		i++;
	}
}