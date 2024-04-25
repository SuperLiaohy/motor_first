#ifndef ANGLE_MOTOR_H
#define ANGLE_MOTOR_H
#ifdef __cplusplus
extern "C" {
#endif

#include "gpio.h"
#include "tim.h"

#ifdef __cplusplus
}
#endif

class motor {
private:
    bool val;

    GPIO_TypeDef *GPIOx;

    uint16_t GPIO_Pin_1;
    uint16_t GPIO_Pin_2;

    TIM_HandleTypeDef *pwm;
    uint32_t Channel;

    TIM_HandleTypeDef *encoder;
public:
    int real;

    short pos;
    short last_pos;

    short speed;

    motor(GPIO_TypeDef *mGPIOx, uint16_t mGPIO_Pin_1, uint16_t mGPIO_Pin_2, TIM_HandleTypeDef *mpwm, uint32_t mChannel,TIM_HandleTypeDef *mencoder,bool mval){
        GPIOx = mGPIOx;
        GPIO_Pin_1 = mGPIO_Pin_1;
        GPIO_Pin_2 = mGPIO_Pin_2;
        pwm = mpwm;
        Channel = mChannel;
        encoder = mencoder;
        val = mval;
    }

    void front_run();
    void back_run();

    void SetPwm(int input);

    void GetPos();

    void clear();
};
extern motor BackLeft;
extern motor FrontLeft;
extern motor FrontRight;
extern motor BackRight;
#endif //ANGLE_MOTOR_H
