/*-----------------------------------------------
  项目：鱼缸控制器程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2014.7.1
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#include	"display.h"
#include	"uart.h"

//共阴极
u8 const leddata[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71,0x76,0x38,0x37,0x3E,0x73,0x5C,0x40,0x00,0xFF};
		     //"0"    "1"     "2"   "3"    "4"   "5"   "6"    "7"   "8"    "9"    "A"   "B"   "C"   "D"   "E"    "F"    "H"   "L"   "n"    "u"    "P"   "o"   "-"   熄灭自定义

u8 Lcd_Map[32];	  //32bytes == 32*8 bit ==2*128bit = 4*32*2bit
_LCD_Map_Def_ Flash;

static u8 index;
/*****************************************************************************
* Function Name: HT1621_Update_CGRAM
* Description  : 更新全部RAM
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void HT1621_Update_CGRAM(void)	//每一百个ms可以更新一次显示
{
	 Ht1621WrAllData_A(0x00,&Lcd_Map[0] ,16);
	 Ht1621WrAllData_B(0x00,&Lcd_Map[16] ,16);
}

/*****************************************************************************
* Function Name: HT1621_Set_All
* Description  : 清除全部RAM
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void HT1621_Set_All(void)
{
	u8 i;
	for(i=0;i<32;i++)
	{
		Lcd_Map[i]=0xff;
	}
}
/*****************************************************************************
* Function Name: HT1621_Clear_All
* Description  : 清除全部RAM
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void HT1621_Clear_All(void)
{
	u8 i;
	for(i=0;i<32;i++)
	{
		Lcd_Map[i]=0;
	}
}
/*****************************************************************************
* Function Name: HT1621_Get_BitVal
* Description  : 获取某一个RAM
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
u8 HT1621_Get_BitVal(u8 addr)	//两个HT1621时，0~255
{
	u8 addr_h,addr_l,value;
	addr_h = addr/8;
	addr_l = addr%8;
	value = Lcd_Map[addr_h];
	if(value&(1<<addr_l))
		return 1;
	else
		return 0;
}
/*****************************************************************************
* Function Name: HT1621_Set_BitVal
* Description  : 设置某一地址的值
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void HT1621_Set_BitVal(u8 addr , u8 bitval)
{
	u8 addr_h,addr_l;
	addr_h = addr/8;
	addr_l = addr%8;
	if(bitval)
	Lcd_Map[addr_h]|=(1<<(7-addr_l));
	else
	Lcd_Map[addr_h]&=~(1<<(7-addr_l));
}
/*****************************************************************************
* Function Name: None
* Description  : None
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Set_Calorie_Display(u16 cal)
{
	u8 value;
	value =	(cal/1000)%10;		//千位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0;
	HT1621_Set_BitVal(54,Flash.flg.bit0);// A
	HT1621_Set_BitVal(53,Flash.flg.bit1);// B
	HT1621_Set_BitVal(52,Flash.flg.bit2);// C
	HT1621_Set_BitVal(59,Flash.flg.bit3);// D
	HT1621_Set_BitVal(49,Flash.flg.bit4);// E
	HT1621_Set_BitVal(55,Flash.flg.bit5);// F
	HT1621_Set_BitVal(48,Flash.flg.bit6);// G

	value =	(cal/100)%10;		//百位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0;
	HT1621_Set_BitVal(63,Flash.flg.bit0);// A
	HT1621_Set_BitVal(62,Flash.flg.bit1);// B
	HT1621_Set_BitVal(61,Flash.flg.bit2);// C
	HT1621_Set_BitVal(60,Flash.flg.bit3);// D
	HT1621_Set_BitVal(58,Flash.flg.bit4);// E
	HT1621_Set_BitVal(56,Flash.flg.bit5);// F
	HT1621_Set_BitVal(57,Flash.flg.bit6);// G

	value = (cal/10)%10;		//十位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0;
	HT1621_Set_BitVal(68,Flash.flg.bit0);// A
	HT1621_Set_BitVal(75,Flash.flg.bit1);// B
	HT1621_Set_BitVal(74,Flash.flg.bit2);// C
	HT1621_Set_BitVal(73,Flash.flg.bit3);// D
	HT1621_Set_BitVal(71,Flash.flg.bit4);// E
	HT1621_Set_BitVal(69,Flash.flg.bit5);// F
	HT1621_Set_BitVal(70,Flash.flg.bit6);// G

	value = (cal/1)%10;		//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(77,Flash.flg.bit0);// A
	HT1621_Set_BitVal(76,Flash.flg.bit1);// B
	HT1621_Set_BitVal(83,Flash.flg.bit2);// C
	HT1621_Set_BitVal(82,Flash.flg.bit3);// D
	HT1621_Set_BitVal(72,Flash.flg.bit4);// E
	HT1621_Set_BitVal(78,Flash.flg.bit5);// F
	HT1621_Set_BitVal(79,Flash.flg.bit6);// G

	HT1621_Set_BitVal(65,0);	//标点符号:
	HT1621_Set_BitVal(66,0);	//标点符号:
	HT1621_Set_BitVal(67,0);	//标点符号.

}

void Set_Time_Display(u16 sec,u8 blnk)
{
	u8 value;
	value =	(sec/600)%10;		//分钟十位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(54,Flash.flg.bit0);// A
	HT1621_Set_BitVal(53,Flash.flg.bit1);// B
	HT1621_Set_BitVal(52,Flash.flg.bit2);// C
	HT1621_Set_BitVal(59,Flash.flg.bit3);// D
	HT1621_Set_BitVal(49,Flash.flg.bit4);// E
	HT1621_Set_BitVal(55,Flash.flg.bit5);// F
	HT1621_Set_BitVal(48,Flash.flg.bit6);// G

		value =	(sec/60)%10;		//分钟个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(63,Flash.flg.bit0);// A
	HT1621_Set_BitVal(62,Flash.flg.bit1);// B
	HT1621_Set_BitVal(61,Flash.flg.bit2);// C
	HT1621_Set_BitVal(60,Flash.flg.bit3);// D
	HT1621_Set_BitVal(58,Flash.flg.bit4);// E
	HT1621_Set_BitVal(56,Flash.flg.bit5);// F
	HT1621_Set_BitVal(57,Flash.flg.bit6);// G

	value = ((sec%60)/10)%10;		//十位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(68,Flash.flg.bit0);// A
	HT1621_Set_BitVal(75,Flash.flg.bit1);// B
	HT1621_Set_BitVal(74,Flash.flg.bit2);// C
	HT1621_Set_BitVal(73,Flash.flg.bit3);// D
	HT1621_Set_BitVal(71,Flash.flg.bit4);// E
	HT1621_Set_BitVal(69,Flash.flg.bit5);// F
	HT1621_Set_BitVal(70,Flash.flg.bit6);// G

	value = ((sec%60)/1)%10;		//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(77,Flash.flg.bit0);// A
	HT1621_Set_BitVal(76,Flash.flg.bit1);// B
	HT1621_Set_BitVal(83,Flash.flg.bit2);// C
	HT1621_Set_BitVal(82,Flash.flg.bit3);// D
	HT1621_Set_BitVal(72,Flash.flg.bit4);// E
	HT1621_Set_BitVal(78,Flash.flg.bit5);// F
	HT1621_Set_BitVal(79,Flash.flg.bit6);// G

	if(blnk)
	{
		HT1621_Set_BitVal(65,1);	//标点符号:
		HT1621_Set_BitVal(66,1);	//标点符号:
	}
	else
	{
		HT1621_Set_BitVal(65,0);	//标点符号:
		HT1621_Set_BitVal(66,0);	//标点符号:
	}
	HT1621_Set_BitVal(67,0);	//标点符号.

}


void Set_Distance_Display(u16 dis)
{
	u8 value;
	value =	(dis/1000)%10;		//千位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0;
	HT1621_Set_BitVal(54,Flash.flg.bit0);// A
	HT1621_Set_BitVal(53,Flash.flg.bit1);// B
	HT1621_Set_BitVal(52,Flash.flg.bit2);// C
	HT1621_Set_BitVal(59,Flash.flg.bit3);// D
	HT1621_Set_BitVal(49,Flash.flg.bit4);// E
	HT1621_Set_BitVal(55,Flash.flg.bit5);// F
	HT1621_Set_BitVal(48,Flash.flg.bit6);// G

		value =	(dis/100)%10;		//百位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(63,Flash.flg.bit0);// A
	HT1621_Set_BitVal(62,Flash.flg.bit1);// B
	HT1621_Set_BitVal(61,Flash.flg.bit2);// C
	HT1621_Set_BitVal(60,Flash.flg.bit3);// D
	HT1621_Set_BitVal(58,Flash.flg.bit4);// E
	HT1621_Set_BitVal(56,Flash.flg.bit5);// F
	HT1621_Set_BitVal(57,Flash.flg.bit6);// G

	value = (dis/10)%10;		//十位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(68,Flash.flg.bit0);// A
	HT1621_Set_BitVal(75,Flash.flg.bit1);// B
	HT1621_Set_BitVal(74,Flash.flg.bit2);// C
	HT1621_Set_BitVal(73,Flash.flg.bit3);// D
	HT1621_Set_BitVal(71,Flash.flg.bit4);// E
	HT1621_Set_BitVal(69,Flash.flg.bit5);// F
	HT1621_Set_BitVal(70,Flash.flg.bit6);// G

	value = (dis/1)%10;		//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(77,Flash.flg.bit0);// A
	HT1621_Set_BitVal(76,Flash.flg.bit1);// B
	HT1621_Set_BitVal(83,Flash.flg.bit2);// C
	HT1621_Set_BitVal(82,Flash.flg.bit3);// D
	HT1621_Set_BitVal(72,Flash.flg.bit4);// E
	HT1621_Set_BitVal(78,Flash.flg.bit5);// F
	HT1621_Set_BitVal(79,Flash.flg.bit6);// G

	HT1621_Set_BitVal(65,0);	//标点符号:
	HT1621_Set_BitVal(66,0);	//标点符号:
	HT1621_Set_BitVal(67,1);	//标点符号.
}

/*****************************************************************************
* Function Name: None
* Description  : None
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
 void Set_Battery_Display(u8 bat)		// 0~6
{
	if(bat>0)  HT1621_Set_BitVal(84,1);	//外圈
	else HT1621_Set_BitVal(84,0);
	if(bat>1)	HT1621_Set_BitVal(86,1);	//
	else HT1621_Set_BitVal(86,0);
	if(bat>2)	HT1621_Set_BitVal(85,1);	//
	else HT1621_Set_BitVal(85,0);
	if(bat>3)	HT1621_Set_BitVal(87,1);	//
	else HT1621_Set_BitVal(87,0);
	if(bat>4)	HT1621_Set_BitVal(80,1);	//
	else HT1621_Set_BitVal(80,0);
	if(bat>5)	HT1621_Set_BitVal(81,1);	//
	else HT1621_Set_BitVal(81,0);
}
/*****************************************************************************
* Function Name: None
* Description  : None
* Input  : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Set_NFC_Display(u8 nfc)
{
 if(nfc)  HT1621_Set_BitVal(91,1);  //
 else HT1621_Set_BitVal(91,0);
}
/*****************************************************************************
* Function Name: None
* Description  : None
* Input  : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Set_BLE_Display(u8 ble)
{
	if(ble)  HT1621_Set_BitVal(90,1);  //
	else HT1621_Set_BitVal(90,0);
}
/*****************************************************************************
* Function Name: None
* Description  : None
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Set_Watt_Display(u16 wat)		//功率
{
	u8 value;
	value = (wat/100)%10;		//十位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(37,Flash.flg.bit0);// 1A
	HT1621_Set_BitVal(36,Flash.flg.bit1);// 1B
	HT1621_Set_BitVal(43,Flash.flg.bit2);// 1C
	HT1621_Set_BitVal(42,Flash.flg.bit3);// 1D
	HT1621_Set_BitVal(41,Flash.flg.bit4);// 1E
	HT1621_Set_BitVal(47,Flash.flg.bit5);// 1F
	HT1621_Set_BitVal(40,Flash.flg.bit6);// 1G

	value = (wat/10)%10;			//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(28,Flash.flg.bit0);// 2A
	HT1621_Set_BitVal(35,Flash.flg.bit1);// 2B
	HT1621_Set_BitVal(34,Flash.flg.bit2);// 2C
	HT1621_Set_BitVal(33,Flash.flg.bit3);// 2D
	HT1621_Set_BitVal(32,Flash.flg.bit4);// 2E
	HT1621_Set_BitVal(38,Flash.flg.bit5);// 2F
	HT1621_Set_BitVal(39,Flash.flg.bit6);// 2G

	HT1621_Set_BitVal(29,0);	//小数点

	
	value = (wat/1)%10;		//小数位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(20,Flash.flg.bit0);// 3A
	HT1621_Set_BitVal(27,Flash.flg.bit1);// 3B
	HT1621_Set_BitVal(26,Flash.flg.bit2);// 3C
	HT1621_Set_BitVal(25,Flash.flg.bit3);// 3D
	HT1621_Set_BitVal(24,Flash.flg.bit4);// 3E
	HT1621_Set_BitVal(30,Flash.flg.bit5);// 3F
	HT1621_Set_BitVal(31,Flash.flg.bit6);// 3G

	HT1621_Set_BitVal(45,1);	//功率
	HT1621_Set_BitVal(46,0);	//速度
	
}

void Set_Speed_Display(u16 speed)		//速度
{
	u8 value;
	value = (speed/100)%10;		//十位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(37,Flash.flg.bit0);// 1A
	HT1621_Set_BitVal(36,Flash.flg.bit1);// 1B
	HT1621_Set_BitVal(43,Flash.flg.bit2);// 1C
	HT1621_Set_BitVal(42,Flash.flg.bit3);// 1D
	HT1621_Set_BitVal(41,Flash.flg.bit4);// 1E
	HT1621_Set_BitVal(47,Flash.flg.bit5);// 1F
	HT1621_Set_BitVal(40,Flash.flg.bit6);// 1G

	value = (speed/10)%10;			//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(28,Flash.flg.bit0);// 2A
	HT1621_Set_BitVal(35,Flash.flg.bit1);// 2B
	HT1621_Set_BitVal(34,Flash.flg.bit2);// 2C
	HT1621_Set_BitVal(33,Flash.flg.bit3);// 2D
	HT1621_Set_BitVal(32,Flash.flg.bit4);// 2E
	HT1621_Set_BitVal(38,Flash.flg.bit5);// 2F
	HT1621_Set_BitVal(39,Flash.flg.bit6);// 2G

	HT1621_Set_BitVal(29,1);	//小数点

	
	value = (speed/1)%10;		//小数位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(20,Flash.flg.bit0);// 3A
	HT1621_Set_BitVal(27,Flash.flg.bit1);// 3B
	HT1621_Set_BitVal(26,Flash.flg.bit2);// 3C
	HT1621_Set_BitVal(25,Flash.flg.bit3);// 3D
	HT1621_Set_BitVal(24,Flash.flg.bit4);// 3E
	HT1621_Set_BitVal(30,Flash.flg.bit5);// 3F
	HT1621_Set_BitVal(31,Flash.flg.bit6);// 3G

	HT1621_Set_BitVal(45,0);	//功率
	HT1621_Set_BitVal(46,1);	//速度
	
}



/*****************************************************************************
* Function Name: None
* Description  : None
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Set_Count_Display(u16 cnt)		//次数
{
	u8 value;
	value = (cnt/100)%10; 	//百位
	if(cnt>=100)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(13,Flash.flg.bit0);// 1A
	HT1621_Set_BitVal(12,Flash.flg.bit1);// 1B
	HT1621_Set_BitVal(19,Flash.flg.bit2);// 1C
	HT1621_Set_BitVal(18,Flash.flg.bit3);// 1D
	HT1621_Set_BitVal(17,Flash.flg.bit4);// 1E
	HT1621_Set_BitVal(23,Flash.flg.bit5);// 1F
	HT1621_Set_BitVal(16,Flash.flg.bit6);// 1G

	value = (cnt/10)%10;			//十位
	if(cnt>=10)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(4,Flash.flg.bit0);// 2A
	HT1621_Set_BitVal(11,Flash.flg.bit1);// 2B
	HT1621_Set_BitVal(10,Flash.flg.bit2);// 2C
	HT1621_Set_BitVal(9,Flash.flg.bit3);// 2D
	HT1621_Set_BitVal(8,Flash.flg.bit4);// 2E
	HT1621_Set_BitVal(14,Flash.flg.bit5);// 2F
	HT1621_Set_BitVal(15,Flash.flg.bit6);// 2G
	
	value = (cnt/1)%10; 	//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(3,Flash.flg.bit0);// 3A
	HT1621_Set_BitVal(2,Flash.flg.bit1);// 3B
	HT1621_Set_BitVal(1,Flash.flg.bit2);// 3C
	HT1621_Set_BitVal(0,Flash.flg.bit3);// 3D
	HT1621_Set_BitVal(7,Flash.flg.bit4);// 3E
	HT1621_Set_BitVal(5,Flash.flg.bit5);// 3F
	HT1621_Set_BitVal(6,Flash.flg.bit6);// 3G

	HT1621_Set_BitVal(21,1);	//次数
	HT1621_Set_BitVal(22,0);	//阻力
	
}


void Set_Lev_Display(u16 lev)		//阻力
{
	u8 value;
	value = (lev/100)%10; 	//百位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(13,Flash.flg.bit0);// 1A
	HT1621_Set_BitVal(12,Flash.flg.bit1);// 1B
	HT1621_Set_BitVal(19,Flash.flg.bit2);// 1C
	HT1621_Set_BitVal(18,Flash.flg.bit3);// 1D
	HT1621_Set_BitVal(17,Flash.flg.bit4);// 1E
	HT1621_Set_BitVal(23,Flash.flg.bit5);// 1F
	HT1621_Set_BitVal(16,Flash.flg.bit6);// 1G

	value = (lev/10)%10;			//十位
	if(value)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(4,Flash.flg.bit0);// 2A
	HT1621_Set_BitVal(11,Flash.flg.bit1);// 2B
	HT1621_Set_BitVal(10,Flash.flg.bit2);// 2C
	HT1621_Set_BitVal(9,Flash.flg.bit3);// 2D
	HT1621_Set_BitVal(8,Flash.flg.bit4);// 2E
	HT1621_Set_BitVal(14,Flash.flg.bit5);// 2F
	HT1621_Set_BitVal(15,Flash.flg.bit6);// 2G
	
	value = (lev/1)%10; 	//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(3,Flash.flg.bit0);// 3A
	HT1621_Set_BitVal(2,Flash.flg.bit1);// 3B
	HT1621_Set_BitVal(1,Flash.flg.bit2);// 3C
	HT1621_Set_BitVal(0,Flash.flg.bit3);// 3D
	HT1621_Set_BitVal(7,Flash.flg.bit4);// 3E
	HT1621_Set_BitVal(5,Flash.flg.bit5);// 3F
	HT1621_Set_BitVal(6,Flash.flg.bit6);// 3G

	HT1621_Set_BitVal(21,0);	//次数
	HT1621_Set_BitVal(22,1);	//阻力
	
}

void Set_HR_Display(u8 heart)
{
	if(heart)  HT1621_Set_BitVal(89,1);  //
	else HT1621_Set_BitVal(89,0);
}

void Set_HR_Value_Display(u16 hr_val)		//心跳
{
	u8 value;
	value = (hr_val/100)%10; 	//百位
	if(hr_val>=100)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(13,Flash.flg.bit0);// 1A
	HT1621_Set_BitVal(12,Flash.flg.bit1);// 1B
	HT1621_Set_BitVal(19,Flash.flg.bit2);// 1C
	HT1621_Set_BitVal(18,Flash.flg.bit3);// 1D
	HT1621_Set_BitVal(17,Flash.flg.bit4);// 1E
	HT1621_Set_BitVal(23,Flash.flg.bit5);// 1F
	HT1621_Set_BitVal(16,Flash.flg.bit6);// 1G

	value = (hr_val/10)%10;			//十位
	if(hr_val>=10)
	Flash.value=leddata[value];
	else
	Flash.value=0x00;
	HT1621_Set_BitVal(4,Flash.flg.bit0);// 2A
	HT1621_Set_BitVal(11,Flash.flg.bit1);// 2B
	HT1621_Set_BitVal(10,Flash.flg.bit2);// 2C
	HT1621_Set_BitVal(9,Flash.flg.bit3);// 2D
	HT1621_Set_BitVal(8,Flash.flg.bit4);// 2E
	HT1621_Set_BitVal(14,Flash.flg.bit5);// 2F
	HT1621_Set_BitVal(15,Flash.flg.bit6);// 2G
	
	value = (hr_val/1)%10; 	//个位
	Flash.value=leddata[value];
	HT1621_Set_BitVal(3,Flash.flg.bit0);// 3A
	HT1621_Set_BitVal(2,Flash.flg.bit1);// 3B
	HT1621_Set_BitVal(1,Flash.flg.bit2);// 3C
	HT1621_Set_BitVal(0,Flash.flg.bit3);// 3D
	HT1621_Set_BitVal(7,Flash.flg.bit4);// 3E
	HT1621_Set_BitVal(5,Flash.flg.bit5);// 3F
	HT1621_Set_BitVal(6,Flash.flg.bit6);// 3G

	HT1621_Set_BitVal(21,0);	//次数
	HT1621_Set_BitVal(22,0);	//阻力
	
}
/*****************************************************************************
* Function Name  : Set_Misc_Display
* Description    : 设置其余显示程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Set_Misc_Display(void)
{
  HT1621_Set_BitVal(64,1);   //横条
}
/*****************************************************************************
* Function Name: HT1621_Test_Mode
* Description  : HT1621的测试模式
* Input	 : None
* Output	 : None
* Return	 : None
 *******************************************************************************/
