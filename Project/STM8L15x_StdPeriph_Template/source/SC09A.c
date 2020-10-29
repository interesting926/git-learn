//#include "stm8l15x_gpio.h"
#include "SC09A.h"
#include "timer.h"
#include "debug.h"





/*************************************************************************************
* Function Name  : None
* Description    : None
* Input          : None
* Output         : None
* Return         : None
*************************************************************************************/





 void Delay(unsigned char  time)
{
    unsigned char a;
    for(a = time; a>0; a--) delay_us(1);
}


void KEY_GPIO_INIT(void)
{
	GPIO_Init(KEY_SDA_PORT, KEY_SDA_PIN, GPIO_Mode_Out_PP_High_Slow);
	GPIO_Init(KEY_SCL_PORT, KEY_SCL_PIN, GPIO_Mode_Out_PP_High_Slow);
	GPIO_Init(KEY_INT_PORT, KEY_INT_PIN, GPIO_Mode_In_PU_IT);
    EXTI_SetPinSensitivity(EXTI_Pin_0,EXTI_Trigger_Falling);//key
    delay_ms(300);
}

void key_int_handler(void)
{
    power.time_cnt = TIMEOUT_MAX;

}


void key_gpio_tset(void)
{
  /*  GPIO_Init(KEY_SDA_PORT, KEY_SDA_PIN, GPIO_Mode_Out_PP_High_Slow);
    GPIO_Init(KEY_SCL_PORT, KEY_SCL_PIN, GPIO_Mode_Out_PP_High_Slow);
    KEY_SDA_OUTPUT;
    while(1)
    {
	    KEY_SDA_L;
        KEY_SCL_L;
        delay_ms(500);
        KEY_SDA_H;
        KEY_SCL_H;
        delay_ms(500);


    }
*/

}
void  I2C_Start(void)
{
    //SDA_OUT_OR_IN = 0;
    KEY_SDA_OUTPUT;
    //SCL_OUT_OR_IN = 0;
    // SDA = 1;
    //SCL = 1;
    KEY_SDA_H;
    KEY_SCL_H;
    Delay(1);
    //SDA = 0;
    KEY_SDA_L;
    Delay(1);
    // SCL = 0;
    KEY_SCL_L;
    Delay(1);

}


unsigned char SendByteAndGetNACK(unsigned char dataToSend)
{
    unsigned char i;
    unsigned char ack=0;
    //SDA_OUT_OR_IN = 0;
    KEY_SDA_OUTPUT;
    for (i = 0; i < 8; i++) {   
        //SCL = 0;
        KEY_SCL_L;
        Delay(1);
        if (dataToSend & 0x80) {
            //SDA =  1;
            KEY_SDA_H;
        }
        else {
            //SDA  =  0;
            KEY_SDA_L;
        }
        Delay(1);
        //SCL = 1;
        KEY_SCL_H;
        Delay(1);
        dataToSend <<= 1;
    }
    
    //SCL = 0;
    KEY_SCL_L;
    Delay(1);
    //SDA_OUT_OR_IN = 1;
    KEY_SDA_INPUT;
    Delay(1);
    //SCL = 1;
    KEY_SCL_H;
    Delay(2);  
    //ack =SDA_IN;
    ack=KEY_SDA;
    //SCL =  0; 
    KEY_SCL_L;
    Delay(1);                    
  // SDA_OUT_OR_IN = 0;
  //  SDA = 0;
    return (ack);
}



 void I2C_Respond(unsigned char ACKSignal)
{
    //SDA_OUT_OR_IN = 0;
    KEY_SDA_OUTPUT;
    // SDA =  0;
    KEY_SDA_L;
    //SCL = 0; 
    KEY_SCL_L;
    if (ACKSignal) {
      //SDA  = 1; 
      KEY_SDA_H;
    }
    else {
      //SDA =  0;
      KEY_SDA_L;
    }
	Delay(1);
    //SCL = 1;
    KEY_SCL_H;
    Delay(1);
    //SCL = 0;
    KEY_SCL_L;
}




 void I2C_Stop()
 {   
     //SCL =  0;
     KEY_SCL_L;
     //SDA_OUT_OR_IN = 0;
     KEY_SDA_OUTPUT;
     //SDA = 0;
     KEY_SDA_L;
     Delay(1);
     //SCL = 1;
     KEY_SCL_H;
     Delay(1);
     //SDA  = 1;
     KEY_SDA_H;
 }


unsigned int I2C_Receive16Bit(void)
{
     unsigned char i;
     unsigned int buffer;
     //SDA_OUT_OR_IN = 1;
     KEY_SDA_INPUT;
     for (i = 0; i < 16; i++) {   
        //SCL = 0;
        KEY_SCL_L;
        Delay(1);
        //SCL = 1;
        KEY_SCL_H;
        Delay(1);           
         //if (SDA_IN) { 
         if(KEY_SDA){
             buffer |= 0x01;
         }
         if (i < 15) {
             buffer <<= 1;
         }
     }
     //SCL = 0;
     KEY_SCL_L;
     //SDA_OUT_OR_IN = 1;
     KEY_SDA_OUTPUT;
     //SDA =  0;  
     KEY_SDA_L;
     return (buffer);
}


void I2C_ReadDeviceDataTo(unsigned char deviceAddr, unsigned int *target, unsigned char lengthOfData)
{
    unsigned char i; 
   // unsigned char dev;
    I2C_Start();                
    if (SendByteAndGetNACK(deviceAddr | 0x01)) {
	    *target = 0xFFFF;
        I2C_Stop(); 
        return;
    }   
    for (i = 0; i < lengthOfData; i++) {
        target[i] = I2C_Receive16Bit();
        if (i == (lengthOfData - 1))
            break;
        I2C_Respond(0);
    }
    I2C_Respond(1);
    I2C_Stop();           
}


void gpio_test(void)
{
    GPIO_Init(GPIOF,GPIO_Pin_1, GPIO_Mode_Out_PP_High_Slow);

}


void addr_test(void)
{
    unsigned char i;
    unsigned char ack;
    //char ok=0;
    while(1)
    {
        for(i=0;i<255;i++)
        {
            I2C_Start();        
            ack = SendByteAndGetNACK(0x81);
            if(ack == 0)
            {
    		  printf("ack ok");
                ack=1;
            }
            //delay_ms(20);
            delay_us(200);
        }
    }

}



