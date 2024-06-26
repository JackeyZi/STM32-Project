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

#include "stm32f10x.h"
#include "initial.h"
#include "led.h"
#include "delay.h"
#include "timer.h"
#include "uart.h"
#include "config.h"
#include "OLED.h"
#include "key.h"
#include "pwm.h"
#include "sys.h"

/**
 * @brief System Initial
 * @note  初始化函数
*/
void InitSystem(void)
{   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  // 初始化-NVIC	
	InitOled();                                      // 初始化-OLED 
  InitKey();	                                     // 初始化-按钮
	InitWorkLed();                                   // 初始化-LED灯
	InitUsarts();                                    // 初始化-串口  
	//InitPWM();                                       // 初始化-PWM 
	InitTimer();                                     // 初始化-定时器	
	USART_Printf(USART1,"Sys init finish.....\r\n"); // 初始化-完成	
}
