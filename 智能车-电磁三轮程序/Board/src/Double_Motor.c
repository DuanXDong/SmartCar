#include "Double_Motor.h"
#include "common.h"
#include "include.h"


/*
********电机设置源文件******
@file     Double_Motor.c
@author   段学东、李兢兢、张一翔
@date     2018-1-27
*/


/*!
 *  @brief      双电机初始化
 *  @param      freq   频率
 *  @param      duty   占空比
 *  Sample usage:   Double_Motor_init(100,30.1);  设置频率为：100Hz；占空比为：30.1%
 */
void Double_Motor_init(uint32 freq,float duty)
{
  
  ftm_pwm_finit(FTM0, FTM_CH0, freq, duty);     //左电机初始化
  ftm_pwm_finit(FTM0, FTM_CH1, freq, duty); 
  
  ftm_pwm_finit(FTM2, FTM_CH0, freq, duty);     //右电机初始化
  ftm_pwm_finit(FTM2, FTM_CH1, freq, duty); 
}

/*!
 *  @brief      双电机占空比设置
 *  @param      Left_motor_duty   左电机占空比；正数电机正传，负数电机反转
 *  @param      Right_motor_duty  右电机占空比；正数电机正传，负数电机反转
 *  Sample usage:   Double_Motor_pwm_duty(30.0,30.1);  设置左电机占空比为：30.0%；右电机占空比为：30.1%
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