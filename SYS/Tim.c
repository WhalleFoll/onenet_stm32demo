#include "Tim.h"
#include "sys.h"


extern unsigned char temp_flag,ping_flag;

void Tim1_Init(int arr,int psc)//500ms进入一次
{ 
     TIM_TimeBaseInitTypeDef TIM_Structure;               //定义定时器结构体变量
	 NVIC_InitTypeDef NVIC_TIM;                           //定义中断嵌套结构体变量
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //打开定时器时钟
	 
	 TIM_Structure.TIM_Period = (arr-1) ;         //设置自动重装载寄存器周期值  溢出时间TimeOut= (arr)*(psc)/Tic    单位为us
     TIM_Structure.TIM_Prescaler = (psc-1);       //设置预分频值     
     TIM_Structure.TIM_CounterMode = TIM_CounterMode_Up ;     //计数模式 上升计数
	 TIM_Structure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频      Tic=72M/（TIM_ClockDivision+1）
	 TIM_Structure.TIM_RepetitionCounter = 0; //重复计数的次数
	
	 TIM_TimeBaseInit(TIM1,&TIM_Structure);   //初始化定时器1
	
	 NVIC_TIM.NVIC_IRQChannel = TIM1_UP_IRQn;  //定时器1的向上计算通道
	 NVIC_TIM.NVIC_IRQChannelCmd = ENABLE ;    //使能
	 NVIC_TIM.NVIC_IRQChannelPreemptionPriority = 0 ;    //抢占优先级
	 NVIC_TIM.NVIC_IRQChannelSubPriority = 0;            //响应优先级 
	
	 NVIC_Init(&NVIC_TIM);                     //初始化结构体
	 
	 TIM_ClearFlag(TIM1,TIM_FLAG_Update);      //清空所有标志位  保证工作状态初始化 
	 
	 TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);  //打开计时器
	
	 TIM_Cmd(TIM1,ENABLE);      	  	 	       //打开TIM1
	
	 
}	

/*****定时器1中断响应函数*****/
/*   需要查询中断函数名字 请打开 startup_stm32f10x_hd.s启动文件查询对应的中断响应名字*/
/*   说明：TIM_ClearFlag()函数是清除该定时器的所有标志位  
          一个定时器的标志位包括很多如 TIM_IT_Update TIM_IT_CC1 TIM_IT_CC2 TIM_IT_CC3 等 
          所以我们用具体清空标志位函数TIM_ClearITPendingBit() 对某个标志位进行清除 如果在没有几个标志位同时工作 两函数的使用效果应该是一样的  */

void TIM1_UP_IRQHandler (void)                
{
	static unsigned int temp_count,ping_count;

	if(TIM_GetITStatus(TIM1,TIM_IT_Update) != RESET)   //如果中断标志被置1 证明有中断
	{
	 
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);    // 清空标志位，为下一次进入中断做准备

	    temp_count++;
	    ping_count++;
		
		 if(temp_count == 2000)//10s
		 {
			 temp_flag=1;
			 temp_count=0;
		 } 
		if(ping_count == 8000)//40s
		 {
			 ping_flag=1;
			 ping_count=0;
		 } 
	}
  
}




void Tim2_Init(int arr,int psc)
{ 
   TIM_TimeBaseInitTypeDef TIM_Structure;               //定义定时器结构体变量
	 NVIC_InitTypeDef NVIC_TIM;                           //定义中断嵌套结构体变量
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  //打开定时器2时钟
	
	 TIM_Structure.TIM_Period = (arr-1) ;         //设置自动重装载寄存器周期值  溢出时间TimeOut= (arr+1)*(psc+1)/Tic    
   TIM_Structure.TIM_Prescaler = (psc-1);       //设置预分频值     
   TIM_Structure.TIM_CounterMode = TIM_CounterMode_Up ;     //计数模式 上升计数
	 TIM_Structure.TIM_ClockDivision = TIM_CKD_DIV1;     //时钟分频      Tic=72M/（TIM_ClockDivision+1）
	 TIM_Structure.TIM_RepetitionCounter = 0; //重复计数的次数
	
	 TIM_TimeBaseInit(TIM2,&TIM_Structure);   //初始化定时器1
	
	 NVIC_TIM.NVIC_IRQChannel = TIM2_IRQn;  //定时器1的向上计算通道
	 NVIC_TIM.NVIC_IRQChannelCmd = ENABLE ;    //使能
	 NVIC_TIM.NVIC_IRQChannelPreemptionPriority = 0 ;    //抢占优先级
	 NVIC_TIM.NVIC_IRQChannelSubPriority = 0;            //响应优先级 
	
	 NVIC_Init(&NVIC_TIM);                     //初始化结构体
	 
	 TIM_ClearFlag(TIM2,TIM_FLAG_Update);      //清空所有标志位  保证工作状态初始化 
	 
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);  //打开计时器
	
	 TIM_Cmd(TIM2,ENABLE);      	  	 	       //打开TIM2
	
	 
}	



void pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //声明一个结构体变量，用来初始化GPIO

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;//声明一个结构体变量，用来初始化定时器

	TIM_OCInitTypeDef TIM_OCInitStructure;//根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	/* 开启时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	/*  配置GPIO的模式和IO口 */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;// PC6
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	//TIM3定时器初始化
	TIM_TimeBaseInitStructure.TIM_Period = 199; //PWM 频率=72000/(199+1)=36Khz//设置自动重装载寄存器周期的值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7199;//设置用来作为TIMx时钟频率预分频值
	TIM_TimeBaseInitStructure.TIM_ClockDivision = 0;//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseInitStructure);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);//改变指定管脚的映射	//pC6

	//PWM初始化	  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;//PWM输出使能
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;

	TIM_OC1Init(TIM3,&TIM_OCInitStructure);
	//注意此处初始化时TIM_OC1Init而不是TIM_OCInit，否则会出错。因为固件库的版本不一样。
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//使能或者失能TIMx在CCR1上的预装载寄存器
	TIM_Cmd(TIM3,ENABLE);//使能或者失能TIMx外设
}



void TIM2_IRQHandler (void)                
{
           		 

}
  

