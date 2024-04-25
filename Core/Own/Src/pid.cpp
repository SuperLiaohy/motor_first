//
// Created by 24106 on 2024/4/5.
//

#include "Inc/pid.h"

void limit(float min,float &m,float max){
    if (min>m){
        m = min;
    } else if (max<m){
        m = max;
    }
}

void pid::clear() {
    clean = true;
    PItem = 0;
    IItem = 0;
    DItem = 0;
}

float pid::PosPid(motor MOTOR, float target) {

    PItem = target - MOTOR.real;
    IItem += PItem;
    DItem = MOTOR.real - MOTOR.last_pos;

    return p * PItem + i * IItem + d * DItem;
}

float pid::AddPid(motor MOTOR, float target) {
    static float PreErr = 0;
    static float LastErr = 0;
    static float Err = 0;
    if (clean){
        PreErr = 0;
        LastErr = 0;
        Err = 0;
        clean = false;
    }
/*
 * limit speed
 * can't too small
 * else
 * Turn left and right
 */
    limit(-25,target,25);

    PreErr = LastErr;
    LastErr = Err;
    Err = target - MOTOR.speed;

    limit(-10000,Err,10000);

    PItem = Err - LastErr;
    IItem = Err;
    DItem = Err - 2 * LastErr + PreErr;

    return p * PItem + i * IItem + d * DItem;
}

float pid::SpeedPid(motor MOTOR, float target) {
    PItem = target - MOTOR.speed;
    IItem += PItem;
    DItem = MOTOR.real - MOTOR.last_pos;

    return p * PItem + i * IItem + d * DItem;
}

pid angle;
pid speed;

pid speed_alone1;
pid speed_alone2;
pid speed_alone3;
pid speed_alone4;
