//定时器4计时产生中断

#include "sys.h"
#include "time.h"

int flag1=0;


void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///使能TIM3时钟
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//初始化TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //允许定时器3更新中断
	TIM_Cmd(TIM4,ENABLE); //使能定时器3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //定时器3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	
}
	
	
	
	
	//定时器3中断服务函数
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //溢出中断
	{
		if (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1)
		{
			flag1++;
			if (flag1==1000)
			{
				TIM_SetCompare1(TIM3,1500);
				GPIO_SetBits(GPIOC,GPIO_Pin_1);
			}
		}
		else
		{
			GPIO_ResetBits(GPIOC,GPIO_Pin_1);
			flag1=0;
			TIM_SetCompare1(TIM2,500);
		  TIM_SetCompare1(TIM3,500);//舵机1,2都转到0度	
		}
	}TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //清除中断标志位
}



