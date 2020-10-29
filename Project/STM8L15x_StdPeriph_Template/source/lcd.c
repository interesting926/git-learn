/*-----------------------------------------------
  ��Ŀ��Smart Demo ����
  ��̳��www.forlinux.com
  ���ߣ�Fuqiaobin
  ���ڣ�2017.12.30
  �汾: V1.0
  ע�����V1.0:  ����  ����: 16M�ڲ�����
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
* Description    :  ѡ��HT1621
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
/***************��ʱ����******************/

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
д���ݺ���,cntΪ��������λ��,���ݴ���Ϊ��λ��ǰ
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
�������ƣ�void Ht1621_Write_Data(u8 Cmd)
��������: HT1623����д�뺯��
����˵����CmdΪд����������
����˵������
********************************************************/
void Ht1621_WrCmd_A(u8 Cmd)
{
	Ht1621_Select_A_Chip();
	Ht1621_Write_Data(0x80,4); //д�������־100
	Ht1621_Write_Data(Cmd,8); //д����������
	Ht1621_DeSelect_Chip();
}
void Ht1621_WrCmd_B(u8 Cmd)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0x80,4); //д�������־100
    Ht1621_Write_Data(Cmd,8); //д����������
    Ht1621_DeSelect_Chip();
}

/********************************************************
�������ƣ�void SendByteToHt1621(u8 Addr,u8 Data)
��������: HT1623��ָ����ַд�����ݺ���
����˵����AddrΪд���ʼ��ַ��DataΪд������
����˵������
********************************************************/
void Ht1621_SendByteToA(u8 Addr,u8 Data)
{
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    Ht1621_Write_Data(Data,8); //д������
    Ht1621_DeSelect_Chip();
}

void Ht1621_SendByteToB(u8 Addr,u8 Data)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    Ht1621_Write_Data(Data,8); //д������
    Ht1621_DeSelect_Chip();
}


/********************************************************
�������ƣ�void Send_4BitToHt1621(u8 Addr,u8 Data)
��������: HT1623��ָ����ַд�����ݺ���
����˵����AddrΪд���ʼ��ַ��DataΪд������
����˵������
********************************************************/
void Ht1621_Send_4BitToA(u8 Addr,u8 Data)
{
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    Ht1621_Write_Data(Data<<4,4); //д������
    Ht1621_DeSelect_Chip();
}

void Ht1621_Send_4BitToB(u8 Addr,u8 Data)
{
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    Ht1621_Write_Data(Data<<4,4); //д������
    Ht1621_DeSelect_Chip();
}

/********************************************************
�������ƣ�void Ht1621WrAllData(u8 Addr,u8 *p,u8 cnt)
��������: HT1623����д�뷽ʽ����
����˵����AddrΪд���ʼ��ַ��*pΪ����д������ָ�룬
cntΪд����������
˵����HT1621������λ4λ���˴�ÿ������Ϊ8λ��д������
������8λ����
********************************************************/
void Ht1621WrAllData_A(u8 Addr,u8 *p,u8 cnt)
{
    u8 i;
    Ht1621_Select_A_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    for (i=0;i<cnt;i++)
    {
      Ht1621_Write_Data(*p,8); //д������
      p++;
    }
    Ht1621_DeSelect_Chip();
}
void Ht1621WrAllData_B(u8 Addr,u8 *p,u8 cnt)
{
    u8 i;
    Ht1621_Select_B_Chip();
    Ht1621_Write_Data(0xa0,3); //д�����ݱ�־101
    Ht1621_Write_Data(Addr<<2,6); //д���ַ����
    for (i=0;i<cnt;i++)
    {
      Ht1621_Write_Data(*p,8); //д������
      p++;
    }
    Ht1621_DeSelect_Chip();
}

/********************************************************
�������ƣ�void Ht1621_Init(void)
��������: HT1623��ʼ��
����˵������
˵������ʼ����Һ���������ֶξ���ʾ
********************************************************/
void Ht1621_Init_A(void)
{
  Ht1621_DeSelect_Chip();
  Ht1621_WR_High();
  Ht1621_DATA_High();
  Ht1621_DelayMS(2000); //��ʱʹLCD������ѹ�ȶ�
  Ht1621_WrCmd_A(RC256); //ʹ���ڲ�����
  Ht1621_WrCmd_A(SYSDIS);
  Ht1621_WrCmd_A(SYSEN);
  Ht1621_WrCmd_A(LCDON);
  Ht1621_DelayMS(500); //��ʱһ��ʱ��

}
/********************************************************
�������ƣ�void Ht1621_Init(void)
��������: HT1623��ʼ��
����˵������
˵������ʼ����Һ���������ֶξ���ʾ
********************************************************/
void Ht1621_Init_B(void)
{
	Ht1621_DeSelect_Chip();
	Ht1621_WR_High();
	Ht1621_DATA_High();
	Ht1621_DelayMS(2000); //��ʱʹLCD������ѹ�ȶ�
	Ht1621_WrCmd_B(RC256); //ʹ���ڲ�����
	Ht1621_WrCmd_B(SYSDIS);
	Ht1621_WrCmd_B(SYSEN);
	Ht1621_WrCmd_B(LCDON);
	Ht1621_DelayMS(500); //��ʱһ��ʱ��


}
void HT1621B_Init(void)
{
	Ht1621_DeSelect_Chip();
	Ht1621_WR_High();
	Ht1621_DATA_High();
	Ht1621_DelayMS(10); //��ʱʹLCD������ѹ�ȶ�

	Ht1621_WrCmd_A(RC256); //ʹ���ڲ�����
	Ht1621_WrCmd_A(SYSDIS);
	Ht1621_WrCmd_A(SYSEN);
	Ht1621_WrCmd_A(BIAS_13_4C);
	Ht1621_WrCmd_A(LCDON);

	Ht1621_WrCmd_B(RC256); //ʹ���ڲ�����
	Ht1621_WrCmd_B(SYSDIS);
	Ht1621_WrCmd_B(SYSEN);
	Ht1621_WrCmd_B(BIAS_13_4C);
	Ht1621_WrCmd_B(LCDON);

	Ht1621_WrCmd_A(TONE_4K);
  Ht1621_WrCmd_A(TONE_OFF);
	

	Ht1621_DelayMS(20); //��ʱһ��ʱ��
  HT1621_Set_All();
	Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_Set,16);
	Ht1621WrAllData_B(0x00,(u8 *)Ht1621Tab_Set,16);
	Ht1621_DelayMS(1000);
	//Ht1621WrAllData_A(0x00,(u8 *)Ht1621Tab_CLR,16);
	//Ht1621WrAllData_B(0x00,(u8 *)Ht1621Tab_CLR,16);
	//HT1621_Clear_All();

	
}

