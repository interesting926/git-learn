/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/

#include	"lcd.h"


u8 const Ht1621Tab_CLR[]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
u8 const Ht1621Tab_Set[]={0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};

void Ht1621_Port_Init(void)
{
	GPIO_Init(Ht1621_POWER_Port, Ht1621_POWER_Pin, GPIO_Mode_Out_PP_High_Fast);
	GPIO_Init(Ht1621_CS1_Port, Ht1621_CS1_Pin, GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(Ht1621_CS2_Port, Ht1621_CS2_Pin, GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(Ht1621_WR_Port, Ht1621_WR_Pin, GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(Ht1621_DATA_Port, Ht1621_DATA_Pin, GPIO_Mode_Out_PP_Low_Fast);
	GPIO_Init(Ht1621_MODE_Port, Ht1621_MODE_Pin, GPIO_Mode_Out_PP_High_Fast);

	Ht1621_POWER_High();
	Ht1621_MODE_High();
	Ht1621_CS1_High();
	Ht1621_CS2_High();
	Ht1621_WR_High();
	Ht1621_DATA_High();

}
/******************************************************************************
* Function Name  : LCD_Select_Chip
* Description    :  选择HT1621
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void	Ht1621_Select_A_Chip(void)
{
	Ht1621_CS1_Low();
	Ht1621_CS2_High();
}
void	Ht1621_Select_B_Chip(void)
{
	Ht1621_CS1_High();
	Ht1621_CS2_Low();
}
void	Ht1621_DeSelect_Chip(void)
{
	Ht1621_CS1_High();
	Ht1621_CS2_High();
}
/***************延时函数******************/

volatile void Ht1621_Delay(u8 us)
{
	while(--us);
}

volatile void Ht1621_DelayMS(u16 iMs)
{
	u16 i,j;
	for(i=0;i<iMs;i++)
	{
		for(j=0;j<65;j++)
		{
			Ht1621_Delay(100); 
		}
	}
}

/******************************************************
写数据函数,cnt为传送数据位数,数据传送为高位在前
*******************************************************/
void Ht1621_Write_Data(u8 Data,u8 cnt)
{
  u8 i;
  for (i=0;i<cnt;i++)
  {
	  Ht1621_WR_Low();
	  Ht1621_Delay(5);
	  if((Data&0x80)==0) Ht1621_DATA_Low();
	  else Ht1621_DATA_High();
	  Ht1621_WR_High();
	  Ht1621_Delay(5);
	  Data<<=1;
  }
}
/********************************************************
函数名称：void Ht1621_Write_Data(u8 Cmd)
功能描述: HT1623命令写入函数
参数说明：Cmd为写入命令数据
返回说明：无
********************************************************/
void Ht1621_WrCmd_A(u8 Cmd)
{
	Ht1621_Select_A_Chip();
	Ht1621_Write_Data(0x80,4); //写入命令标志100
	Ht1621_Write_Data(Cmd,8); //写入命令数据
	Ht1621_DeSelect_Chip();
}
void Ht1621_WrCmd_B(u8 Cmd)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0x80,4); //写入命令标志100
    Ht1621_Write_Data(Cmd,8); //写入命令数据
    Ht1621_DeSelect_Chip();
}

/********************************************************
函数名称：void SendByteToHt1621(u8 Addr,u8 Data)
功能描述: HT1623在指定地址写入数据函数
参数说明：Addr为写入初始地址，Data为写入数据
返回说明：无
********************************************************/
void Ht1621_SendByteToA(u8 Addr,u8 Data)
{
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    Ht1621_Write_Data(Data,8); //写入数据
    Ht1621_DeSelect_Chip();
}

void Ht1621_SendByteToB(u8 Addr,u8 Data)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    Ht1621_Write_Data(Data,8); //写入数据
    Ht1621_DeSelect_Chip();
}


/********************************************************
函数名称：void Send_4BitToHt1621(u8 Addr,u8 Data)
功能描述: HT1623在指定地址写入数据函数
参数说明：Addr为写入初始地址，Data为写入数据
返回说明：无
********************************************************/
void Ht1621_Send_4BitToA(u8 Addr,u8 Data)
{
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    Ht1621_Write_Data(Data<<4,4); //写入数据
    Ht1621_DeSelect_Chip();
}

