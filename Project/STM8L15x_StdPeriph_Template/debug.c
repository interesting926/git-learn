/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include	"debug.h"


u8 const DBHEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

u16 Time_delay = 0;

/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Debug_Init(void)
{
	GPIO_Init(Uart_Txd_Port,Uart_Txd_Pin,GPIO_Mode_Out_PP_High_Fast);
	Set_TXD_High();
	//Time_delay=540;	//高优化
	Time_delay=324;	//低优化
	//Uart_Debug_Test();
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Delay_us(u16 t)
{
	while(--t);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_Byte(u8 send_dat)
{
   u8 i=8;
   sim();   //禁止中断
   Set_TXD_Low();
   Delay_us(Time_delay);
   while(i--)
   {
	  if(send_dat & 0x01)
	  {
	      Set_TXD_High();
	  }
	  else
	  {
	      Set_TXD_Low();
	  }
	   Delay_us(Time_delay);
	   send_dat >>=1;
   }
   Set_TXD_High();
   rim();       //允许中断
   Delay_us(Time_delay);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_Hex(u8 Byte_HEX)
{
	Uart_Send_Byte(DBHEX[Byte_HEX/16]);
	Uart_Send_Byte(DBHEX[Byte_HEX%16]);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_IntHex(u16 Byte_HEX)
{
	Uart_Send_Byte(DBHEX[(Byte_HEX>>8)/16]);
	Uart_Send_Byte(DBHEX[(Byte_HEX>>8)%16]);
	Uart_Send_Byte(DBHEX[(Byte_HEX&0xff)/16]);
	Uart_Send_Byte(DBHEX[(Byte_HEX&0xff)%16]);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_Dec(u8 Byte_Dec)
{
	Uart_Send_Byte(DBHEX[(Byte_Dec/100)%10]);
	Uart_Send_Byte(DBHEX[(Byte_Dec/10)%10]);
	Uart_Send_Byte(DBHEX[(Byte_Dec/1)%10]);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_IntDec(u16 Int_dec)
{
	Uart_Send_Byte(DBHEX[(Int_dec/10000)%10]);
	Uart_Send_Byte(DBHEX[(Int_dec/1000)%10]);
	Uart_Send_Byte(DBHEX[(Int_dec/100)%10]);
	Uart_Send_Byte(DBHEX[(Int_dec/10)%10]);
	Uart_Send_Byte(DBHEX[(Int_dec/1)%10]);
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_N_bytes(u8 * buff,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart_Send_Byte(*buff++);
	}
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Send_N_Hexs(u8 * buff,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart_Send_Hex(*buff++);
	}
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_dbg_print(char *str)
{
	while(*str)
	{
		Uart_Send_Byte(*str++);
	}
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/
void Uart_Debug_Test(void)
{
	unsigned int Delays;
	for(Delays=0;Delays<10000;Delays++)
	{
		Time_delay=Delays;
		Uart_dbg_print("Data is:");
		Uart_Send_IntDec(Time_delay);
		Uart_dbg_print("\r\n");
		Delay_us(100);
	}
}
/*****************************************************************************
* Function:
* Author:
* Input:
* Output
*****************************************************************************/