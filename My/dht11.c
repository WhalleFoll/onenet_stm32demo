#include "dht11.h"
#include "delay.h"
      
extern double humi,temp;

void DHT11_Rst(void)	   
{                 
	DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//GPIOA.0=0
    delay_ms(20);    	//Pull down Least 18ms
    DHT11_DQ_OUT=1; 	//GPIOA.0=1 
	delay_us(30);     	//Pull up 20~40us
}

u8 DHT11_Check(void)//DHT11检查模块，曾经差点死在这了，后来发现了是DHT11.h的文件中少&=写成了= 	   
{                   //用了BeyondCompare软件比较了几遍竟然未发现这么明显的错误
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11 Pull down 40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)
		return 1;
	else 
		retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11 Pull up 40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)
		return 1;//chack error	    
	return 0;
}

u8 DHT11_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//wait become Low level
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//wait become High level
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//wait 40us
	if(DHT11_DQ_IN)
		return 1;
	else 
		return 0;		   
}

u8 DHT11_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit();
    }						    
    return dat;
}

u8 DHT11_Read_Data()    
{        
 	u8 buf[5];
	u8 i;

	DHT11_Rst();
	
	if(DHT11_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT11_Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{

				humi = buf[0] + buf[1] / 10.0;    //自动类型转换
				temp = buf[2] + buf[3] / 10.0; 
		} //先转换为double再进行运算。
	}
	else 
		return 1;
	return 0;	    
}
	 
u8 DHT11_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				 
 	GPIO_SetBits(GPIOA,GPIO_Pin_0);						 
			    
	DHT11_Rst();  
	return DHT11_Check();
} 







