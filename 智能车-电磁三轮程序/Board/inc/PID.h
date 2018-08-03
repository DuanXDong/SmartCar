#ifndef _PID_H_
#define _PID_H_

/*
********电机设置头文件******
@file     PID.h
@author   段学东、李兢兢、张一翔
@date     2018-3-10
*/



/*!
 *  @brief      定义PID结构体及其成员
 *  Sample usage:   
 */
typedef struct PID 
{ 
    float SetPoint;//设定目标 Desired Value 
    long SumError; //误差累计
    float Proportion; //比例常数 Proportional Const 
    float Integral; //积分常数 Integral Const 
    float Derivative; //微分常数 Derivative Const 
    float Td;
    float LastError; //Error[-1] 
    float PrevError; //Error[-2] 
}PID; 
 static PID s_PID,d_PID,R_PID,d_d_PID;


void IncPIDInit(void);
float Speed_PID(int Speed_L,int Speed_R);
float dir_PID();
float dir_R_PID();
float dir_d_PID(float NowData, float Point);
void set_d_PID(float P,float I,float D);
void set_R_PID(float P,float I,float D);
void set_d_d_PID(float P,float I,float D);
void set_s_PID(float P,float I,float D);
void set_Speed(float speed);

#endif