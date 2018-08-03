#include "common.h"
#include "include.h"
#include "Init.h"

/*
********初始化源文件******
@file     Double_Motor.c
@author   段学东、李兢兢、张一翔
@date     2018-1-27
*/

void AllInit()
{
  
    led_init(LED3);             //led初始化
    led_init(LED2);
    led_init(LED1);
    led_init(LED0);
    
    lcd_init();                 //lcd初始化
    
    IIC_init();                 //iic初始化，陀螺仪使用
    while (MPU6050_Init());     //陀螺仪初始化
    MPU6050_Offset();            //陀螺仪采集零偏
    
    Double_Motor_init(20000,0);   //电机初始化
    
    IncPIDInit();                 //PID初始化
    
    dianci_init();                //电磁采集初始化
    
    
    //IO口初始化
    gpio_init(PTF0,GPI,0);      
    gpio_init(PTF1,GPI,0);
    
    gpio_init(PTH0,GPI,1);      //拨码开关
    gpio_init(PTH1,GPI,1);
    gpio_init(PTH2,GPI,1);
    gpio_init(PTH3,GPI,1);
    gpio_init(PTH4,GPI,1);
    gpio_init(PTH5,GPI,1);
    gpio_init(PTH6,GPI,1);
    gpio_init(PTH7,GPI,1);
    port_pull(PTH0,ENABLE);     //上拉使能
    port_pull(PTH1,ENABLE);
    port_pull(PTH2,ENABLE);
    port_pull(PTH3,ENABLE);
    port_pull(PTH4,ENABLE);
    port_pull(PTH5,ENABLE);
    port_pull(PTH6,ENABLE);
    port_pull(PTH7,ENABLE);
    
    key_init(KEY_A);            //按键初始化
    key_init(KEY_B);
    
    gpio_init(PTE5,GPI,0);      //停车检测
    port_pull(PTE5,ENABLE);
    kbi_init (PTE5, KBI_PULLUP_EN | KBI_FALLING) ;    
    DELAY_MS(1);        //以便上拉使得PTE5保持高电平    
    KBI1_CLEAN_FLAG();    
    kbi_enable_irq(PTE5);    

    pit_init_ms(PIT0, 50);                                //  定时 50ms
    enable_irq(PIT_CH0_IRQn);                             // 使能PIT_CH0中断

    systick_timing_ms(10);                       //初始化滴答定时器，定时时间为： 10ms
    
    Measurement_speed_init();           //双电机测速初始化
    site.x = 0;    
    site.y = 10;    
    lcd_str(site, "L:", BLUE, RED);    
  
    site.y = 30;    
    lcd_str(site, "L_L:", BLUE, RED);    
  
    site.y = 50;    
    lcd_str(site, "R_R:", BLUE, RED);    
  
    site.y = 70;    
    lcd_str(site, "R:", BLUE, RED);
    EnableInterrupts;                   //开中断
}