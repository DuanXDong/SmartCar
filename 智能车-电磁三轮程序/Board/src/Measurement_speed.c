#include "Measurement_speed.h"

/*
********电机设置源文件******
@file     Measurement_speed.c
@author   段学东、李兢兢、张一翔
@date     2018-3-13
*/

int16_t count_left,count_right;         //全局变量：速度大小
uint16 dir_left,dir_right;              //全局变量：方向标志

int16_t count_left_l[10];
int16_t count_right_r[10];



/*!
 *  @brief      双电机测速初始化
 *  Sample usage:   
 */
void Measurement_speed_init(void)
{
  ftm_pulse_init(FTM1, FTM_PS_1, TCLK1);
  gpio_init(PTF7,GPI,0);
  gpio_init(PTF6,GPI,0);
}


/*!
 *  @brief      双电机测速函数
 *  Sample usage:   
 */
void Measurement_speed(void)
{
  int16_t speed_left,speed_right; 
    //通过 ftm_pulse_mux 函数，重定义引脚 ，下面代码配置为 TCLK1
    ftm_pulse_mux(FTM1, TCLK1);
    ftm_pulse_clean(FTM1) ;
    DELAY_MS(10);
    speed_left = ftm_pulse_get(FTM1);
    
    
    //通过 ftm_pulse_mux 函数，重定义引脚 ，下面代码配置为 TCLK2
    ftm_pulse_mux(FTM1, TCLK2);
    ftm_pulse_clean(FTM1) ;
    DELAY_MS(10);
    speed_right = ftm_pulse_get(FTM1);
    
    if(PTF6_IN==0)
    {
      count_right = -speed_right;
    }
    else
    {
      count_right=speed_right;
      
    }
    if(PTF7_IN==1)
    {
      count_left=-speed_left;
    }
    else
    {
      count_left=speed_left;
    }
}


/*!
 *  @brief      电机测速方向中断
 *  Sample usage:   PTE0、PTE7下降沿触发
 */
/*void  kbi1_irq(void)
{
    if(IS_KBI1_IRQ())       //判断是否有效的KBI中断
    {
        if(IS_KBI_CH_IRQ(PTE0)) //判断是否PTE0触发的中断
        {
            if(PTF0_IN==1)
            {
              dir_left=1;
            }
            else
            {
              dir_left=0;
            }
        }
        
        if(IS_KBI_CH_IRQ(PTE7)) //判断是否PTE7触发的中断
        {
            if(PTF1_IN==0)
            {
              dir_right=1;
            }
            else
            {
              dir_right=0;
            }
        }
    }

    KBI1_CLEAN_FLAG() ;
}*/