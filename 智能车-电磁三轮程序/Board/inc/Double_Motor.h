#ifndef _Double_Motor_H_
#define _Double_Motor_H_


#include "common.h"
#include "include.h"
/*
********�������ͷ�ļ�******
@file     Double_Motor.h
@author   ��ѧ�����������һ��
@date     2018-1-27
*/

void Double_Motor_init(uint32 freq,float duty);
void Double_Motor_pwm_duty(float Left_motor_duty,float Right_motor_duty);

#endif