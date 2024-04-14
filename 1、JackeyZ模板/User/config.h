/**
 * @file config.h
 * @author JackeyZ
 * @brief 
 * @version 0.1
 * @date 2023-12-28
 * 
 * @copyright Copyright (c) JackeyZ
 * 
 */
#ifndef __CONFIG_H_
#define	__CONFIG_H_
#include "stm32f10x.h"


#define TRUE 1
#define FALSE 0

//#define NORMAL 0
//#define REVERSE_DISPLAY 1


typedef struct
{
  uint8_t type;
  uint16_t data;
}SensorTypeDef;


#endif
