#include "common.h"
#include "include.h"
#include "Init.h"

/*
********��ʼ��Դ�ļ�******
@file     Double_Motor.c
@author   ��ѧ�����������һ��
@date     2018-1-27
*/

void AllInit()
{
  
    led_init(LED3);             //led��ʼ��
    led_init(LED2);
    led_init(LED1);
    led_init(LED0);
    
    lcd_init();                 //lcd��ʼ��
    
    IIC_init();                 //iic��ʼ����������ʹ��
    while (MPU6050_Init());     //�����ǳ�ʼ��
    MPU6050_Offset();            //�����ǲɼ���ƫ
    
    Double_Motor_init(20000,0);   //�����ʼ��
    
    IncPIDInit();                 //PID��ʼ��
    
    dianci_init();                //��Ųɼ���ʼ��
    
    
    //IO�ڳ�ʼ��
    gpio_init(PTF0,GPI,0);      
    gpio_init(PTF1,GPI,0);
    
    gpio_init(PTH0,GPI,1);      //���뿪��
    gpio_init(PTH1,GPI,1);
    gpio_init(PTH2,GPI,1);
    gpio_init(PTH3,GPI,1);
    gpio_init(PTH4,GPI,1);
    gpio_init(PTH5,GPI,1);
    gpio_init(PTH6,GPI,1);
    gpio_init(PTH7,GPI,1);
    port_pull(PTH0,ENABLE);     //����ʹ��
    port_pull(PTH1,ENABLE);
    port_pull(PTH2,ENABLE);
    port_pull(PTH3,ENABLE);
    port_pull(PTH4,ENABLE);
    port_pull(PTH5,ENABLE);
    port_pull(PTH6,ENABLE);
    port_pull(PTH7,ENABLE);
    
    key_init(KEY_A);            //������ʼ��
    key_init(KEY_B);
    
    gpio_init(PTE5,GPI,0);      //ͣ�����
    port_pull(PTE5,ENABLE);
    kbi_init (PTE5, KBI_PULLUP_EN | KBI_FALLING) ;    
    DELAY_MS(1);        //�Ա�����ʹ��PTE5���ָߵ�ƽ    
    KBI1_CLEAN_FLAG();    
    kbi_enable_irq(PTE5);    

    pit_init_ms(PIT0, 50);                                //  ��ʱ 50ms
    enable_irq(PIT_CH0_IRQn);                             // ʹ��PIT_CH0�ж�

    systick_timing_ms(10);                       //��ʼ���δ�ʱ������ʱʱ��Ϊ�� 10ms
    
    Measurement_speed_init();           //˫������ٳ�ʼ��
    site.x = 0;    
    site.y = 10;    
    lcd_str(site, "L:", BLUE, RED);    
  
    site.y = 30;    
    lcd_str(site, "L_L:", BLUE, RED);    
  
    site.y = 50;    
    lcd_str(site, "R_R:", BLUE, RED);    
  
    site.y = 70;    
    lcd_str(site, "R:", BLUE, RED);
    EnableInterrupts;                   //���ж�
}