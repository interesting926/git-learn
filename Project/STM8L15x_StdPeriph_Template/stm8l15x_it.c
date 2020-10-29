/**
  ******************************************************************************
  * @file    Project/STM8L15x_StdPeriph_Template/stm8l15x_it.c
  * @author  MCD Application Team
  * @version V1.6.1
  * @date    30-September-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm8l15x_it.h"
#include	"timer.h"
#include	"ds1302.h"
#include "kill.h"
#include "stm8l15x_usart.h"
#include "SC09A.h"



/** @addtogroup STM8L15x_StdPeriph_Template
  * @{
  */
	
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

#ifdef _COSMIC_
/**
  * @brief Dummy interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER(NonHandledInterrupt,0)
{

}
#endif

/**
  * @brief TRAP interrupt routine
  * @par Parameters:
  * None
  * @retval 
  * None
*/
INTERRUPT_HANDLER_TRAP(TRAP_IRQHandler)
{

}
/**
  * @brief FLASH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(FLASH_IRQHandler,1)
{

}
/**
  * @brief DMA1 channel0 and channel1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL0_1_IRQHandler,2)
{

}
/**
  * @brief DMA1 channel2 and channel3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(DMA1_CHANNEL2_3_IRQHandler,3)
{

}
/**
  * @brief RTC / CSS_LSE Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(RTC_CSSLSE_IRQHandler,4)
{

}
/**
  * @brief External IT PORTE/F and PVD Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIE_F_PVD_IRQHandler,5)
{

}

/**
  * @brief External IT PORTB / PORTG Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTIB_G_IRQHandler,6)
{

}

/**
  * @brief External IT PORTD /PORTH Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTID_H_IRQHandler,7)
{

}

/**
  * @brief External IT PIN0 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI0_IRQHandler,8)
{
    if(EXTI_GetITStatus(EXTI_IT_Pin0)!=RESET)
	{
        HR_INT_Routine();
		EXTI_ClearITPendingBit(EXTI_IT_Pin0);
	}       
}

/**
  * @brief External IT PIN1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI1_IRQHandler,9)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin1)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin1);
	}
}

/**
  * @brief External IT PIN2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI2_IRQHandler,10)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin2)!=RESET)
	{
		RPM_INT_Routine();
		EXTI_ClearITPendingBit(EXTI_IT_Pin2);
	}
}

/**
  * @brief External IT PIN3 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI3_IRQHandler,11)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin3)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin3);
	}
}

/**
  * @brief External IT PIN4 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI4_IRQHandler,12)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin4)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin4);
	}
}

/**
  * @brief External IT PIN5 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI5_IRQHandler,13)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin5)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin5);
	}
}

/**
  * @brief External IT PIN6 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI6_IRQHandler,14)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin6)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin6);
	}
    //IR_Rev_Handler();
}

/**
  * @brief External IT PIN7 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(EXTI7_IRQHandler,15)
{
	if(EXTI_GetITStatus(EXTI_IT_Pin7)!=RESET)
	{
		EXTI_ClearITPendingBit(EXTI_IT_Pin7);
	}
}
/**
  * @brief LCD /AES Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(LCD_AES_IRQHandler,16)
{

}
/**
  * @brief CLK switch/CSS/TIM1 break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SWITCH_CSS_BREAK_DAC_IRQHandler,17)
{

}

/**
  * @brief ADC1/Comparator Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(ADC1_COMP_IRQHandler,18)
{

}

/**
  * @brief TIM2 Update/Overflow/Trigger/Break /USART2 TX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_UPD_OVF_TRG_BRK_USART2_TX_IRQHandler,19)	// 10ms
{
	if(TIM2_GetITStatus(TIM2_IT_Update)!=RESET)
	{
		TIM2_ClearITPendingBit(TIM2_IT_Update);
		System_Timeticket();	
		//Display_Timeticket();	
		Uart_Timeticket();	
		Key_Time_Handler();
		ADC_Timeticket();
		//Ds1302_Time_Handler();
		Kill_SysTime_Tick();
		if(power.time_cnt) power.time_cnt--;
		if(sport.send_cnt) sport.send_cnt--;
		if(sport.send_cnt2)
		{
			sport.send_cnt2--;
			if(sport.send_cnt2==0)
			{
				sport.send_cnt2_flg=1;	//主要用于蓝牙第二包数据的发送
			}
		}		
		if(beep.time)
		{
			beep.time--;
			if(beep.time==0) Set_Beep_OFF();
		}
		if(ble.rst_time)
		{
			ble.rst_time--;
			if(ble.rst_time==0) BLE_RST_HIG();
		}
		if(led.time)
		{
			led.time--;
			if(led.time==0) Set_Led1_Off();
		}
		if(hr.time)
		{
			hr.time--;
			if(hr.time==0) hr.display_flg=0;
		}
        face_sport_timer_handler();



	}
    /* In order to detect unexpected events during development,
       it is recommended to set a breakpoint on the following instruction.
    */
}

