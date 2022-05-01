
#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

#define S1 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)
#define S2 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)
#define S3 GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2)
#define S4 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)


#define rans GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)
#define sains GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)
void KEY_Init(void);
u8 scan(void);
#endif
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
