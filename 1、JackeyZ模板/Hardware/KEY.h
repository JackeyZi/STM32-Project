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
//����Ӳ���ӿ�
#define KEY_MENU        GPIO_Pin_13      // ����һGPIO
#define KEY_SETTING     GPIO_Pin_1       // ������GPIO
#define KEY_UP          GPIO_Pin_11      // ������GPIO
#define KEY_DOWN        GPIO_Pin_14      // ������GPIO
#define KEY_SIZE                 4       // ��������
#define KEY_LONG_TIME          100       // ����ʱ��
#define KEY_SHORT_TIME           2       // �̰�����
#define TRUE                     1       // ��һ
#define FALSE                    0       // ����
 
 /* ����ö�� */
typedef enum KeyNum
{ 
	keyMenu = 1,
	keySetting,
	keyUp,
	keyDown,
}KeyNum_t;	

extern uint8_t mode;

/* �����ṹ�� */
typedef struct KeyPress
{
	uint8_t Cnt;
	uint8_t Press;
	uint8_t ShortFlag;
	uint8_t LongFlag;
	uint8_t Short;
}KeyPress;

/* �ⲿ�ɵ��ð����ṹ�� */
extern KeyPress Key_t[];

/* �Ա������� */
void InitKey(void);
void KeyScan(void);
void KeyTask(void);
void KeyShortHandle(void);
void KeyLongHandle(void);

#endif
