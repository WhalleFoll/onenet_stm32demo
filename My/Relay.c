/*-------------------------------------------------------------------------------
继电器
---------------------------------------------------------------------------------*/
#include "Relay.h"
#include "usart.h"
//extern u8 key,key2,key3,key4,key5,key6;


void Relay_Init(void)//继电器初始化
{
      GPIO_InitTypeDef GPIO_InitStructure;
	
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//打开PG口时钟	
	 	
	   	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//PE2,PE3,PE4引脚设置	   
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//端口速度	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//推挽输出
	  
	  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化对应的端口
				
}

void Setkey(void)//继电器操作
{
//	if(key==0)
//	{  key_OFF;	//off-关闭 0	
//	    UsartPrintf(USART_DEBUG, "key_OFF \r\n");
//	}
//	else
//	{	key_ON;    //on-打开 1
//	   UsartPrintf(USART_DEBUG, "key_ON \r\n");
//	}
//	
//	if(key2==0)
//	{key2_OFF;	
//        UsartPrintf(USART_DEBUG, "key2_OFF \r\n");	
//	}
//	else
//	{		key2_ON;
//	UsartPrintf(USART_DEBUG, "key2_ON \r\n");	
//	}
//	
//	if(key3==0) key3_OFF;		
//	else key3_ON;
//	
//	if(key4==0) key4_OFF;		
//	else key4_ON;
//	
//	if(key5==0) key5_OFF;		
//	else key5_ON;
//	
//	if(key6==0) key6_OFF;		
//	else key6_ON;
		
}
