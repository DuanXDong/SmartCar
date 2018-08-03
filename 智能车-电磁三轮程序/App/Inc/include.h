#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

#include "enter.h"
/*
 * Include 用户自定义的头文件
 */
#include "KEA_gpio.h"
#include "KEA_uart.h"
#include "KEA_adc.h"
#include "KEA_ftm.h"
#include "KEA_pit.h"
#include "KEA_SysTick.h"

#include "KEA_wdog.h"

#include "VCAN_LED.h"
#include "VCAN_key.h"
#include "VCAN_NRF24L0.h"
#include "VCAN_lcd.h"
#include "VCAN_computer.h"

#include "Init.h"
#include "Double_Motor.h"
#include "PID.h"
#include "dianci.h"
#include "control.h"
#include "Measurement_speed.h"

#include "MPU6050.h"
#include "My_I2C.h"


extern Site_t site;
extern float var[6];
extern float    point_center;
extern int stop_flag;
extern int start_flag;
extern uint8 start_f;
extern int stop_i;
extern int speed_flag;
extern int RoundI;
extern int mode;
extern int RoundCenterStart_2;
extern int RoundCenterStart_3;
extern int RoundCenterStart_4;
extern int RoundCenterStart_5;
extern int RoundCenterStart_6;
extern int RoundCenterStart_7;

extern int RoundCenterStart_L;
extern int RoundCenterStart_R;
extern int32 Tracking_Sensor_data_L;	
extern int32 Tracking_Sensor_data_L_L;
extern int32 Tracking_Sensor_data_C;	
extern int32 Tracking_Sensor_data_R_R;	
extern int32 Tracking_Sensor_data_R;	
extern int16_t count_left,count_right;
extern uint16 dir_left,dir_right;

#endif  //__INCLUDE_H__
