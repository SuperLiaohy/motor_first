//
// Created by 24106 on 2024/4/25.
//

#include "Inc/blueteeth.h"
extern DMA_HandleTypeDef hdma_usart3_rx;
void BLUETEETH::send(const char* buf, ...) {
    const char *p = buf;
    char str[255] = {0};
    va_list v;
    va_start(v, buf);
    vsprintf(str, buf, v); //使用可变参数的字符串打印。类似sprintf
    HAL_UART_Transmit(huart, (uint8_t *)str, strlen(str), 0xff);
    va_end(v);
}

void BLUETEETH::receive() {
    HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *)bag, 50);
    __HAL_DMA_DISABLE_IT(hdma_usart_rx, DMA_IT_HT);
}

void BLUETEETH::test(){
    if (bag[0]=='@' && bag[1] == 'o'&& bag[2] == 'p' && bag[3] == 'e' && bag[4] == 'n'){
        if (bag[5]==' '&&bag[6]=='a'&&bag[7]=='n'&&bag[8]=='g'&&bag[9]=='l'&&bag[10]=='e') {
            BackRight.clear();
            BackLeft.clear();
            FrontRight.clear();
            FrontLeft.clear();
            AngleOpen = 1;
        }
        else if (bag[5]==' '&&bag[6]=='s'&&bag[7]=='p'&&bag[8]=='e'&&bag[9]=='e'&&bag[10]=='d') {
            BackRight.clear();
            BackLeft.clear();
            FrontRight.clear();
            FrontLeft.clear();
            SpeedOpen = 1;
        }
    } else if (bag[0]=='@' && bag[1] == 'c'&& bag[2] == 'l' && bag[3] == 'o' && bag[4] == 's' && bag[5] == 'e'){
        if (bag[6]==' '&&bag[7]=='a'&&bag[8]=='n'&&bag[9]=='g'&&bag[10]=='l'&&bag[11]=='e') {
            AngleOpen = 0;
        }
        else if (bag[6]==' '&&bag[7]=='s'&&bag[8]=='p'&&bag[9]=='e'&&bag[10]=='e'&&bag[11]=='d') {
            SpeedOpen = 0;
        }
    }
}

BLUETEETH blueteeth(&huart3,&hdma_usart3_rx,bag);
