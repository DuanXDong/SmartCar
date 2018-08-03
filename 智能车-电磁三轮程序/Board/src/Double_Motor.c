#include "Double_Motor.h"
#include "common.h"
#include "include.h"


/*
********�������Դ�ļ�******
@file     Double_Motor.c
@author   ��ѧ�����������һ��
@date     2018-1-27
*/


/*!
 *  @brief      ˫�����ʼ��
 *  @param      freq   Ƶ��
 *  @param      duty   ռ�ձ�
 *  Sample usage:   Double_Motor_init(100,30.1);  ����Ƶ��Ϊ��100Hz��ռ�ձ�Ϊ��30.1%
 */
void Double_Motor_init(uint32 freq,float duty)
{
  
  ftm_pwm_finit(FTM0, FTM_CH0, freq, duty);     //������ʼ��
  ftm_pwm_finit(FTM0, FTM_CH1, freq, duty); 
  
  ftm_pwm_finit(FTM2, FTM_CH0, freq, duty);     //�ҵ����ʼ��
  ftm_pwm_finit(FTM2, FTM_CH1, freq, duty); 
}

/*!
 *  @brief      ˫���ռ�ձ�����
 *  @param      Left_motor_duty   ����ռ�ձȣ�����������������������ת
 *  @param      Right_motor_duty  �ҵ��ռ�ձȣ�����������������������ת
 *  Sample usage:   Double_Motor_pwm_duty(30.0,30.1);  ��������ռ�ձ�Ϊ��30.0%���ҵ��ռ�ձ�Ϊ��30.1%
 */
void Double_Motor_pwm_duty(float Left_motor_duty,float Right_motor_duty)
{
  
  
  if(Left_motor_duty>=0)
  {
      if(Left_motor_duty>=99)
      {
        Left_motor_duty=99;
      }
      else if(Left_motor_duty<=5)
      {
        Left_motor_duty=0;
      }
      ftm_pwm_fduty(FTM0, FTM_CH0, 0);
      ftm_pwm_fduty(FTM0, FTM_CH1, Left_motor_duty);
  }
  else
  {
    if(Left_motor_duty<=-99)
      {
        Left_motor_duty=-99;
      }
      else if(Left_motor_duty>=-5)
      {
        Left_motor_duty=0;
      }
    Left_motor_duty=-Left_motor_duty;
    ftm_pwm_fduty(FTM0, FTM_CH0, Left_motor_duty);
    ftm_pwm_fduty(FTM0, FTM_CH1, 0);
  }
  if(Right_motor_duty>=0)
  {
      if(Right_motor_duty>=99)
      {
        Right_motor_duty=99;
      }
      else if(Right_motor_duty<=5)
      {
        Right_motor_duty=0;
      }
      ftm_pwm_fduty(FTM2, FTM_CH0, Right_motor_duty);
      ftm_pwm_fduty(FTM2, FTM_CH1, 0);
  }
  else
  {
      if(Right_motor_duty<=-99)
      {
        Right_motor_duty=-99;
      }
      else if(Right_motor_duty>=-5)
      {
        Right_motor_duty=0;
      }
      Right_motor_duty=-Right_motor_duty;
      ftm_pwm_fduty(FTM2, FTM_CH0, 0);
      ftm_pwm_fduty(FTM2, FTM_CH1, Right_motor_duty);
  }

  
}