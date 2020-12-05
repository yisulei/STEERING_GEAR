//GPIOB,Pin0 控制按键
#include "sys.h"
#include "key.h"
#include "delay.h"


void KEY_Init(void)
{
	
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA时钟
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; // KEY1 对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
} 

