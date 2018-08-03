#ifndef _PID_H_
#define _PID_H_

/*
********�������ͷ�ļ�******
@file     PID.h
@author   ��ѧ�����������һ��
@date     2018-3-10
*/



/*!
 *  @brief      ����PID�ṹ�弰���Ա
 *  Sample usage:   
 */
typedef struct PID 
{ 
    float SetPoint;//�趨Ŀ�� Desired Value 
    long SumError; //����ۼ�
    float Proportion; //�������� Proportional Const 
    float Integral; //���ֳ��� Integral Const 
    float Derivative; //΢�ֳ��� Derivative Const 
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