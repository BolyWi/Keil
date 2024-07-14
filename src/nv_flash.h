#ifndef __NV_FLASH_H__
#define __NV_FLASH_H__

#define CMD_READ    1
#define CMD_PROGRAM 2
#define CMD_ERASE   3
#define ENABLE_IAP  0x81

typedef unsigned char BYTE;
typedef unsigned int WORD;

void IapIdle();
BYTE IapReadByte(WORD addr);
void IapProgramByte(WORD addr, BYTE dat);
void IapEraseSector(WORD addr);
BYTE ReadByte(WORD addr);
void WriteByte(WORD addr, BYTE dat);
unsigned ReadShortValue(WORD addr);
void WriteShortValue(WORD addr, unsigned dat);
void WriteRecord(WORD addr, BYTE size, BYTE *dat);
void ReadRecord(WORD addr, BYTE size, BYTE *dat);
#endif //__NV_FLASH_H__