/*-------------------------------------------------------------------------------
文件名称：key.c
文件描述：配置按键初始化参数       
备    注：无
---------------------------------------------------------------------------------*/
#include "key.h"
/*-------------------------------------------------------------------------------
程序名称：KEY_Init
程序描述：按键引脚初始化，打开端口时钟，配置端口引脚，端口工作频率，端口输入模式 
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void KEY_Init(void)
{
      GPIO_InitTypeDef GPIO_InitStructure;
	
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//打开PB口时钟	
	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//打开PA口时钟
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);//打开PE口时钟	
	   	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;//PE2,PE3,PE4引脚设置	   
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//端口速度		
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//端口模式，此为输入上拉模式		
	  GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化对应的端口
				
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1 ;//PA0引脚设置	
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//端口速度		
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//端口模式，此为输入上拉模式		
	  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化对应的端口
	
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

