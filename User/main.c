#include "stm32f10x.h"
#include "esp8266.h"
#include "delay.h"
#include "usart.h"
#include "MyEXTI.h"
#include "stdio.h"
#include "sys.h"
#include "led.h"
#include "onenet.h"
#include "string.h" 
#include "Tim.h"
#include "DHT11.h"
#include "tsensor.h"
//#include "dac.h"
#include "adc.h"
#include "lcd.h"
#include "Relay.h"
#include "key.h"

extern __IO uint16_t ADC_ConvertedValue;
// �ֲ����������ڱ���ת�������ĵ�ѹֵ			 
float ADC_ConvertedValueLocal; 

extern u8 key;
extern float rain,san;
unsigned char temp_flag,ping_flag;  //��ʱ��

void KEYS_Init(void);
void Setkey(void);
void GET_Cmd(void);

void red(void);
int main(void)		
 {	 	
	    //u16 dac_temp = 3000;  //ȡֵ0-4096 vol:0~3300,����0~3.3V
	 
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//�жϿ��������� �����ж����ȼ�����2
  	     Delay_Init();//��ʱ��ʼ��SysTick�δ�ʱ��;
	     
		 Usart1_Init(115200);    //��ʼ������1
		 Usart2_Init(115200);    //��ʼ������2
	     EXTIX_Init();	         //�жϳ�ʼ��
	 
	     Relay_Init();            //�̵�����ʼ��
	 
		 //DAC1_Init();            //DAC�ػ�ģʽ��ʼ��	
		 //ADC_dma_init();         //ADC������dma
		 DHT11_Init();		     //DHT11��ʼ�� 
        // T_Adc_Init();		     //оƬ�¶ȳ�ʼ��
	     
	     Tim1_Init(5000,72);     //��ʱ����������Ϊ5ms     ���ʱ��TimeOut= (arr+1)*(psc+1)/Tic   ==5000*72/72
         pwm_init();      
	    		 TIM_SetCompare1(TIM3, 195);//0��
	  delay_ms(500); 
	 delay_ms(500); 
	 TIM_SetCompare1(TIM3, 175);//0��
	  delay_ms(500); 
		delay_ms(500); 
	 TIM_SetCompare1(TIM3, 185);

		 LED_Init();
		 KEY_Init();
		 
		 
	     ESP8266_Init();         //��ʼ��ESP8266������	
		 while(OneNet_DevLink())		//����OneNET			 
		 delay_ms(500);    //����OneNetƽ̨
		
		 
	  while(1)	             //whileѭ��ִ�и��ֹ��� 
		{   
		
      		
		
		 GET_Cmd();      //��ƽ̨��ȡָ��	
		 Setkey();      //�����̵���

			if (key==1)  //kai
			{
			   TIM_SetCompare1(TIM3, 185);
					if (scan()==1)  // guan
					{
						 TIM_SetCompare1(TIM3, 175);
						rain=2.4;
						san=3.3;
					}
//					
//					if (scan()==0)  //kai
//					{
//						 TIM_SetCompare1(TIM3, 185);
//						 rain=3.2;san=2.1;
//					}
			}
			if(key==0)
			{
			  TIM_SetCompare1(TIM3, 175);
			}
			
			

			
			
		if(temp_flag)									//���ͼ��5s  ��ʱ��
		{
			temp_flag=0;
			
			DHT11_Read_Data();//����¶� ʪ��
			
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");		
			
			OneNet_SendData();									//��������
		
			ESP8266_Clear();
			 
		}
		
		if(ping_flag)//���������� ÿ40s/��
		{
			ping_flag=0;
			
			MQTT_Ping();
			
			ESP8266_Clear();
			 
		}

		delay_ms(1000);
		
	  
    }

}


void GET_Cmd(void)//��ȡָ��
{
	unsigned char *dataPtr = NULL;
	dataPtr = ESP8266_GetIPD(0);

	if(dataPtr != NULL)
	OneNet_RevPro(dataPtr);
	
}

