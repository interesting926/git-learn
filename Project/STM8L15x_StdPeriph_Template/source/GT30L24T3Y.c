#include "GT30L24T3Y.h"
#include "stm8l15x_gpio.h"



#define FONTIC_PORT GPIOB
#define FONT_CS_PIN GPIO_Pin_4
#define FONT_SCLK_PIN GPIO_Pin_5
#define FONT_MISO_PIN GPIO_Pin_6
#define FONT_MOSI_PIN GPIO_Pin_7




#if 1
#define Rom_csH	 GPIO_SetBits(FONTIC_PORT,FONT_CS_PIN)	
#define Rom_csL  GPIO_ResetBits(FONTIC_PORT,FONT_CS_PIN)	
#define MOSIH 	 GPIO_SetBits(FONTIC_PORT,FONT_MOSI_PIN)	
#define MOSIL 	 GPIO_ResetBits(FONTIC_PORT,FONT_MOSI_PIN)	
#define Rom_sckH GPIO_SetBits(FONTIC_PORT,FONT_SCLK_PIN)	
#define Rom_sckL GPIO_ResetBits(FONTIC_PORT,FONT_SCLK_PIN)
#define MISO	 GPIO_ReadInputDataBit(FONTIC_PORT, FONT_MISO_PIN)
#endif



void Font_Ic_GPIO_Init(void)
{

    GPIO_Init(FONTIC_PORT, FONT_CS_PIN, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(FONTIC_PORT, FONT_SCLK_PIN, GPIO_Mode_Out_PP_Low_Slow);
    GPIO_Init(FONTIC_PORT, FONT_MISO_PIN, GPIO_Mode_In_FL_No_IT);
    GPIO_Init(FONTIC_PORT, FONT_MOSI_PIN, GPIO_Mode_Out_PP_Low_Slow);

}



void zk_init(void)
{
  Rom_csH;
  MOSIH;
  Rom_sckH;
}

/*******************************************************************************/
// Send data sub-pro (STM8,STM32��˫���)   SPI���͵�ַ��ʱ���㷨               /
/*******************************************************************************/

void Send_Byte(unsigned char out)
{	
	unsigned char i=0;

	for(i=0;i<8;i++)
	{
	  Rom_sckL;  //�ֿ�оƬʱ���õ�
	  if(((out<<i)&0x80)==0)
		  MOSIL;   
	  else
		  MOSIH;
	  Rom_sckH;
  }
}
 
/*******************************************************************************/
// Get data sub-pro (STM8,STM32��˫���)    SPI���յ������ݵ��㷨               /
/*******************************************************************************/
unsigned char Get_Byte(void)         
{
	unsigned char i;
	unsigned char read_dat;

	Rom_sckH;
	for(i=0;i<8;i++)
	{
		Rom_sckL;
		read_dat=read_dat<<1;
		if(MISO)				
			read_dat|=0x01;
		else
			read_dat&=0xfe;
		Rom_sckH;
	}
	return(read_dat);
}
/*******************************************************************************/
//                    Send address sub-pro (STM8,STM32��51)                                     /
/*******************************************************************************/
void SPI_Address(unsigned char AddH,unsigned char AddM,unsigned char AddL) 
{
	Send_Byte(AddH);
	Send_Byte(AddM);
	Send_Byte(AddL);
}
/*******************************************************************************/
//                    Get N bytes sub-pro  (STM8,STM32��51)                                    //
/*******************************************************************************/
//�ͻ��Լ�ʵ�֣���address��ַ��ȡlen���ֽڵ����ݲ����뵽DZ_Data���鵱��
unsigned char r_dat_bat(unsigned long address,unsigned long DataLen,unsigned char *pBuff)
{
    unsigned long i;
    unsigned char addrHigh;
    unsigned char addrMid;
    unsigned char addrLow;
    addrHigh=address>>16;
    addrMid=address>>8;
    addrLow=(unsigned char)address;

    Rom_csL;          //Ƭѡѡ���ֿ�оƬ
    Send_Byte(0x03);	//��ͨ��ȡ������0X03,Ȼ���͵�ַ�߰�λaddrHigh���а�λaddrMid���Ͱ�λaddrLow��
    SPI_Address(addrHigh,addrMid,addrLow);	
    for(i=0;i<DataLen;i++)
    *(pBuff+i)=Get_Byte();
    Rom_csH;
    return 0;
}

//�ͻ��Լ�ʵ�֣���address��ַ��ȡһ���ֽڵ����ݲ����ظ�����
unsigned char r_dat(u32 address){
	unsigned char buff;
	unsigned char addrHigh;
	unsigned char addrMid;
	unsigned char addrLow;
	addrHigh=address>>16;
	addrMid=address>>8;
	addrLow=(unsigned char)address;
	
	Rom_csL;
	Send_Byte(0x03);
	SPI_Address(addrHigh,addrMid,addrLow);
	buff = Get_Byte();
	Rom_csH;
	return buff;
}

/******************************************************
�ͻ��Լ�ʵ��, ���ļ������ڲ���Ҫ���øú���ƥ��оƬID��
����˵���ļ���ͷ�ļ��Ƿ���Ҫ, û�оͲ���Ҫʵ��
******************************************************/
unsigned char CheckID(unsigned char CMD, unsigned long address,
	unsigned long byte_long,unsigned char *p_arr)
{
	unsigned long j;
	Rom_csL;
	Send_Byte(CMD);
	Send_Byte((unsigned char)((address)>>16)); 
	Send_Byte((unsigned char)((address)>>8));   
	Send_Byte((unsigned char)address); 
	for(j=0;j<byte_long;j++)
	{
			p_arr[j]=Get_Byte();
	}
	Rom_csH;
	return 1;
}



















