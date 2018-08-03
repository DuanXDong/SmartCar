#ifndef _DIANCI_H_
#define _DIANCI_H_

/*
********�������ͷ�ļ�******
@file     dianci.h
@author   ��ѧ�����������һ��
@date     2018-3-10
*/

#include "common.h"

#define VPOWR  5000  //���ù����ѹ

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