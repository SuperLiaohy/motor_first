//
// Created by 24106 on 2024/4/5.
//

#include "Inc/uart.h"

/*
 * global variable
 */

uint8_t bag[50];   //指定集 //data bag
uint8_t AngleOpen=0;
uint8_t SpeedOpen=0;
/**
 * @brief it can change int to string,
 * @param str
 * @param s
 */
void number(const char* str,int *s){
    int num=0;
    int val_fu=0;
    for (int i = 0; str[i] != '!' ; ++i) {
        if (str[i]<='9'&&'0'<=str[i]){
            if (val_fu)
                num = num * 10 - (str[i] - '0');
            else
                num = num * 10 + (str[i] - '0');
        } else if (str[i]=='-'){
            val_fu = 1;
        }
    }
    *s = num;
}




void print(UART_HandleTypeDef* huart, const char* buf, ...)
{
    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(huart, str, strlen(str), 0xff);
    va_end(v);
}


void printn(UART_HandleTypeDef* huart, uint16_t Size,const uint8_t * buf)
{
    HAL_UART_Transmit(huart,buf, Size,0xff);
}

