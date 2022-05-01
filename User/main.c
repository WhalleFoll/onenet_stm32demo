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
// 局部变量，用于保存转换计算后的电压值			 
float ADC_ConvertedValueLocal; 

extern u8 key;
extern float rain,san;
unsigned char temp_flag,ping_flag;  //定时器

void KEYS_Init(void);
void Setkey(void);
void GET_Cmd(void);

void red(void);
int main(void)		
 {	 	
	    //u16 dac_temp = 3000;  //取值0-4096 vol:0~3300,代表0~3.3V
	 
		 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//中断控制器分组 设置中断优先级分组2
  	     Delay_Init();//延时初始化SysTick滴答定时器;
	     
		 Usart1_Init(115200);    //初始化串口1
		 Usart2_Init(115200);    //初始化串口2
	     EXTIX_Init();	         //中断初始化
	 
	     Relay_Init();            //继电器初始化
	 
		 //DAC1_Init();            //DAC回环模式初始化	
		 //ADC_dma_init();         //ADC采用了dma
		 DHT11_Init();		     //DHT11初始化 
        // T_Adc_Init();		     //芯片温度初始化
	     
	     Tim1_Init(5000,72);     //定时器周期配置为5ms     溢出时间TimeOut= (arr+1)*(psc+1)/Tic   ==5000*72/72
         pwm_init();      
	    		 TIM_SetCompare1(TIM3, 195);//0度
	  delay_ms(500); 
	 delay_ms(500); 
	 TIM_SetCompare1(TIM3, 175);//0度
	  delay_ms(500); 
		delay_ms(500); 
	 TIM_SetCompare1(TIM3, 185);

		 LED_Init();
		 KEY_Init();
		 
		 
	     ESP8266_Init();         //初始化ESP8266的引脚	
		 while(OneNet_DevLink())		//接入OneNET			 
		 delay_ms(500);    //接入OneNet平台
		
		 
	  while(1)	             //while循环执行各种功能 
		{   
		
      		
		
		 GET_Cmd();      //从平台获取指令	
		 Setkey();      //操作继电器

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
			
			

			
			
		if(temp_flag)									//发送间隔5s  定时器
		{
			temp_flag=0;
			
			DHT11_Read_Data();//外界温度 湿度
			
			UsartPrintf(USART_DEBUG, "OneNet_SendData\r\n");		
			
			OneNet_SendData();									//发送数据
		
			ESP8266_Clear();
			 
		}
		
		if(ping_flag)//发送心跳包 每40s/次
		{
			ping_flag=0;
			
			MQTT_Ping();
			
			ESP8266_Clear();
			 
		}

		delay_ms(1000);
		
	  
    }

}


void GET_Cmd(void)//获取指令
{
	unsigned char *dataPtr = NULL;
	dataPtr = ESP8266_GetIPD(0);

	if(dataPtr != NULL)
	OneNet_RevPro(dataPtr);
	
}

