/*-----------------------------------------------
  项目：鱼缸控制器程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2014.7.1
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#ifndef		_DISPLAY_H_
#define		_DISPLAY_H_

#include "stm8l15x.h"
#include    "stdio.h"
#include	"key.h"
#include	"lcd.h"
#include	"function.h"
#include	"uart.h"

typedef union
{
	struct
	{
		u8 bit0:1;
		u8 bit1:1;
		u8 bit2:1;
		u8 bit3:1;
		u8 bit4:1;
		u8 bit5:1;
		u8 bit6:1;
		u8 bit7:1;
	}flg;
	u8 value;
}_LCD_Map_Def_;


extern u8 const Ht1621Tab_CLR[];
extern u8 const Ht1621Tab_Set[];

extern void HT1621_Test_Mode(void);
extern void HT1621_Update_CGRAM(void);
extern void HT1621_Set_All(void);
extern void HT1621_Clear_All(void);
extern u8 HT1621_Get_BitVal(u8 addr);
extern void HT1621_Set_BitVal(u8 addr , u8 bitval);
extern void Set_Calorie_Display(u16 cal);
extern void Set_Time_Display(u16 sec,u8 blnk);
extern void Set_Distance_Display(u16 dis);
extern void Set_Battery_Display(u8 bat);		// 0~6
extern void Set_NFC_Display(u8 nfc);
extern void Set_BLE_Display(u8 ble);
extern void Set_Watt_Display(u16 wat);		//功率
extern void Set_Speed_Display(u16 speed);		//速度
extern void Set_Count_Display(u16 cnt);		//次数
extern void Set_Lev_Display(u16 lev);		//阻力
extern void Set_HR_Display(u8 heart);
extern void Set_HR_Value_Display(u16 hr_val);		//心跳
extern void Set_Misc_Display(void);


#endif