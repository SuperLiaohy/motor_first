//
// Created by 24106 on 2024/4/25.
//

#include "telescopic.h"

void telescopic::Open(bool val) {
    if (val) {
        HAL_GPIO_WritePin(GPIOx,GPIO_Pin_2,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOx,GPIO_Pin_1,GPIO_PIN_SET);
    } else{
        HAL_GPIO_WritePin(GPIOx,GPIO_Pin_2,GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOx,GPIO_Pin_1,GPIO_PIN_RESET);
    }

    open = 1;


}

void telescopic::Close() {
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_2,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOx,GPIO_Pin_1,GPIO_PIN_SET);

    open = 0;
}



void telescopic::Clear() {
    time = 0;
}

void telescopic::SetTimer(int x) {
    target = x;
}


telescopic stick(GPIOC,GPIO_PIN_0,GPIO_PIN_1,&htim6);