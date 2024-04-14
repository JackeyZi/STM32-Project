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
#ifndef __KEY_H
#define __KEY_H
//按键硬件接口
#define KEY_MENU        GPIO_Pin_13      // 按键一GPIO
#define KEY_SETTING     GPIO_Pin_1       // 按键二GPIO
#define KEY_UP          GPIO_Pin_11      // 按键三GPIO
#define KEY_DOWN        GPIO_Pin_14      // 按键四GPIO
#define KEY_SIZE                 4       // 按键数量
#define KEY_LONG_TIME          100       // 长按时间
#define KEY_SHORT_TIME           2       // 短按消抖
#define TRUE                     1       // 置一
#define FALSE                    0       // 置零
 
 /* 按键枚举 */
typedef enum KeyNum
{ 
	keyMenu = 1,
	keySetting,
	keyUp,
	keyDown,
}KeyNum_t;	

extern uint8_t mode;

/* 按键结构体 */
typedef struct KeyPress
{
	uint8_t Cnt;
	uint8_t Press;
	uint8_t ShortFlag;
	uint8_t LongFlag;
	uint8_t Short;
}KeyPress;

/* 外部可调用按键结构体 */
extern KeyPress Key_t[];

/* 自变量函数 */
void InitKey(void);
void KeyScan(void);
void KeyTask(void);
void KeyShortHandle(void);
void KeyLongHandle(void);

#endif