/**
  * @brief Timer2 Capture/Compare / USART2 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM2_CC_USART2_RX_IRQHandler,20)
{
#ifdef	USING_UART2
 		u8 rdata; 
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
        rdata = USART_ReceiveData8(USART2);
				Uart2_Receive_Data(rdata);
    }
		else
		{
			rdata = USART_ReceiveData8(USART2);	//非接收中断时，需要通过接收来清除
		}
#endif
}


/**
  * @brief Timer3 Update/Overflow/Trigger/Break Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_UPD_OVF_TRG_BRK_USART3_TX_IRQHandler,21)
{
	if(TIM3_GetITStatus(TIM3_IT_Update)!=RESET)
	{
		TIM3_ClearITPendingBit(TIM3_IT_Update);





	}
}
/**
  * @brief Timer3 Capture/Compare /USART3 RX Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM3_CC_USART3_RX_IRQHandler,22)
{
#ifdef	USING_UART3
 		u8 rdata; 
    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
        rdata = USART_ReceiveData8(USART3);
				Uart3_Receive_Data(rdata);
    }
		else
		{
			rdata = USART_ReceiveData8(USART3);	//非接收中断时，需要通过接收来清除
		}
#endif
}
/**
  * @brief TIM1 Update/Overflow/Trigger/Commutation Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_UPD_OVF_TRG_COM_IRQHandler,23)
{
	if(TIM1_GetITStatus(TIM1_IT_Update)!=RESET)
	{
		TIM1_ClearITPendingBit(TIM1_IT_Update);





	}
}
/**
  * @brief TIM1 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM1_CC_IRQHandler,24)
{

}

/**
  * @brief TIM4 Update/Overflow/Trigger Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(TIM4_UPD_OVF_TRG_IRQHandler,25)
{
	if(TIM4_GetITStatus(TIM4_IT_Update)!=RESET)
	{
		TIM4_ClearITPendingBit(TIM4_IT_Update);
		HR_TimeTicket();	// 1ms
		RPM_TimeTicket();	// 1ms
	}
}
/**
  * @brief SPI1 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(SPI1_IRQHandler,26)
{
	
}

/**
  * @brief USART1 TX / TIM5 Update/Overflow/Trigger/Break Interrupt  routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_TX_TIM5_UPD_OVF_TRG_BRK_IRQHandler,27)
{

}

/**
  * @brief USART1 RX / Timer5 Capture/Compare Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(USART1_RX_TIM5_CC_IRQHandler,28)
{
#ifdef	USING_UART1
 		u8 rdata; 
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
    {
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        rdata = USART_ReceiveData8(USART1);
				Uart1_Receive_Data(rdata);
    }
		else
		{
			rdata = USART_ReceiveData8(USART1);	//非接收中断时，需要通过接收来清除
		}
#endif
}

/**
  * @brief I2C1 / SPI2 Interrupt routine.
  * @param  None
  * @retval None
  */
INTERRUPT_HANDLER(I2C1_SPI2_IRQHandler,29)
{

}
/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
