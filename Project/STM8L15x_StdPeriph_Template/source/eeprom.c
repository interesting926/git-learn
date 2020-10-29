/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#include	"eeprom.h"
#include "stm8l15x.h"
#include	"stm8l15x_flash.h"
#include	"function.h"
#include	"uart.h"






void Set_Paper_Parity(u16 addr)
{
    FLASH_Unlock(FLASH_MemType_Data);
    FLASH_ProgramByte(addr,Parity_A);
    FLASH_ProgramByte(addr+1,Parity_B);
    FLASH_Lock(FLASH_MemType_Data);
}


u8 Get_Paper_Length(u16 addr)   //从eeprom当中获取纸的长度
{
    u8 temp;
    temp = FLASH_ReadByte(addr);
    return temp;
}


void Set_Paper_Length(u16 addr,u8 len)
{
    FLASH_Unlock(FLASH_MemType_Data);
    FLASH_ProgramByte(addr,len);
    FLASH_Lock(FLASH_MemType_Data);
}

void Eeprom_Init(void)		//上电时获取记忆状态
{
  u8 flag1,flag2;
	u8 length;
	FLASH_DeInit();			//Flash复位
	FLASH_ITConfig(DISABLE);	//禁止中断
	flag1 = FLASH_ReadByte(PaperParity_Addr);	//获取标志位1
	flag2 = FLASH_ReadByte(PaperParity_Addr+1);//获取标志位2
	if((flag1==Parity_A)&&(flag2==Parity_B))	//第一次上电
	{
	    length=Get_Paper_Length(PaperLength_Addr);
			c_dbg_print("[eeprom]: Paper Length is ok:%d\r\n",length);
	}
	else
	{
		length=1;		//默认有三种长度：0,1,2
		Set_Paper_Parity(PaperParity_Addr);
		Set_Paper_Length(PaperLength_Addr,length);
		c_dbg_print("[eeprom]: Paper Length is ng:%d\r\n",length);
	}
}




