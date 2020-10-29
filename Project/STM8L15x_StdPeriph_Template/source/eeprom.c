/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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


u8 Get_Paper_Length(u16 addr)   //��eeprom���л�ȡֽ�ĳ���
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

void Eeprom_Init(void)		//�ϵ�ʱ��ȡ����״̬
{
  u8 flag1,flag2;
	u8 length;
	FLASH_DeInit();			//Flash��λ
	FLASH_ITConfig(DISABLE);	//��ֹ�ж�
	flag1 = FLASH_ReadByte(PaperParity_Addr);	//��ȡ��־λ1
	flag2 = FLASH_ReadByte(PaperParity_Addr+1);//��ȡ��־λ2
	if((flag1==Parity_A)&&(flag2==Parity_B))	//��һ���ϵ�
	{
	    length=Get_Paper_Length(PaperLength_Addr);
			c_dbg_print("[eeprom]: Paper Length is ok:%d\r\n",length);
	}
	else
	{
		length=1;		//Ĭ�������ֳ��ȣ�0,1,2
		Set_Paper_Parity(PaperParity_Addr);
		Set_Paper_Length(PaperLength_Addr,length);
		c_dbg_print("[eeprom]: Paper Length is ng:%d\r\n",length);
	}
}




