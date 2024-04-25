//
// Created by 24106 on 2024/4/25.
//

#ifndef MOTOR_FIRST_BLUETEETH_H
#define MOTOR_FIRST_BLUETEETH_H
#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include "uart.h"
#include "stm32f1xx_hal.h"
#ifdef __cplusplus
}
#endif
#include "motor.h"
class BLUETEETH{
public:
    BLUETEETH(UART_HandleTypeDef *mhuart,DMA_HandleTypeDef *mhdma_usart_rx,uint8_t* mbag){
        huart = mhuart;
        hdma_usart_rx = mhdma_usart_rx;
        bag = mbag;
    }

    UART_HandleTypeDef *huart;
    DMA_HandleTypeDef *hdma_usart_rx;

    uint8_t *bag;

    void send(const char* buf, ...);

    void receive();

    void test();

};

extern BLUETEETH blueteeth;

#endif //MOTOR_FIRST_BLUETEETH_H
