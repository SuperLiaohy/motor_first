//
// Created by 24106 on 2024/4/21.
//

#ifndef RCT6_GY953_GY953_H
#define RCT6_GY953_GY953_H
#ifdef __cplusplus
extern "C" {
#endif
#include "uart.h"

#ifdef __cplusplus
}
#endif
#include "IT.h"


class GY953{
public:
    const uint8_t SendStart = 0xa5;
    const uint8_t ReceiveStart = 0x5a;

    const uint8_t BAU115200 = 0x54;
    const uint8_t BAU9600 = 0x53;

    const uint8_t AIO[2] = {0x51, 0xf6};
    const uint8_t GIO[2] = {0x52,0xf7};
    const uint8_t MIO[2] = {0x53,0xf8};
    const uint8_t AGRest[2] = {0x57,0xfc};
    const uint8_t MRest[2] = {0x58,0xfd};
    const uint8_t Rest[2] = {0x59,0xfe};
    const uint8_t Out50[2] = {0xa4,0x49};
    const uint8_t Out100[2] = {0xa5,0x4a};
    const uint8_t Out200[2] = {0xa6,0x4b};


    const uint8_t AOut[2] = {0x15,0xba};
    const uint8_t GOut[2] = {0x25,0xca};
    const uint8_t MOut[2] = {0x35,0xda};
    const uint8_t EOut[2] = {0x45,0xea};
    const uint8_t ASCEOut[2] = {0x55,0xfa};
    const uint8_t FNumberOut[2] = {0x65,0x0a};

    const uint8_t AData = 0x15;
    const uint8_t GData = 0x25;
    const uint8_t MData = 0x35;
    const uint8_t RPYData = 0x45;
    const uint8_t No = 0x55;
    const uint8_t FNumber = 0x65;
    const uint8_t Hz = 0x75;
    const uint8_t MAX = 0x85;


    int16_t ROLL,PITCH,YAW;
    int16_t rpy[3],Acc[3],Gyr[3],Mag[3],Q[4];

    short e[3],a[3],g[3],m[3];

    DMA_HandleTypeDef *hdma_usart_rx;
    uint8_t *buffer;
public:
    UART_HandleTypeDef *huart;
    GY953(UART_HandleTypeDef *mhuart,uint8_t *mbuffer,DMA_HandleTypeDef *mhdma_usart_rx);

    void Send(const uint8_t* cmd);

    void Init();

    void compute();

    void Test(uint16_t Size);

    void Receive();
};
#endif //RCT6_GY953_GY953_H
