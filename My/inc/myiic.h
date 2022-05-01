#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f10x.h"
/*-------------------------------------------------------------------------------
文件名称：myiic.c
文件描述：模拟IIC时序控制，
硬件平台：尼莫M3S开发板
编写整理：shifang
固件库  ：V3.5
技术论坛：www.doflye.net
备    注：通过简单修改可以移植到其他开发板，部分资料来源于网络。
---------------------------------------------------------------------------------*/

//IO方向设置
#define SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO操作函数	 
#define IIC_SCL_SET GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define IIC_SCL_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define IIC_SDA_SET GPIO_SetBits(GPIOB,GPIO_Pin_11)
#define IIC_SDA_CLR GPIO_ResetBits(GPIOB,GPIO_Pin_11) 
#define READ_SDA   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) //输入SDA 

//IIC所有操作函数


void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif

/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/














