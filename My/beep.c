/*-------------------------------------------------------------------------------
文件名称：beep.c
文件描述：根据硬件连接配置蜂鸣器端口，打开对应的寄存器        
备    注：无
---------------------------------------------------------------------------------*/
#include "beep.h"
/*-------------------------------------------------------------------------------
程序名称：BEEP_Init
程序描述：初始化BEEP相关端口，打开端口时钟，配置端口输出  
输入参数：无
返回参数：无
备    注：无
---------------------------------------------------------------------------------*/
void BEEP_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  //打开PB口时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//PB8引脚设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//端口速度
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//端口模式，此为输出推挽模式
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	//初始化对应的端口
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
