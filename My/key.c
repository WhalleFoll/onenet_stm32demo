/*-------------------------------------------------------------------------------
�ļ����ƣ�key.c
�ļ����������ð�����ʼ������       
��    ע����
---------------------------------------------------------------------------------*/
#include "key.h"
/*-------------------------------------------------------------------------------
�������ƣ�KEY_Init
�����������������ų�ʼ�����򿪶˿�ʱ�ӣ����ö˿����ţ��˿ڹ���Ƶ�ʣ��˿�����ģʽ 
�����������
���ز�������
��    ע����
---------------------------------------------------------------------------------*/
void KEY_Init(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
	
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//��PB��ʱ��	
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//��PA��ʱ��
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//��PE��ʱ��	
	   	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//PE2,PE3,PE4��������	   
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//�˿��ٶ�		
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�˿�ģʽ����Ϊ��������ģʽ		
	  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ����Ӧ�Ķ˿�
				
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;//PA0��������	
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//�˿��ٶ�		
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//�˿�ģʽ����Ϊ��������ģʽ		
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ����Ӧ�Ķ˿�
	
}


u8 scan(void)
{
 if (sains == 0 || rans == 1)     // yu 0   an  1  
 {
  return 1;
 }
 else 
	 return 0;
}

