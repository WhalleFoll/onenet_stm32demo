/*-------------------------------------------------------------------------------
�̵���
---------------------------------------------------------------------------------*/
#include "Relay.h"
#include "usart.h"
//extern u8 key,key2,key3,key4,key5,key6;


void Relay_Init(void)//�̵�����ʼ��
{
      GPIO_InitTypeDef GPIO_InitStructure;
	
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG, ENABLE);//��PG��ʱ��	
	 	
	   	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;//PE2,PE3,PE4��������	   
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//�˿��ٶ�	
      GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	//�������
	  
	  GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ����Ӧ�Ķ˿�
				
}

void Setkey(void)//�̵�������
{
//	if(key==0)
//	{  key_OFF;	//off-�ر� 0	
//	    UsartPrintf(USART_DEBUG, "key_OFF \r\n");
//	}
//	else
//	{	key_ON;    //on-�� 1
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
