//
// Created by 24106 on 2024/4/25.
//

#ifndef MOTOR_FIRST_TELESCOPIC_H
#define MOTOR_FIRST_TELESCOPIC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "tim.h"

#ifdef __cplusplus
}
#endif

class telescopic{
private:
    GPIO_TypeDef *GPIOx;

    uint16_t GPIO_Pin_1;
    uint16_t GPIO_Pin_2;

public:
    bool open;

    int target;

    int time;

    TIM_HandleTypeDef *timer;

    telescopic(GPIO_TypeDef *mGPIOx, uint16_t mGPIO_Pin_1, uint16_t mGPIO_Pin_2, TIM_HandleTypeDef *mtimer){
        GPIOx = mGPIOx;

        GPIO_Pin_2 = mGPIO_Pin_2;
        GPIO_Pin_1 = mGPIO_Pin_1;

        timer = mtimer;
    };

    void Close();

    void Open(bool val = 1);

    void SetTimer(int x);

    void Clear();
};

extern telescopic stick;

#endif //MOTOR_FIRST_TELESCOPIC_H
