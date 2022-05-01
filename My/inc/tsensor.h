#ifndef __TSENSOR_H
#define __TSENSOR_H	
#include "stm32f10x.h"

 		 
#define ADC_CH_TEMP  	ADC_Channel_16 //温度传感器通道
   
u16  T_Get_Temp(void);  //取得温度值
void T_Adc_Init(void); //ADC通道初始化
u16  T_Get_Adc(u8 ch); //获得某个通道值  
u16  T_Get_Adc_Average(u8 ch,u8 times);//得到某个通道10次采样的平均值 
u8 Chip_temp_Read(void); //
#endif 

