#include "control.h"

/*
********电机设置源文件******
@file     control.c
@author   段学东、李兢兢、张一翔
@date     2018-3-10
*/


float car_Dir_out,car_Speed_out;

/*!
 *  @brief      方向PID的中断
 *  Sample usage:   10ms
 */

void systick_irq(void)
{
  static int i=0;    
    if(stop_flag==1)       //因为 SysTick 不能进行长时间的定时，所以这里只能用变量来做倍数，相当于 10*10 = 100ms中断一次    
    {    
        i++;  
    }    
    if(i>=50)   
    {    
        stop_flag=2;    
    }    
    
//    MPU6050_GetData(&GYRO, &ACC);	// 读取陀螺仪数据
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
 *  @brief      速度PID的中断
 *  Sample usage:   50ms
 */
void pit_ch0_irq(void)
{
    static int i=0;    
    if(i==50)          
    {    
        //led_turn(LED2);             //闪烁 LED2    
        i=0;    
    }    
    else   
    {    
        i++;    
    }  
    Measurement_speed();
    car_Speed_out += Speed_PID(count_left,count_right);
    vcan_sendware(var, sizeof(var));

    PIT_Flag_Clear(PIT0);       //清中断标志位
}


//用于停车检测中断
void  kbi1_irq(void)    
{    
   if(IS_KBI1_IRQ())       //判断是否有效的KBI中断    
   {    
       if(IS_KBI_CH_IRQ(PTE5)) //判断是否PTE4触发的中断    
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
 *  @brief      电机输出函数
 *  Sample usage:   
 */
void Motor_out(void)
{
  float Motor_left_out,Motor_right_out;
  Motor_left_out = car_Speed_out-car_Dir_out;
  Motor_right_out = car_Speed_out+car_Dir_out;
  Double_Motor_pwm_duty(Motor_left_out,Motor_right_out);

}