#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include "time.h"
#include "key.h"
#include "led.h"

int main(void)
	
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	KEY_Init();
  TIM2_PWM_Init(20000-1,84-1);
	TIM3_PWM_Init(20000-1,84-1);
	LED_Init();
	TIM4_Int_Init(100-1,840-1);//1ms�ж�һ��  84/84M*1000=1ms
	//TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
	SystemInit();
	
	//TIM_SetCompare1(TIM2,975);			

	while(1)
	{
		while (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0)==1)
		{
			//TIM4_Int_Init(1000-1,84-1);//1ms�ж�һ��  84/84M*1000=1ms
			GPIO_SetBits(GPIOC,GPIO_Pin_0);
			//TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
			TIM_SetCompare1(TIM2,1500);  //(arr+1)-(arr+1)*ռ�ձ�  ���1ת90��
		}
		//TIM_SetCompare1(TIM2,500);
		//TIM_SetCompare1(TIM3,500);//���1,2��ת��0��		
		GPIO_ResetBits(GPIOC,GPIO_Pin_1);
		GPIO_ResetBits(GPIOC,GPIO_Pin_0);
		//TIM_Cmd(TIM4,DISABLE);
  }
	
}




