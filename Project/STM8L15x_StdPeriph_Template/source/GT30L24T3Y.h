
#ifndef _GT30L24T3Y_H_
#define _GT30L24T3Y_H_

#include <string.h>

void Font_Ic_GPIO_Init(void);
extern unsigned char r_dat_bat(unsigned long address,unsigned long ascii_kind,unsigned char *p_arr);

#define ASCII_5X7              1
#define ASCII_7X8              2
#define ASCII_6X12             3
#define ASCII_12_A             4 
#define ASCII_16_A             5 
#define ASCII_24_A             6
#define ASCII_8X16             7

unsigned char  ASCII_GetData(unsigned char ASCIICode,unsigned long ascii_kind,unsigned char *DZ_Data);
void gt_12_GetData (unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
void gt_16_GetData (unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
void gt_24_GetData (unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long GB12345_12_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long GB12345_16_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long GB12345_24_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long BIG5_12_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long BIG5_16_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long BIG5_24_GetData(unsigned char MSB,unsigned char LSB,unsigned char *DZ_Data);
unsigned long UniCodeHZ_12_GetData(unsigned int unicode,unsigned char *DZ_Data);
unsigned long UniCodeHZ_16_GetData(unsigned int unicode,unsigned char *DZ_Data);
unsigned long UniCodeHZ_24_GetData(unsigned int unicode,unsigned char *DZ_Data);

#endif
