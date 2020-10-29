/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/
#include	"main.h"
#include "stm8l15x.h"
#include	"timer.h"
#include "kill.h"
#include	"lcd.h"
#include "JLX256160G.h"
#include "SC09A.h"


u8 INT_FLG;
char const Product_Info[]={"\
************************************************************\r\n\
Company: Forlinux Technoly Electronics Co.,LTD.\r\n\
Project: GFamily Software\r\n\
Author: Fuqiaobin\r\n\
Date:	2018.11.16\r\n\
************************************************************\r\n"};
/*******************************************************************************
* Function Name  : SysClock_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void SysClock_Init(void)
{
	CLK_DeInit();
	CLK_SYSCLKSourceConfig(CLK_SYSCLKSource_HSI);
	CLK_SYSCLKDivConfig(CLK_SYSCLKDiv_1);
	CLK_HSICmd(ENABLE);
}
/*******************************************************************************
* Function Name  : Hard_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void Hard_Init(void)
{
	GPIO_DeInit(GPIOA);
	GPIO_DeInit(GPIOB);
	GPIO_DeInit(GPIOC);
	GPIO_DeInit(GPIOD);
	GPIO_DeInit(GPIOE);
	GPIO_DeInit(GPIOF);
	GPIO_DeInit(GPIOG);
	Ht1621_Port_Init();
	
	GPIO_Init(DB_POWER_PORT,DB_POWER_PIN,GPIO_Mode_Out_PP_High_Fast);	//DB_POWER
	DB_POWER_HIG();
	
	//GPIO_Init(BLE_WAKUP_PORT,BLE_WAKUP_PIN,GPIO_Mode_Out_PP_High_Fast);	//WAKEUP
	//GPIO_Init(BLE_CONNECT_PORT,BLE_CONNECT_PIN,GPIO_Mode_In_PU_No_IT);	//connect
	//GPIO_Init(BLE_RST_PORT,BLE_RST_PIN,GPIO_Mode_Out_OD_HiZ_Fast);	//RST
	//GPIO_Init(BLE_INT_PORT,BLE_INT_PIN,GPIO_Mode_In_PU_No_IT);	//INT
	
	GPIO_Init(Led1_Port,Led1_Pin,GPIO_Mode_Out_OD_HiZ_Fast);	//开漏输出
	GPIO_Init(Beep_Port,Beep_Pin,GPIO_Mode_Out_OD_HiZ_Fast);
	LED_Display(100);
	
}
/*******************************************************************************
* Function Name  : Exti_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void Exti_Init(void)
{
	EXTI_DeInit();
	EXTI_SetPinSensitivity(EXTI_Pin_1,EXTI_Trigger_Falling);
	EXTI_SetPinSensitivity(EXTI_Pin_2,EXTI_Trigger_Falling);
	ITC_SetSoftwarePriority(EXTI1_IRQn,ITC_PriorityLevel_3);	//优先级
	ITC_SetSoftwarePriority(EXTI2_IRQn,ITC_PriorityLevel_3);	//优先级
}
/*******************************************************************************
* Function Name  : Soft_Init
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void Soft_Init(void)
{
	sport.start=1;
	sport.resume=0;
	sport.level=1;
	sport.loader=1;
	timer.total_time=0;
	power.time_cnt=TIMEOUT_MAX;	// 10分钟
}

/*******************************************************************************
* Function Name  : main
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/
void main(void)
{
	
  disableInterrupts();INT_FLG=0;
	SysClock_Init();
	Hard_Init();
	delay_ms(100);
	ADC_Config();
	HR_INT_Init();
	RPM_INT_Init();
	Uart_Init();
	Timer_Init();
	Exti_Init();
	Kill_Init();
    lcd_Init();
	Ultra_Power_Init();
    KEY_GPIO_INIT();
    key_gpio_tset();
	Soft_Init();
	Beep_Ring(50);
	Print_System_Info();
	c_dbg_print("System Init is OK!\r\n");
	enableInterrupts();INT_FLG=1;
  while (1)
  {    
		Key_Scan_Handler();
		Function();
  }
}
/*******************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*********************************************************************************/

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
		delay_ms(1000);
		printf("Wrong parameters value: file %s on line %d\r\n", file, (u16)line);
  }
}
#endif

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
