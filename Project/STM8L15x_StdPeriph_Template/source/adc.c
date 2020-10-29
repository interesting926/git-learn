/*-----------------------------------------------
  项目：Smart Demo 程序
  论坛：www.forlinux.com
  作者：Fuqiaobin
  日期：2017.12.30
  版本: V1.0
  注意事项：V1.0:  初版  晶振: 16M内部晶振
------------------------------------------------*/


#include "adc.h"
#include "stm8l15x_adc.h"
#include	"uart.h"



_ADC_CTRL_DEF_ adc;

/*****************************************************************************
* Function Name  : WatchDog_Init
* Description    : 看门狗初始化程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void ADC_Config(void)
{
	u8 i;


  GPIO_Init(BAT1_VOLTAGE_PORT, BAT1_VOLTAGE_PIN, GPIO_Mode_In_FL_No_IT);	//VOLTAGE BAT1
  GPIO_Init(BAT1_CURRENT_PORT, BAT1_CURRENT_PIN, GPIO_Mode_In_FL_No_IT);	//CURRENT BAT1
  GPIO_Init(BAT1_CHARGE_PORT, BAT1_CHARGE_PIN, GPIO_Mode_Out_PP_High_Fast);	//CHARGE BAT1
	
  GPIO_Init(BAT2_VOLTAGE_PORT, BAT2_VOLTAGE_PIN, GPIO_Mode_In_FL_No_IT);	//VOLTAGE BAT2
  GPIO_Init(BAT2_CURRENT_PORT, BAT2_CURRENT_PIN, GPIO_Mode_In_FL_No_IT);	//CURRENT BAT2
  GPIO_Init(BAT2_CHARGE_PORT, BAT2_CHARGE_PIN, GPIO_Mode_Out_PP_High_Fast);	//CHARGE BAT2

  CLK_PeripheralClockConfig(CLK_Peripheral_ADC1,ENABLE);
  ADC_DeInit(ADC1);
  ADC_Init(ADC1,ADC_ConversionMode_Single, ADC_Resolution_10Bit,ADC_Prescaler_2);
  ADC_Cmd(ADC1,ENABLE);
 // ADC_ChannelCmd(ADC1,BAT1_VOLTAGE_CHANNEL,ENABLE);
 // ADC_ChannelCmd(ADC1,BAT1_CURRENT_CHANNEL,ENABLE);
 // ADC_ChannelCmd(ADC1,BAT2_VOLTAGE_CHANNEL,ENABLE);
 // ADC_ChannelCmd(ADC1,BAT2_CURRENT_CHANNEL,ENABLE); 
  ADC_SamplingTimeConfig(ADC1,ADC_Group_SlowChannels,ADC_SamplingTime_384Cycles);
  ADC_SamplingTimeConfig(ADC1,ADC_Group_FastChannels,ADC_SamplingTime_384Cycles);
  ADC_VrefintCmd(DISABLE);
  ADC_DMACmd(ADC1,DISABLE);
  //ADC_SchmittTriggerConfig(ADC1,BAT1_CURRENT_CHANNEL,DISABLE);
  ADC_ITConfig(ADC1,ADC_IT_EOC,DISABLE);
  ADC_ClearFlag(ADC1,ADC_FLAG_EOC);

  adc.init = 0;
  adc.index = 0;
  for(i=0;i<SAMP_MAX;i++)
  {
	  adc.bat1_currbuff[i]=0;
	  adc.bat1_voltbuff[i]=0;
	  adc.bat2_currbuff[i]=0;
	  adc.bat2_voltbuff[i]=0;
  }
  adc.full_flg=0;	//上电默认电池未满
	adc.step=0;
	adc.bat_lev=1;

}

void ADC_Timeticket(void)
{
	if(adc.time_cnt) adc.time_cnt--;
	if(adc.bat_time) adc.bat_time--;
}
void ADC_ClearChannel(void)
{
  ADC1->SQR[0] =  ADC_SQR1_RESET_VALUE;
  ADC1->SQR[1] =  ADC_SQR2_RESET_VALUE;
  ADC1->SQR[2] =  ADC_SQR3_RESET_VALUE;
  ADC1->SQR[3] =  ADC_SQR4_RESET_VALUE;
}
/*****************************************************************************
* Function Name  : WatchDog_Init
* Description    : 看门狗初始化程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
#pragma optimize= none
void ADC_Serv_Handler(void)
{
    u16 Adc_Value,voltage,current;
    if(adc.time_cnt==0)     //降低频率
    {
        adc.time_cnt=100;
				//BAT1 VOLTAGE
		ADC_ChannelCmd(ADC1,BAT1_VOLTAGE_CHANNEL,ENABLE);
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
        Adc_Value = ADC_GetConversionValue(ADC1);
        adc.bat1_voltbuff[adc.index]=Adc_Value;
        ADC_ClearChannel();

				//BAT1 CURRENT
		ADC_ChannelCmd(ADC1,BAT1_CURRENT_CHANNEL,ENABLE);
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
        Adc_Value = ADC_GetConversionValue(ADC1);
        adc.bat1_currbuff[adc.index]=Adc_Value;
		ADC_ClearChannel();

				//BAT2 VOLTAGE
		ADC_ChannelCmd(ADC1,BAT2_VOLTAGE_CHANNEL,ENABLE);
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
        Adc_Value = ADC_GetConversionValue(ADC1);
        adc.bat2_voltbuff[adc.index]=Adc_Value;
		ADC_ClearChannel();

        //BAT2 CURRENT
		ADC_ChannelCmd(ADC1,BAT2_CURRENT_CHANNEL,ENABLE);
        ADC_SoftwareStartConv(ADC1);
        while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC)==RESET);
        ADC_ClearFlag(ADC1,ADC_FLAG_EOC);
        Adc_Value = ADC_GetConversionValue(ADC1);
        adc.bat2_currbuff[adc.index]=Adc_Value;
		ADC_ClearChannel();
				
        adc.index++;
        if(adc.index>=SAMP_MAX)
        {
            adc.index = 0;
            adc.init= 1; //填满32个字节表明已经初始化
        }
        
        if(adc.init)
        {
            voltage=ADC_Get_Average(adc.bat1_voltbuff,SAMP_MAX)+1;   //平均值
            adc.bat1_volt=(u16)(((u32)voltage*331*25)/(10*1024));
            //c_dbg_print("ADC bat1_volt: %d-%.1fV\t",adc.bat1_volt,(float)adc.bat1_volt/10);
            
            current=ADC_Get_Average(adc.bat1_currbuff,SAMP_MAX)+1;   //平均值
       			adc.bat1_curr= (u16)(((u32)current*331*1)/1024);	// 电流，0.1A为单位
            //c_dbg_print("bat1_curr: %d-%.1fA\t",adc.bat1_curr,(float)adc.bat1_curr/10);
			//			c_dbg_print("\r\n");

            voltage=ADC_Get_Average(adc.bat2_voltbuff,SAMP_MAX)+1;   //平均值
            adc.bat2_volt=(u16)(((u32)voltage*331*25)/(10*1024));
            //c_dbg_print("bat2_volt: %d-%.1fV\t",adc.bat2_volt,(float)adc.bat2_volt/10);
            
			current=ADC_Get_Average(adc.bat2_currbuff,SAMP_MAX)+1;	 //平均值
			adc.bat2_curr= (u16)(((u32)current*331*1)/1024);	// 电流，0.1A为单位
			//c_dbg_print("bat2_curr: %d-%.1fA\r\n",adc.bat2_curr,(float)adc.bat2_curr/10);

			if(adc.bat_time==0)
			{
				adc.bat_time=300;
				if(adc.bat1_volt>=140)	//电压过高
				{
					adc.full_flg=1;
					BAT1_CHARGE_OFF();
					//c_dbg_print("[BAT] bat1 is fulled!Stop Charge\r\n");
				}
				else if(adc.bat1_volt<=125)	//电压过低
				{
					adc.full_flg=0;
					BAT1_CHARGE_ON();
					//c_dbg_print("[BAT] bat1 is empty!Charge!\r\n");
				}
				else	//过程
				{
					if(adc.full_flg==0)	//充电过程
					{
						BAT1_CHARGE_ON();
						//c_dbg_print("[BAT] Charge!\r\n");
					}
					else	//放电过程
					{
						BAT1_CHARGE_OFF();
						//c_dbg_print(">");
					}
				}
			}
			if(adc.bat1_volt>=138) adc.bat_lev=6;
			else if(adc.bat1_volt>=132) adc.bat_lev=5;
			else if(adc.bat1_volt>=128) adc.bat_lev=4;
			else if(adc.bat1_volt>=120) adc.bat_lev=3;
			else if(adc.bat1_volt>=108) adc.bat_lev=2;
			else  adc.bat_lev=1;
        }
    }
    /*
    if(adc.init)
    {
	    switch(adc.step)
	    {
				case 0:	//判断
				{
					if(adc.bat_time==0)
					{
						adc.bat_time=100;
						if(adc.bat1_volt>142)	//电压过高
						{
							adc.full_flg=1;
							BAT1_CHARGE_OFF();
							c_dbg_print("[BAT] bat1 is fulled!\r\n");
						}
						else if(adc.bat1_volt<125)	//电压过低
						{
							adc.full_flg=0;
							adc.step=1;
							adc.bat_time=CHARG_TIME;
							BAT1_CHARGE_ON();
							c_dbg_print("[BAT] bat1 <12.5V!\r\n");
							c_dbg_print("[BAT] Charge!\r\n");
						}
						else	//过程
						{
							if(adc.full_flg==0)	//充电过程
							{
								adc.step=1;
								adc.bat_time=CHARG_TIME;
								BAT1_CHARGE_ON();
								c_dbg_print("[BAT] Charge!\r\n");
							}
							else	//放电过程
							{
								BAT1_CHARGE_OFF();
								c_dbg_print(">");
							}
						}
					}
					
					if(adc.bat1_volt>=142) adc.bat_lev=6;
					else if(adc.bat1_volt>=135) adc.bat_lev=5;
					else if(adc.bat1_volt>=128) adc.bat_lev=4;
					else if(adc.bat1_volt>=121) adc.bat_lev=3;
					else if(adc.bat1_volt>=108) adc.bat_lev=2;
					else  adc.bat_lev=1;
					
				}break;
				case 1:	//进行充电
				{
					if(adc.bat_time==0)	//充电完成
					{
						adc.step=2;
						adc.bat_time=RELEASE_TIME;
						BAT1_CHARGE_OFF();
						c_dbg_print("[BAT] Charge Release!\r\n");
					}
				}break;			
				case 2:
				{
					if(adc.bat_time==0)	//充电完成
					{
						adc.step=0;
						adc.bat_time=0;
						BAT1_CHARGE_OFF();
						c_dbg_print("[BAT] Charge ok!\r\n");
					}
				}break;
				default:break;
	    }
	}
	*/
}


/*****************************************************************************
* Function Name  : WatchDog_Init
* Description    : 看门狗初始化程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
u16 ADC_Get_Average(u16 *pt, u8 len)
{
	u8 i;
	u16 sum;
	sum= 0;
	for(i=0;i<len; ++i)
	{
		sum+= *pt;
		pt++;
	}
	return sum / len;
}

/*****************************************************************************
* Function Name  : WatchDog_Init
* Description    : 看门狗初始化程序
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/











