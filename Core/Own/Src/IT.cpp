//
// Created by 24106 on 2024/4/5.
//

#include "Inc/IT.h"

extern GY953 gy953;

int  target = 100;

uint8_t rebuf[100]={0};

extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
/**
 * @brief test function
 */


float myabs(float input){
    return input<0?-input:input;
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    if (huart == blueteeth.huart){

        blueteeth.send("bag:%s\n",bag);

        if (bag[0]=='@'){

            angle.clear();
            speed.clear();
            speed_alone1.clear();
            speed_alone2.clear();
            speed_alone3.clear();
            speed_alone4.clear();

            blueteeth.send("%s\n","get the struct");
            number((char *)(bag), &target);
            blueteeth.send("target:%d\n",target);
        }

        blueteeth.test();

        blueteeth.receive();
    }
    if (huart == gy953.huart){

        gy953.Test(Size);

        gy953.Receive();
    }
}





void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
    if (htim == &htim4){

        BackLeft.GetPos();
        BackRight.GetPos();
        FrontLeft.GetPos();
        FrontRight.GetPos();

        blueteeth.send("FR::@%hd@%d@%hd@%hd\n",FrontRight.speed,FrontRight.real,FrontRight.pos,FrontRight.last_pos);
        blueteeth.send("BR@%hd@%d@%hd@%hd\n",BackRight.speed,BackRight.real,BackRight.pos,BackRight.last_pos);
        blueteeth.send("BL::@%hd@%d@%hd@%hd\n",BackLeft.speed,BackLeft.real,BackLeft.pos,BackLeft.last_pos);
        blueteeth.send("FL@%hd@%d@%hd@%hd\n",FrontLeft.speed,FrontLeft.real,FrontLeft.pos,FrontLeft.last_pos);

        if (AngleOpen) {

        }

        if (SpeedOpen){

            FrontLeft.SetPwm(speed_alone1.SpeedPid(FrontLeft, target));
            BackRight.SetPwm(speed_alone2.SpeedPid(BackRight, target));
            BackLeft.SetPwm(speed_alone3.SpeedPid(BackLeft, target));
            FrontRight.SetPwm(speed_alone4.SpeedPid(FrontRight, target));

            blueteeth.send("@%hd@%d@%hd@%hd\n",FrontRight.speed,FrontRight.real,FrontRight.pos,FrontRight.last_pos);
        }

    }
    if (htim == stick.timer){
        if (stick.open) {
            stick.time++;
            if (stick.time == stick.target) {
                stick.Close();
                stick.Clear();
            }
        }

    }
};
