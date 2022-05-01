
#ifndef __RELAY_H
#define __RELAY_H

#include "stm32f10x.h"


#define key_OFF GPIO_SetBits(GPIOG,GPIO_Pin_2)
#define key_ON GPIO_ResetBits(GPIOG,GPIO_Pin_2)
#define key_REV GPIO_WriteBit(GPIOG, GPIO_Pin_2,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOG, GPIO_Pin_2))))

#define key2_OFF GPIO_SetBits(GPIOG,GPIO_Pin_3)
#define key2_ON GPIO_ResetBits(GPIOG,GPIO_Pin_3)

#define key3_OFF GPIO_SetBits(GPIOG,GPIO_Pin_4)
#define key3_ON GPIO_ResetBits(GPIOG,GPIO_Pin_4)

#define key4_OFF GPIO_SetBits(GPIOG,GPIO_Pin_5)
#define key4_ON GPIO_ResetBits(GPIOG,GPIO_Pin_5)

#define key5_OFF GPIO_SetBits(GPIOG,GPIO_Pin_6)
#define key5_ON GPIO_ResetBits(GPIOG,GPIO_Pin_6)

#define key6_OFF GPIO_SetBits(GPIOG,GPIO_Pin_7)
#define key6_ON GPIO_ResetBits(GPIOG,GPIO_Pin_7)

void Relay_Init(void);
void Setkey(void);

#endif
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
