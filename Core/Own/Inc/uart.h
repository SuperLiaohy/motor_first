//
// Created by 24106 on 2024/4/5.
//

#ifndef ANGLE_UART_H
#define ANGLE_UART_H

#include "usart.h"
#include "stdio.h"
#include "stdarg.h"
#include "string.h"

extern uint8_t bag[50];   //指定集 //data bag
extern uint8_t AngleOpen;
extern uint8_t SpeedOpen;

void print(UART_HandleTypeDef* huart, const char* buf, ...);
void number(const char* str,int *s);
void printn(UART_HandleTypeDef* huart, uint16_t Size,const uint8_t * buf);


#endif //ANGLE_UART_H
