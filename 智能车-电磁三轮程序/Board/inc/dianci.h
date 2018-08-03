#ifndef _DIANCI_H_
#define _DIANCI_H_

/*
********电机设置头文件******
@file     dianci.h
@author   段学东、李兢兢、张一翔
@date     2018-3-10
*/

#include "common.h"

#define VPOWR  5000  //设置供电电压

extern float    point_center;

extern int32 Tracking_Sensor_data_L; 
extern int32 Tracking_Sensor_data_L_L;
extern int32 Tracking_Sensor_data_C;
extern int32 Tracking_Sensor_data_R_R;
extern int32 Tracking_Sensor_data_R;     





void dianci_init(void);
int16 dianci_1(void);
int16 dianci_2(void);
int16 dianci_3(void);
int16 dianci_4(void);
int16 dianci_5(void);
int16 dianci_6(void);

float dianci_manage(void);



#endif