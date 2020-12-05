#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include "time.h"
#include "key.h"
#include "led.h"

int main(void)
	
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	KEY_Init();
        TIM2_PWM_Init(20000-1,84-1);
	TIM3_PWM_Init(20000-1,84-1);
	LED_Init();
	TIM4_Int_Init(100-1,840-1);//1ms中断一次  84/84M*1000=1ms
	SystemInit()；			
	while(1)
	{
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1)
		{
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			TIM_SetCompare1(TIM2,1500);  //(arr+1)-(arr+1)*占空比  舵机1转90度
		}		
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		
  }
	
}




