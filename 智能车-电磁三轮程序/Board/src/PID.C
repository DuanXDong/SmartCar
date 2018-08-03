#include "PID.h"
#include "common.h"
#include "include.h"

/*
********电机设置源文件******
@file     PID.c
@author   段学东、李兢兢、张一翔
@date     2018-3-10
*/



/*!
 *  @brief      PID 参数初始化
 *  Sample usage:   
 */
void IncPIDInit(void) 
{ 
  
    s_PID.SumError = 0; 
    s_PID.LastError = 0; //Error[-1] 
    s_PID.PrevError = 0; //Error[-2] 
    s_PID.Proportion =0; //比例常数 Proportional Const 
    s_PID.Integral = 0; //积分常数 Integral Const 
    s_PID.Derivative = 0; //0.055微分常数 Derivative Const 
    s_PID.SetPoint = 0;
    
   
    d_PID.SumError = 0; 
    d_PID.LastError = 0; //Error[-1] 
    d_PID.PrevError = 0; //Error[-2] 
    d_PID.Proportion =0; //比例常数 Proportional Const 
    d_PID.Integral =0; //积分常数 Integral Const 
    d_PID.Derivative =0; //微分常数 Derivative Const 
    d_PID.SetPoint = 0;
    
    R_PID.SumError = 0; 
    R_PID.LastError = 0; //Error[-1] 
    R_PID.PrevError = 0; //Error[-2] 
    R_PID.Proportion =0; //比例常数 Proportional Const 
    R_PID.Integral =0; //积分常数 Integral Const 
    R_PID.Derivative =0; //微分常数 Derivative Const 
    R_PID.SetPoint = 0;
    
    d_d_PID.SumError = 0; 
    d_d_PID.LastError = 0; //Error[-1] 
    d_d_PID.PrevError = 0; //Error[-2] 
    d_d_PID.Proportion =0; //比例常数 Proportional Const 
    d_d_PID.Integral =0; //积分常数 Integral Const 
    d_d_PID.Derivative =0; //微分常数 Derivative Const 
    d_d_PID.SetPoint = 0;
    
    
}

/*!
 *  @brief      速度PID函数
 *  @param      Speed_L   左电机测出的速度值
 *  @param      Speed_R   右电机测出的速度值
 *  Sample usage:   
 */
float Speed_PID(int Speed_L,int Speed_R)
{
    register float iError, Speed_out,Speed;    //当前误差
    Speed = (float)((Speed_L+Speed_R)/2.0);
    iError = s_PID.SetPoint - Speed;   //增量计算  
    Speed_out = s_PID.Proportion * iError - s_PID.Integral * s_PID.LastError + s_PID.Derivative * s_PID.PrevError; 
                                 //E[k]项                         //E[k－1]项                          //E[k－2]项
    s_PID.PrevError = s_PID.LastError;   //存储误差，用于下次计算 
    s_PID.LastError = iError;   //返回增量值

    return(Speed_out);
}


/*!
 *  @brief      方向内环PID函数
 *  Sample usage:   
 */
float dir_PID()
{
  register float iError,Dir_out,dError;
  iError = dianci_manage();
  d_PID.SumError += iError; //积分
  dError = iError - d_PID.LastError; //微分                                                                       
  d_PID.LastError = iError;
  Dir_out = d_PID.Proportion * iError + d_PID.Integral * d_PID.SumError + d_PID.Derivative * dError;    
  return(Dir_out);
}

float dir_R_PID()
{
  register float iError,Dir_out,dError;
  iError = dianci_manage();
  R_PID.SumError += iError; //积分
  dError = iError - R_PID.LastError; //微分                                                                       
  R_PID.LastError = iError;
  Dir_out = R_PID.Proportion * iError + R_PID.Integral * R_PID.SumError +R_PID.Derivative * dError;    
  return(Dir_out);
}
/*!
 *  @brief      方向外环PID函数
 *  Sample usage:   
 */
float dir_d_PID(float NowData, float Point)
{
  register float iError,Dir_d_out,dError;
  iError = Point - NowData;
  d_d_PID.SumError += iError; //积分
  dError = iError - d_d_PID.LastError; //微分                                                                       
  d_d_PID.LastError = iError;
  Dir_d_out = d_d_PID.Proportion * iError + d_d_PID.Integral * d_d_PID.SumError + d_d_PID.Derivative * dError;    
  return(Dir_d_out);
}


/*!
 *  @brief      设置方向内环PID参数
 *  Sample usage:   
 */    
void set_d_PID(float P,float I,float D)
{
    d_PID.Proportion = P;
    d_PID.Integral = I;
    d_PID.Derivative =D;
}    
void set_R_PID(float P,float I,float D)
{
    R_PID.Proportion = P;
    R_PID.Integral = I;
    R_PID.Derivative =D;
}    
/*!
 *  @brief      设置方向外环PID参数
 *  Sample usage:   
 */    
void set_d_d_PID(float P,float I,float D)
{
    d_d_PID.Proportion = P;
    d_d_PID.Integral = I;
    d_d_PID.Derivative =D;
}    
/*!
 *  @brief      设置速度PID参数
 *  Sample usage:   
 */    
void set_s_PID(float P,float I,float D)
{
    s_PID.Proportion = P;
    s_PID.Integral = I;
    s_PID.Derivative = D;
}

/*!
 *  @brief      设置速度目标值
 *  Sample usage:   
 */    
void set_Speed(float speed)
{
  s_PID.SetPoint = speed;
}