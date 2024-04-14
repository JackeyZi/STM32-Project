/**
 * @file timer.c
 * @author JackeyZ
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#include "timer.h"
#include "led.h"
#include "key.h"

#define T3PSC 1800 -1 	//定时器2的PSC值
#define T3ARR 400 -1		  //定时器2的ARR值
/**
 * @brief Timer Initial
 * @note  Tout = ((arr + 1) * ( psc + 1 )) / Tclk
 * @param psc = 18000 - 1 
 * @param arr = 4000 -1
 * @note interval 1s 
*/
void InitTimer()
{
	TIMx_Init(TIM3,T3PSC,T3ARR);
}


void TIMx_Init(TIM_TypeDef* TIMx,u16 Psc,u16 Arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	if(TIMx==TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
		NVIC_InitStruct.NVIC_IRQChannel=TIM1_UP_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;
		NVIC_Init(&NVIC_InitStruct);
	}
	else if(TIMx==TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
		NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
		NVIC_Init(&NVIC_InitStruct);
	}
	else if(TIMx==TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
		NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority=2;
		NVIC_Init(&NVIC_InitStruct);
	}
	
	TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period=Arr; 
	TIM_TimeBaseInitStruct.TIM_Prescaler=Psc;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIMx,&TIM_TimeBaseInitStruct);
    
	TIM_ITConfig(TIMx,TIM_IT_Update,ENABLE);
	TIM_ClearITPendingBit(TIMx,TIM_IT_Update);
	TIM_Cmd(TIMx,ENABLE);
}


void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		WorkLedToggle();
		KeyScan();
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
	}
}