void Ht1621_Send_4BitToB(u8 Addr,u8 Data)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    Ht1621_Write_Data(Data<<4,4); //写入数据
    Ht1621_DeSelect_Chip();
}

/********************************************************
函数名称：void Ht1621WrAllData(u8 Addr,u8 *p,u8 cnt)
功能描述: HT1623连续写入方式函数
参数说明：Addr为写入初始地址，*p为连续写入数据指针，
cnt为写入数据总数
说明：HT1621的数据位4位，此处每次数据为8位，写入数据
总数按8位计算
********************************************************/
void Ht1621WrAllData_A(u8 Addr,u8 *p,u8 cnt)
{
    u8 i;
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    for (i=0;i<cnt;i++)
    {
      Ht1621_Write_Data(*p,8); //写入数据
      p++;
    }
    Ht1621_DeSelect_Chip();
}
void Ht1621WrAllData_B(u8 Addr,u8 *p,u8 cnt)
{
    u8 i;
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //写入数据标志101
    Ht1621_Write_Data(Addr<<2,6); //写入地址数据
    for (i=0;i<cnt;i++)
    {
      Ht1621_Write_Data(*p,8); //写入数据
      p++;
    }
    Ht1621_DeSelect_Chip();
}

/********************************************************
函数名称：void Ht1621_Init(void)
功能描述: HT1623初始化
参数说明：无
说明：初始化后，液晶屏所有字段均显示
********************************************************/
void Ht1621_Init_A(void)
{
  Ht1621_DeSelect_Chip();
  Ht1621_WR_High();
  Ht1621_DATA_High();
  Ht1621_DelayMS(2000); //延时使LCD工作电压稳定
  Ht1621_WrCmd_A(RC256); //使用内部振荡器
  Ht1621_WrCmd_A(SYSDIS);
  Ht1621_WrCmd_A(SYSEN);
  Ht1621_WrCmd_A(LCDON);
  Ht1621_DelayMS(500); //延时一段时间

}
/********************************************************
函数名称：void Ht1621_Init(void)
功能描述: HT1623初始化
参数说明：无
说明：初始化后，液晶屏所有字段均显示
********************************************************/
void Ht1621_Init_B(void)
{
	Ht1621_DeSelect_Chip();
	Ht1621_WR_High();
	Ht1621_DATA_High();
	Ht1621_DelayMS(2000); //延时使LCD工作电压稳定
	Ht1621_WrCmd_B(RC256); //使用内部振荡器
	Ht1621_WrCmd_B(SYSDIS);
	Ht1621_WrCmd_B(SYSEN);
	Ht1621_WrCmd_B(LCDON);
	Ht1621_DelayMS(500); //延时一段时间


}
void HT1621B_Init(void)
{
	Ht1621_DeSelect_Chip();
	Ht1621_WR_High();
	Ht1621_DATA_High();
	Ht1621_DelayMS(10); //延时使LCD工作电压稳定

	Ht1621_WrCmd_A(RC256); //使用内部振荡器
	Ht1621_WrCmd_A(SYSDIS);
	Ht1621_WrCmd_A(SYSEN);
	Ht1621_WrCmd_A(BIAS_13_4C);
	Ht1621_WrCmd_A(LCDON);

	Ht1621_WrCmd_B(RC256); //使用内部振荡器
	Ht1621_WrCmd_B(SYSDIS);
	Ht1621_WrCmd_B(SYSEN);
	Ht1621_WrCmd_B(BIAS_13_4C);
	Ht1621_WrCmd_B(LCDON);

	Ht1621_WrCmd_A(TONE_4K);
  Ht1621_WrCmd_A(TONE_OFF);
	

	Ht1621_DelayMS(20); //延时一段时间
  HT1621_Set_All();
	Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_Set,16);
	Ht1621WrAllData_B(0x00,(u8 *)Ht1621Tab_Set,16);
	Ht1621_DelayMS(1000);
	//Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_CLR,16);
	//Ht1621WrAllData_B(0x00,(u8 *)Ht1621Tab_CLR,16);
	//HT1621_Clear_All();

	
}