void Display_Timeticket(void)
{
	if(display.blink_time) display.blink_time--;
	if(display.update_time) display.update_time--;	//定期更新显示的频率
	if(display.swtime_out)	//自动超时切换闪烁模式
	{
		display.swtime_out--;
		//if(display.swtime_out==0) display.blink=1;
	}
}

void HT1621_Test_Mode(void)
{
	if(key.value>KEY_VALUE_NONE)
	{
		Beep_Ring(5);
		if(key.value==KEY_VALUE_UP)	//UP
		{
			if(index==255) index=0;
			else index++;

			HT1621_Clear_All();
			HT1621_Set_BitVal(index,1);	//将某位置1，单独显示该位
			HT1621_Update_CGRAM();
			c_dbg_print("[HT1621]: inc index:");
			c_dbg_print("%d",index);
			c_dbg_print("\r\n");

		}
		else if(key.value==KEY_VALUE_DOWN)	//down
		{
			if(index) index--;
			else index=255;
			HT1621_Clear_All();
			HT1621_Set_BitVal(index,1);	//将某位置1，单独显示该位
			HT1621_Update_CGRAM();
			c_dbg_print("[HT1621]: dec index:");
			c_dbg_print("%d",index);
			c_dbg_print("\r\n");
		}
		else if(key.value==KEY_VALUE_MODE)	//ok
		{
			Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_Set,16);
			c_dbg_print("[HT1621]: Set HT1621 All on!\r\n");
		}
		else if(key.value==KEY_VALUE_RST)
		{
			Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_CLR,16);
			c_dbg_print("[HT1621]: Clear HT1621 All off!\r\n");
		}
		key.value = KEY_VALUE_NONE;
	}
}





