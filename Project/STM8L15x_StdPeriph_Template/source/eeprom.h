/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#ifndef		_EEPROM_H_
#define		_EEPROM_H_


#include "stm8l15x.h"

typedef union
{
    u16 un_temp16;
    u8  un_temp8[2];
}union_temp16;



#define PaperParity_Addr	FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS
#define PaperLength_Addr	(FLASH_DATA_EEPROM_START_PHYSICAL_ADDRESS+2)

#define Parity_A	0xAA
#define Parity_B	0xBB

extern void Eeprom_Init(void);
extern void Set_Paper_Length(u16 addr,u8 len);
extern u8 Get_Paper_Length(u16 addr);
extern void Set_Paper_Parity(u16 addr);











#endif






