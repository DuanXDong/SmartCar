/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2017,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��KEA ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v6.0
 * @date       2017-12-10
 */


#include "common.h"
#include "include.h"

float var[6];

Site_t site;

float L_R_flag;
int i;
int start_flag=0;
int stop_i;
int stop_flag=0;
int mode=0;
uint8 start_f=0;
uint8 flag;

/*!
 *  @brief      main����
 *  @since      v1.0
 *  @note       ���ֳ�������
 */
 void  main(void)
{
    AllInit();
     
    while(1)
    {
        if(start_f == 1)
        {
            if(gpio_get(PTH3)==0&&gpio_get(PTH2)==1&&gpio_get(PTH1)==1&&gpio_get(PTH0)==1)
            {
                mode=1;
            }
            else if(gpio_get(PTH3)==1&&gpio_get(PTH2)==0&&gpio_get(PTH1)==1&&gpio_get(PTH0)==1)
            {
                mode=2;
            }
            else if(gpio_get(PTH3)==1&&gpio_get(PTH2)==1&&gpio_get(PTH1)==0&&gpio_get(PTH0)==1)
            {
                mode=3;
            }
            else if(gpio_get(PTH3)==1&&gpio_get(PTH2)==1&&gpio_get(PTH1)==1&&gpio_get(PTH0)==0)
            {
                mode=4;
            }
            else
            {
              set_Speed(0);
            }
            
            switch(mode)
          {
            case 1: set_s_PID(2.0,1.85,0);                  //speed:35
                    set_d_PID(0.10,0,0.5);                  //speed:35
                    set_R_PID(0.039,0,0.95);
                    set_Speed(35);
            break;
            case 2:if(speed_flag==1)
                    {
                      set_s_PID(2.0,1.85,0);                  //speed:35
                      set_d_PID(0.10,0,0.5);                  //speed:35
                      set_R_PID(0.041,0,0.95);
                      set_Speed(35);
                    }
                     else
                    {   
                          set_s_PID(2.0,1.85,0);                  //speed:55
                          set_d_PID(0.20,0,0.9);   
                          set_Speed(55);
                    }
                    
                      
                    
            break;
            case 3: if(speed_flag==1)
                    {
                      set_s_PID(2.0,1.85,0);                  //speed:35
                      set_d_PID(0.10,0,0.5);                  //speed:35
                      set_R_PID(0.041,0,0.95);
                      set_Speed(35);
                    }
                     else
                    {   
                          set_s_PID(2.0,1.85,0);                  //speed:55
                          set_d_PID(0.3,0,0.9);   
                          set_Speed(70);
                    }
            break;
            case 4:if(speed_flag==1)
                    {
                      set_s_PID(2.0,1.85,0);                  //speed:35
                      set_d_PID(0.10,0,0.5);                  //speed:35
                      set_R_PID(0.041,0,0.95);
                      set_Speed(35);
                    }
                     else
                    {   
                          set_s_PID(2.0,1.85,0);                  //speed:55
                          set_d_PID(0.20,0,0.9);   
                          set_Speed(65);
                    }
              break;
                      
          default:
            break;
          }
        }
        else
        {
          set_Speed(0);
        }
        if(gpio_get(PTH4)==0)
        {
              site.x = 60;
              site.y = 10;
              lcd_num_bc(site, Tracking_Sensor_data_L,4, BLUE, RED);
        
              site.y = 30;
              lcd_num_bc(site, Tracking_Sensor_data_L_L,4, BLUE, RED);
        
              site.y = 50;
              lcd_num_bc(site, Tracking_Sensor_data_R_R,4, BLUE, RED);
                      
              site.y = 70;
              lcd_num_bc(site, Tracking_Sensor_data_R,4, BLUE, RED);

        }  
        if(key_check(KEY_A) == KEY_DOWN) //���key״̬������ʱ������
        {
            DELAY_MS(500);  
            start_f = 1;
            i=0;

        }
        if(key_check(KEY_B) == KEY_DOWN) //���key״̬������ʱ������
        {
            start_f = 0;
            i=0;
            set_Speed(0);
        }
    }
}





