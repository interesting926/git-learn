#ifndef __SC09A_H_
#define __SC09A_H_

#include "stm8l15x.h"
#include "stm8l15x_gpio.h"

/*    
#define   SDA_OUT_OR_IN     TRISAbits.TRISA0
#define   SCL_OUT_OR_IN     TRISAbits.TRISA2
#define   SDA               LATAbits.LATA0
#define   SDA_IN            PORTAbits.RA0
#define   SCL               LATAbits.LATA2
#define   SC09A_ADDR        0x80  */

#define CON_ADDR 0x80 // {A[6:0] + RWB} = 81H

#define KEY_SDA_PORT GPIOF
#define KEY_SDA_PIN GPIO_Pin_1

#define KEY_SCL_PORT GPIOF
#define KEY_SCL_PIN GPIO_Pin_0


 
#define KEY_INT_PORT GPIOB
#define KEY_INT_PIN GPIO_Pin_0

#define KEY_SCL_H GPIO_SetBits(KEY_SCL_PORT, KEY_SCL_PIN)
#define KEY_SCL_L GPIO_ResetBits(KEY_SCL_PORT, KEY_SCL_PIN)

#define KEY_INT_H GPIO_SetBits(KEY_INT_PORT, KEY_INT_PIN)
#define KEY_INT_L GPIO_ResetBits(KEY_INT_PORT, KEY_INT_PIN)

#define KEY_SDA_OUTPUT GPIO_Init(KEY_SDA_PORT, KEY_SDA_PIN, GPIO_Mode_Out_PP_High_Slow)
#define KEY_SDA_INPUT GPIO_Init(KEY_SDA_PORT, KEY_SDA_PIN, GPIO_Mode_In_PU_No_IT)
#define KEY_SDA_H GPIO_SetBits(KEY_SDA_PORT, KEY_SDA_PIN)
#define KEY_SDA_L GPIO_ResetBits(KEY_SDA_PORT, KEY_SDA_PIN)
//#define KEY_SDA  GPIO_ReadOutputDataBit(KEY_SDA_PORT, KEY_SDA_PIN)
#define KEY_SDA (KEY_SDA_PORT->IDR & GPIO_Pin_1)


    
void Delay(unsigned char  time);  
void  I2C_Start(void);
unsigned char SendByteAndGetNACK(unsigned char dataToSend);
void I2C_Respond(unsigned char ACKSignal);
void I2C_Stop();
unsigned int I2C_Receive16Bit(void);
void I2C_ReadDeviceDataTo(unsigned char deviceAddr, unsigned int *target, unsigned char lengthOfData);
void key_int_handler(void);


void KEY_GPIO_INIT(void);
//unsigned int ReadKey(void);
void key_gpio_tset(void);
void addr_test(void);
void gpio_test(void);



#endif


