/**
 * @file main.c
 * @author JackeyZ
 * @brief STM32F103C8T6 Template projects
 * @version 0.1
 * @date 2023-1-21
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "sys.h"
#include "key.h"

KeyPress Key_t[KEY_SIZE+1]; /* 按键数量     */
uint8_t mode;

void InitKey(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=KEY_MENU | KEY_DOWN ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode= GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin= KEY_SETTING | KEY_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
}

uint8_t GetKeyNum(void)
{
	if(GPIO_ReadInputDataBit(GPIOC,KEY_MENU) == RESET) return keyMenu;
	else if(GPIO_ReadInputDataBit(GPIOB,KEY_SETTING) == RESET) return keySetting;
	else if(GPIO_ReadInputDataBit(GPIOB,KEY_UP) == RESET) return keyUp;
	else if(GPIO_ReadInputDataBit(GPIOC,KEY_DOWN) == RESET) return keyDown;	
	else return 0;
}

void KeyScan(void)
{
	uint8_t keySta = GetKeyNum();
	if((keySta != FALSE) && (Key_t[keySta].Press == FALSE))   //  按下时处理
	{
		Key_t[keySta].Cnt++;
		if(Key_t[keySta].Cnt > KEY_SHORT_TIME)
			Key_t[keySta].ShortFlag = TRUE;
		
		if(Key_t[keySta].Cnt > KEY_LONG_TIME) 
		{
			Key_t[keySta].LongFlag  = TRUE;
			Key_t[keySta].Cnt       = FALSE;
			Key_t[keySta].Press     = TRUE;
			Key_t[keySta].ShortFlag = FALSE;
		}
	}
	else if(keySta == FALSE)                              //  松开时处理
	{
		for(int i = 0; i < (KEY_SIZE + 1); i++)
		{
			Key_t[i].Cnt = FALSE;
			Key_t[i].Press = FALSE; 
			if(Key_t[i].ShortFlag == TRUE)
			{
				Key_t[i].Short = TRUE;
				Key_t[i].ShortFlag = FALSE;
			}			
		}	
	}	
}

void KeyShortHandle(void)
{
	if(Key_t[1].Short == 1)
	{
		mode++;
	}
	else if(Key_t[2].Short == 1)
	{
		mode+=2;
	}	
	else if(Key_t[3].Short == 1)
	{
		mode+=3;
	}	
	else if(Key_t[4].Short == 1)
	{
		mode+=4;
	}	
}

void KeyLongHandle(void)
{
	uint8_t keyNum = GetKeyNum();
	switch(keyNum)
	{
		case keyMenu:
			mode--;
			break;
		case keySetting:
			mode-=2;
			break;
		case keyUp:
			mode-=3;
			break;
		case keyDown:
			mode-=4;
			break;
		default:
			break;
	}
}

void KeyTask(void)
{
	for(int i = 0; i < KEY_SIZE + 1; i++)
	{
		if(Key_t[i].Short == TRUE)
		{
			KeyShortHandle();
			Key_t[i].Short = FALSE;
		}
		else if(Key_t[i].LongFlag == TRUE)
		{
			KeyLongHandle();
			Key_t[i].LongFlag = FALSE;
		}
	}
}
