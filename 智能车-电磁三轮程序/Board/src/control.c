#include "control.h"

/*
********�������Դ�ļ�******
@file     control.c
@author   ��ѧ�����������һ��
@date     2018-3-10
*/


float car_Dir_out,car_Speed_out;

/*!
 *  @brief      ����PID���ж�
 *  Sample usage:   10ms
 */

void systick_irq(void)
{
  static int i=0;    
    if(stop_flag==1)       //��Ϊ SysTick ���ܽ��г�ʱ��Ķ�ʱ����������ֻ���ñ��������������൱�� 10*10 = 100ms�ж�һ��    
    {    
        i++;  
    }    
    if(i>=50)   
    {    
        stop_flag=2;    
    }    
    
//    MPU6050_GetData(&GYRO, &ACC);	// ��ȡ����������
//    Data_Filter();
//    if(GYRO_Real.Z>=-5&&GYRO_Real.Z<=5)
//    {
//      GYRO_Real.Z = 0;
//    }
    //car_Dir_out = dir_d_PID((float)(GYRO_Real.Z*100),Radius);  
  //car_Dir_out=dir_PID();
    if(RoundCenterStart_2==1&&RoundCenterStart_3==1&&RoundCenterStart_5==0)
    {
      car_Dir_out = dir_R_PID();
    }
    else
    {
      car_Dir_out = dir_PID();
    }
    Motor_out();
}

/*!
 *  @brief      �ٶ�PID���ж�
 *  Sample usage:   50ms
 */
void pit_ch0_irq(void)
{
    static int i=0;    
    if(i==50)          
    {    
        //led_turn(LED2);             //��˸ LED2    
        i=0;    
    }    
    else   
    {    
        i++;    
    }  
    Measurement_speed();
    car_Speed_out += Speed_PID(count_left,count_right);
    vcan_sendware(var, sizeof(var));

    PIT_Flag_Clear(PIT0);       //���жϱ�־λ
}


//����ͣ������ж�
void  kbi1_irq(void)    
{    
   if(IS_KBI1_IRQ())       //�ж��Ƿ���Ч��KBI�ж�    
   {    
       if(IS_KBI_CH_IRQ(PTE5)) //�ж��Ƿ�PTE4�������ж�    
       {    
         //led_turn(LED3);

           if(stop_flag==2)
           {
             start_f=0;
           }
           stop_flag=1;
       }    
   }    
   KBI1_CLEAN_FLAG() ;    
}    

/*!
 *  @brief      ����������
 *  Sample usage:   
 */
void Motor_out(void)
{
  float Motor_left_out,Motor_right_out;
  Motor_left_out = car_Speed_out-car_Dir_out;
  Motor_right_out = car_Speed_out+car_Dir_out;
  Double_Motor_pwm_duty(Motor_left_out,Motor_right_out);

}