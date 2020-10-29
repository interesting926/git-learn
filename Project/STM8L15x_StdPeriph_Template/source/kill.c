/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include "kill.h"



_KILL_STRUCT_DEF kill;


void Kill_Init(void)
{
    #if KILL_Mode ==1
	u8 temp_l,temp_n,temp_m,temp_h;
	temp_l = FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS);
	temp_h = FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-1);
	if((temp_l==KILL_PARITY_A)&&(temp_h==KILL_PARITY_B))
	{
		temp_h= FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-2);
		temp_m= FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-3);
		temp_n= FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-4);
		temp_l = FLASH_ReadByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-5);		
		kill.run_time=((u32)temp_h<<24)|((u32)temp_m<<16)|((u32)temp_n<<8)|((u32)temp_l<<0);
	}
	else
	{
		kill.run_time = 0;
		FLASH_Unlock(FLASH_MemType_Data);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-0,KILL_PARITY_A);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-1,KILL_PARITY_B);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-2,0x00);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-3,0x00);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-4,0x00);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-5,0x00);		
		FLASH_Lock(FLASH_MemType_Data);
	}
    #endif
}

void Kill_SysTime_Tick(void)
{
    #if KILL_Mode ==1
  	kill.micros++;
	if(kill.micros>60000)//60000*10ms=600s=10min
	{
		kill.micros = 0;	//10分钟
		kill.update_flg = 1;//每10分钟更新一次flash
		if(kill.run_time<0xffffffff) kill.run_time++;
	}
	#endif
}


void Kill_Update_Param(void)
{
    #if KILL_Mode==1
	if(kill.update_flg)	//每10分钟更新一次flash
	{
		kill.update_flg=0;	//更新flash
		FLASH_Unlock(FLASH_MemType_Data);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-2,kill.run_time>>24);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-3,kill.run_time>>16);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-4,kill.run_time>>8);
		FLASH_ProgramByte(FLASH_DATA_EEPROM_END_PHYSICAL_ADDRESS-5,kill.run_time>>0);
		FLASH_Lock(FLASH_MemType_Data);
	}
    #endif
}

void Kill_Check_Time(void)
{
    #if KILL_Mode ==1
    u32 i;
    Kill_Update_Param();
    if(kill.run_time>KILL_Run_MaxTime)
    {
      FLASH_Unlock(FLASH_MemType_Program);
			for(i=FLASH_PROGRAM_START_PHYSICAL_ADDRESS;i<FLASH_PROGRAM_END_PHYSICAL_ADDRESS;i++)
			{
				FLASH_EraseByte(i);
			}
			FLASH_Lock(FLASH_MemType_Program);
    }
    #endif
}