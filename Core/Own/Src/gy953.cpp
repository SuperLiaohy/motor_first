//
// Created by 24106 on 2024/4/21.
//

#include "Inc/gy953.h"
GY953::GY953(UART_HandleTypeDef *mhuart,uint8_t *mbuffer,DMA_HandleTypeDef *mhdma_usart_rx) {
    buffer = mbuffer;
    huart = mhuart;
    hdma_usart_rx = mhdma_usart_rx;
}

void GY953::Send(const uint8_t* cmd){
    uint8_t c[3];
    c[0] = SendStart;
    c[1] = cmd[0];
    c[2] = cmd[1];
    printn(huart,3,c);
}

void GY953::Test(uint16_t Size) {
    if (buffer[0]==ReceiveStart&&buffer[1]==ReceiveStart){
        printn(huart, Size, (rebuf));
        if (1) {

            if (buffer[2] == AData) {//加数度数据输出
                Acc[0] = (buffer[4] << 8) | buffer[5];
                Acc[1] = (buffer[6] << 8) | buffer[7];
                Acc[2] = (buffer[8] << 8) | buffer[9];

            } else if (buffer[2] == GData) {//陀螺仪数据输出
                Gyr[0] = (buffer[4] << 8) | buffer[5];
                Gyr[1] = (buffer[6] << 8) | buffer[7];
                Gyr[2] = (buffer[8] << 8) | buffer[9];

            } else if (buffer[2] == MData) {//磁场数据输出
                Mag[0] = (buffer[4] << 8) | buffer[5];
                Mag[1] = (buffer[6] << 8) | buffer[7];
                Mag[2] = (buffer[8] << 8) | buffer[9];

            } else if (buffer[2] == RPYData) {//欧拉角数据输出
                ROLL  = (buffer[4] << 8) | buffer[5];
                PITCH = (buffer[6] << 8) | buffer[7];
                YAW   = (buffer[8] << 8) | buffer[9];
                rpy[0] = ROLL;
                rpy[1] = PITCH;
                rpy[2] = YAW;

            } else if (buffer[2] == FNumber) {//四元数数据输出
                Q[0] = (buffer[0] << 8) | buffer[1];
                Q[1] = (buffer[2] << 8) | buffer[3];
                Q[2] = (buffer[4] << 8) | buffer[5];
                Q[3] = (buffer[6] << 8) | buffer[7];

            }

        }
        compute();
    }
}

void GY953::Init() {

//    Send(AIO);
//    Send(GIO);
//    Send(MIO);

//    Send(AGRest);
//    Send(MRest);

//    Send(Out100);
//    Send(AOut);
//    Send(GOut);
//    Send(MOut);
    Send(EOut);
//    Send(FNumberOut);
}

void GY953::compute() {
    for (int i = 0; i < 3; ++i) {
//        a[i] = Acc[i] * 1.0 / 32767 * 20;
//        g[i] = Gyr[i] * 1.0 / 32767 * 2000;
//        m[i] = Mag[i] * 1.0 / 32767 * 4915;
        e[i] = rpy[i] * 1.0 / 100;
    }

}

void GY953::Receive() {
    HAL_UARTEx_ReceiveToIdle_DMA(huart, (uint8_t *)bag, 50);
    __HAL_DMA_DISABLE_IT(hdma_usart_rx, DMA_IT_HT);
}


