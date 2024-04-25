//
// Created by 24106 on 2024/4/5.
//

#include "Inc/motor.h"
#include "Inc/uart.h"



void motor::front_run() {
    if (val) {
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_SET);
    }
}

void motor::back_run() {
    if (val) {
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_SET);
    } else{
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_RESET);
    }
}

void motor::SetPwm(int input) {

    if (input>0){
        front_run();
    } else if (input<0){
        input = -input;
        back_run();
    }
    if (input==0)
        __HAL_TIM_SetCompare(pwm,Channel,0);
    else
        __HAL_TIM_SetCompare(pwm,Channel,input);

}

void motor::GetPos() {
    last_pos = pos;
    pos = __HAL_TIM_GET_COUNTER(encoder);
    speed = pos - last_pos;
    real += speed;
}

void motor::clear() {
    real = 0;
    pos = 0;
    last_pos = 0;
    speed = 0;
    __HAL_TIM_SET_COUNTER(encoder,0);
}


motor FrontRight (GPIOA,GPIO_PIN_12,GPIO_PIN_11,&htim8,TIM_CHANNEL_2,&htim2,1);

motor FrontLeft   (GPIOB,GPIO_PIN_8,GPIO_PIN_9,&htim8,TIM_CHANNEL_4,&htim5,1);

motor BackRight  (GPIOA,GPIO_PIN_4,GPIO_PIN_5,&htim8,TIM_CHANNEL_1,&htim1,1);

motor BackLeft  (GPIOB,GPIO_PIN_2,GPIO_PIN_1,&htim8,TIM_CHANNEL_3,&htim3,1);