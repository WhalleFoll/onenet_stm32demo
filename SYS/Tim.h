#ifndef __TIM_H
#define __TIM_H	

#include "stm32f10x.h"



void Tim1_Init(int arr,int psc);
void Tim2_Init(int arr,int psc);
void pwm_init(void);
#endif
