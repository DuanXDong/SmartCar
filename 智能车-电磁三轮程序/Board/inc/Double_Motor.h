#ifndef _Double_Motor_H_
#define _Double_Motor_H_


#include "common.h"
#include "include.h"
/*
********电机设置头文件******
@file     Double_Motor.h
@author   段学东、李兢兢、张一翔
@date     2018-1-27
*/

void Double_Motor_init(uint32 freq,float duty);
void Double_Motor_pwm_duty(float Left_motor_duty,float Right_motor_duty);

#endif