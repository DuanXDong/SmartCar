#include "Measurement_speed.h"

/*
********�������Դ�ļ�******
@file     Measurement_speed.c
@author   ��ѧ�����������һ��
@date     2018-3-13
*/

int16_t count_left,count_right;         //ȫ�ֱ������ٶȴ�С
uint16 dir_left,dir_right;              //ȫ�ֱ����������־

int16_t count_left_l[10];
int16_t count_right_r[10];



/*!
 *  @brief      ˫������ٳ�ʼ��
 *  Sample usage:   
 */
void Measurement_speed_init(void)
{
  ftm_pulse_init(FTM1, FTM_PS_1, TCLK1);
  gpio_init(PTF7,GPI,0);
  gpio_init(PTF6,GPI,0);
}


/*!
 *  @brief      ˫������ٺ���
 *  Sample usage:   
 */
void Measurement_speed(void)
{
  int16_t speed_left,speed_right; 
    //ͨ�� ftm_pulse_mux �������ض������� �������������Ϊ TCLK1
    ftm_pulse_mux(FTM1, TCLK1);
    ftm_pulse_clean(FTM1) ;
    DELAY_MS(10);
    speed_left = ftm_pulse_get(FTM1);
    
    
    //ͨ�� ftm_pulse_mux �������ض������� �������������Ϊ TCLK2
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
 *  @brief      ������ٷ����ж�
 *  Sample usage:   PTE0��PTE7�½��ش���
 */
/*void  kbi1_irq(void)
{
    if(IS_KBI1_IRQ())       //�ж��Ƿ���Ч��KBI�ж�
    {
        if(IS_KBI_CH_IRQ(PTE0)) //�ж��Ƿ�PTE0�������ж�
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
        
        if(IS_KBI_CH_IRQ(PTE7)) //�ж��Ƿ�PTE7�������ж�
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