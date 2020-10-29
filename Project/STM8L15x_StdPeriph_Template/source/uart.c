/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include "stm8l15x.h"
#include	"main.h"
#include	"uart.h"
#include	"debug.h"
#include "stm8l15x_usart.h"


u8 debug_flg=0;
u8 const HEX[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};


/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
#ifdef	USING_UART1
_UART1_CTRL_DEF uart1;
void Uart1_Init(void)
{
	uart1.length=0;
	uart1.rev_flg=0;
	uart1.time_cnt=0;

	CLK_PeripheralClockConfig(CLK_Peripheral_USART1,ENABLE);
	
	//SYSCFG_REMAPDeInit();
	//stm8l151c8
	GPIO_Init(GPIOC,GPIO_Pin_3,GPIO_Mode_Out_PP_High_Fast);	//TXD	//< USART1 Tx- Rx (PC3- PC2)
	GPIO_Init(GPIOC,GPIO_Pin_2,GPIO_Mode_In_FL_No_IT);	//RXD

	//SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortA,);//< USART1 Tx- Rx (PC3- PC2) remapping to PA2- PA3 //
	//GPIO_Init(GPIOA,GPIO_Pin_2,GPIO_Mode_Out_PP_High_Fast);	//TXD
	//GPIO_Init(GPIOA,GPIO_Pin_3,GPIO_Mode_In_PU_No_IT);	//RXD
	
	//SYSCFG_REMAPPinConfig(REMAP_Pin_USART1TxRxPortC,);//USART1 Tx- Rx (PC3- PC2) remapping to PC5- PC6 //
	//GPIO_Init(GPIOC,GPIO_Pin_5,GPIO_Mode_Out_PP_High_Fast);	//TXD
	//GPIO_Init(GPIOC,GPIO_Pin_6,GPIO_Mode_In_PU_No_IT);	//RXD
	

	USART_DeInit(USART1);
	USART_Init(USART1,(u32)UART1_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Rx|USART_Mode_Tx));
	USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1,ENABLE);
}
void Uart1_SendByte(u8 c)
{
	while ((USART1->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART1,(u8)c);
}
void Uart1_Send_N_bytes(u8 *buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart1_SendByte(buf[i]);
	}
}
void Uart1_Send_Hex(u8 Byte_HEX)
{
	Uart1_SendByte(HEX[Byte_HEX/16]);
	Uart1_SendByte(HEX[Byte_HEX%16]);
}
void Uart1_Send_Dec(u8 Byte_Dec)
{
	Uart1_SendByte(HEX[(Byte_Dec/100)%10]);
	Uart1_SendByte(HEX[(Byte_Dec/10)%10]);
	Uart1_SendByte(HEX[(Byte_Dec/1)%10]);
}
void Uart1_Send_IntDec(u16 Int_dec)
{
	Uart1_SendByte(HEX[(Int_dec/10000)%10]);
	Uart1_SendByte(HEX[(Int_dec/1000)%10]);
	Uart1_SendByte(HEX[(Int_dec/100)%10]);
	Uart1_SendByte(HEX[(Int_dec/10)%10]);
	Uart1_SendByte(HEX[(Int_dec/1)%10]);
}
void Uart1_dbg_print(char *str)
{
	while(*str)
	{
		Uart1_SendByte(*str++);
	}
}
void Uart1_Timeticket(void)		//判断接收超时
{
	if(uart1.time_cnt)
	{
			uart1.time_cnt--;
			if(uart1.time_cnt==0)
			{
				uart1.rev_flg=1;	//超过接收时限，标记为接收成功
			}
	}
}
void Uart1_Receive_Data(u8 rdata)
{
	if(uart1.rev_flg==0)
	{
		if(uart1.length<UART1_MAX_RECV_LEN)
		{
			uart1.time_cnt=UART1_BYTE_MAX_TIME;	//清零超时
			uart1.rbuf[uart1.length++]=rdata;	//保存数据
		}
		else
		{
			uart1.rev_flg=1;	//超过数据接收的长度，强制标记
		}
	}
}
#endif
/*********************************************************
* Function Name  : Uart2_Init
* Description    : 串口2初始化程序，用于打印消息
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
#ifdef	USING_UART2
_UART2_CTRL_DEF uart2;

void Uart2_Init(void)
{
	/*uart2.length=0;
	uart2.rev_flg=0;
	uart2.time_cnt=0;
	CLK_PeripheralClockConfig(CLK_Peripheral_USART2,ENABLE);

	//stm8l151c8
	GPIO_Init(GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_High_Fast);	//TXD
	GPIO_Init(GPIOE,GPIO_Pin_3,GPIO_Mode_In_FL_No_IT);	//RXD
	
	GPIO_Init(RS485_DR_PORT,RS485_DR_PIN,GPIO_Mode_Out_PP_High_Fast);	//RS485_DR
	
	USART_DeInit(USART2);
	USART_Init(USART2,(u32)UART2_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Rx|USART_Mode_Tx));
	USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2,ENABLE);*/

    uart2.length=0;
    uart2.rev_flg=0;
    uart2.time_cnt=0;

    CLK_PeripheralClockConfig(CLK_Peripheral_USART2,ENABLE);

    GPIO_Init(GPIOE,GPIO_Pin_4,GPIO_Mode_Out_PP_High_Fast);	//TXD	//< USART1 Tx- Rx (PC3- PC2)
    GPIO_Init(GPIOE,GPIO_Pin_3,GPIO_Mode_In_FL_No_IT);	//RXD

    USART_DeInit(USART2);
    USART_Init(USART2,(u32)UART2_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Rx|USART_Mode_Tx));
    USART_ITConfig(USART2,USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2,ENABLE);

}
void Uart2_SendByte(u8 c)
{
	while ((USART2->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART2,(u8)c);
}
void Uart2_Send_N_bytes(u8 *buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart2_SendByte(buf[i]);
	}
}
void Uart2_Send_Hex(u8 Byte_HEX)
{
	Uart2_SendByte(HEX[Byte_HEX/16]);
	Uart2_SendByte(HEX[Byte_HEX%16]);
}
void Uart2_Send_Dec(u8 Byte_Dec)
{
	Uart2_SendByte(HEX[(Byte_Dec/100)%10]);
	Uart2_SendByte(HEX[(Byte_Dec/10)%10]);
	Uart2_SendByte(HEX[(Byte_Dec/1)%10]);
}
void Uart2_Send_IntDec(u16 Int_dec)
{
	Uart2_SendByte(HEX[(Int_dec/10000)%10]);
	Uart2_SendByte(HEX[(Int_dec/1000)%10]);
	Uart2_SendByte(HEX[(Int_dec/100)%10]);
	Uart2_SendByte(HEX[(Int_dec/10)%10]);
	Uart2_SendByte(HEX[(Int_dec/1)%10]);
}
void Uart2_dbg_print(char *str)
{
	while(*str)
	{
		Uart2_SendByte(*str++);
	}
}
void Uart2_Timeticket(void)		//判断接收超时
{
	if(uart2.time_cnt)
	{
			uart2.time_cnt--;
			if(uart2.time_cnt==0)
			{
				uart2.rev_flg=1;	//超过接收时限，标记为接收成功
			}
	}
}
void Uart2_Receive_Data(u8 rdata)
{
	if(uart2.rev_flg==0)
	{
		if(uart2.length<UART2_MAX_RECV_LEN)
		{
			uart2.time_cnt=UART2_BYTE_MAX_TIME;	//清零超时
			uart2.rbuf[uart2.length++]=rdata;	//保存数据
		}
		else
		{
			uart2.rev_flg=1;	//超过数据接收的长度，强制标记
		}
	}
}
#endif
/*******************************************************************************
* Function Name  : Uart3_Init
* Description    : 串口3初始化
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
#ifdef	USING_UART3
_UART3_CTRL_DEF uart3;

void Uart3_Init(void)
{
	uart3.length=0;
	uart3.rev_flg=0;
	uart3.time_cnt=0;
	CLK_PeripheralClockConfig(CLK_Peripheral_USART3,ENABLE);

	//stm8l151c8
	GPIO_Init(GPIOE,GPIO_Pin_6,GPIO_Mode_Out_PP_High_Fast);	//TXD
	GPIO_Init(GPIOE,GPIO_Pin_7,GPIO_Mode_In_PU_No_IT);	//RXD

	USART_DeInit(USART3);
	USART_Init(USART3,(u32)UART3_BAUDRATE, USART_WordLength_8b, USART_StopBits_1, USART_Parity_No, (USART_Mode_TypeDef)(USART_Mode_Rx|USART_Mode_Tx));
	USART_ITConfig(USART3,USART_IT_RXNE, ENABLE);
	USART_Cmd(USART3,ENABLE);

}
void Uart3_SendByte(u8 c)
{
	while ((USART3->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART3,(u8)c);

}
void Uart3_Send_N_bytes(u8 *buf,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		Uart3_SendByte(buf[i]);
	}
}

void Uart3_Send_Hex(u8 Byte_HEX)
{
	Uart3_SendByte(HEX[Byte_HEX/16]);
	Uart3_SendByte(HEX[Byte_HEX%16]);
}
void Uart3_Send_Dec(u8 Byte_Dec)
{
	Uart3_SendByte(HEX[(Byte_Dec/100)%10]);
	Uart3_SendByte(HEX[(Byte_Dec/10)%10]);
	Uart3_SendByte(HEX[(Byte_Dec/1)%10]);
}
void Uart3_Send_IntDec(u16 Int_dec)
{
	Uart3_SendByte(HEX[(Int_dec/10000)%10]);
	Uart3_SendByte(HEX[(Int_dec/1000)%10]);
	Uart3_SendByte(HEX[(Int_dec/100)%10]);
	Uart3_SendByte(HEX[(Int_dec/10)%10]);
	Uart3_SendByte(HEX[(Int_dec/1)%10]);
}
void Uart3_dbg_print(char *str)
{
	while(*str)
	{
		Uart3_SendByte(*str++);
	}
}
void Uart3_Timeticket(void)		//判断接收超时
{
	if(uart3.time_cnt)
	{
			uart3.time_cnt--;
			if(uart3.time_cnt==0)
			{
				uart3.rev_flg=1;	//超过接收时限，标记为接收成功
			}
	}
}
void Uart3_Receive_Data(u8 rdata)
{
	if(uart3.rev_flg==0)
	{
		if(uart3.length<UART3_MAX_RECV_LEN)
		{
			uart3.time_cnt=UART3_BYTE_MAX_TIME;	//清零超时
			uart3.rbuf[uart3.length++]=rdata;	//保存数据
		}
		else
		{
			uart3.rev_flg=1;	//超过数据接收的长度，强制标记
		}
	}
}
#endif

/****************************************************************
* Function Name  : None
* Description    :None
* Input          : None
* Output         : None
* Return         : None
*****************************************************************/
#ifdef	UART1_DBG_PRINT
int putchar(int c)	//使用串口1作为打印口
{
	while ((USART1->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART1,(u8)c);
	return (c);
}
#endif

#ifdef	UART2_DBG_PRINT
int putchar(int c)	//使用串口2作为打印口
{
	while ((USART2->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART2,(u8)c);
	return (c);
}
#endif
#ifdef	UART3_DBG_PRINT
int putchar(int c)	//使用串口3作为打印口
{
	while ((USART3->SR&USART_SR_TXE)==RESET);
	USART_SendData8(USART3,(u8)c);
	return (c);
}
#endif
#ifdef	DUART_DBG_PRINT
int putchar(int c)	//使用串口模拟作为打印口
{
	if(debug_flg==0)
	{
		Uart_Send_Byte(c);
	}
	else
	{
		while ((USART3->SR&USART_SR_TXE)==RESET);
		USART_SendData8(USART3,(u8)c);
	}
	return (c);
}
#endif



/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Uart_Init(void)
{
#ifdef USING_UART1
	Uart1_Init();
#endif
#ifdef USING_UART2
	Uart2_Init();
#endif
#ifdef USING_UART3
	Uart3_Init();
#endif
#ifdef USING_DUART
	Uart_Debug_Init();		//如果串口不够用时，可以使用此模拟串口进行消息打印
#endif
}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Uart_Timeticket(void)
{
#ifdef	USING_UART1
	Uart1_Timeticket();
#endif
#ifdef	USING_UART2
	Uart2_Timeticket();
#endif
#ifdef	USING_UART3
	Uart3_Timeticket();
#endif
}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
void Print_System_Info(void)
{
	c_dbg_print((char *)Product_Info);      //打印产品信息
	c_dbg_print("Ver: %s\r\n",Software_Ver);       //软件版本
	c_dbg_print("DATE: %s\r\n",__DATE__);        //软件编译日期和时间
	c_dbg_print("TIME: %s\r\n",__TIME__);
}
/*********************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************/
