#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

#define BEEP_ON GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define BEEP_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define BEEP_REV GPIO_WriteBit(GPIOB, GPIO_Pin_8,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_8))))


void BEEP_Init(void);

#endif
/*----------------------德飞莱 技术论坛：www.doflye.net--------------------------*/
