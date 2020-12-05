//��ʱ��4��ʱ�����ж�

#include "sys.h"
#include "time.h"

int flag1=0;


void TIM4_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM3ʱ��
	
  TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM3
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��3�����ж�
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��3
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn; //��ʱ��3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x00; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
	
}
	
	
	
	
	//��ʱ��3�жϷ�����
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
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
		  TIM_SetCompare1(TIM3,500);//���1,2��ת��0��	
		}
	}TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
}



