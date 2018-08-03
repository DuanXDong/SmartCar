#include "dianci.h"
#include "include.h"
#include "math.h"

/*
********电机设置源文件******
@file     dianci.c
@author   段学东、李兢兢、张一翔
@date     2018-3-10
*/

int RoundCenterStart_L=0;
int RoundCenterStart_R=0;
int RoundCenterStart_1=0;
int RoundCenterStart_2=0;
int RoundCenterStart_3=0;
int RoundCenterStart_4=0;
int RoundCenterStart_5=0;
int RoundCenterStart_6=0;
int RoundCenterStart_7=0;
int RoundOutFlag=0;
int speed_flag=0;
int RoundI=0;
int RoundJ=0;

float    point_center=0;            //总偏差 


int16 Tracking_ADC_Val_Temp_L[10];                       //循迹传感器AD转换值缓存
int16 Tracking_ADC_Val_Temp_L_L[10];
int16 Tracking_ADC_Val_Temp_C[10]; 
int16 Tracking_ADC_Val_Temp_R_R[10];
int16 Tracking_ADC_Val_Temp_R[10];                      //循迹传感器AD转换值缓存

uint16  Weighted_Ration[10]={4,6,7,8,10,15,20,30,200,700};      //权值数组 参数未实验 1000 
uint16  Weighted_Ration_add=1000;                      //全值数组和值

int32 Tracking_Sensor_data_L=0; 
int32 Tracking_Sensor_data_L_L=0;
int32 Tracking_Sensor_data_C=0;
int32 Tracking_Sensor_data_R_R=0;
int32 Tracking_Sensor_data_R=0;                             //循迹传感器加权平均滤波后值

float Tracking_Sensor_data_MAX=0; 

int32 Tracking_Sensor_data_L_record[10];                //加权滤波后的每个电感值记录数组
int32 Tracking_Sensor_data_L_L_record[10];
int32 Tracking_Sensor_data_C_record[10];  
int32 Tracking_Sensor_data_R_R_record[10];  
int32 Tracking_Sensor_data_R_record[10];           

int32 Tracking_ADC_Val_Sum_L=0;	
int32 Tracking_ADC_Val_Sum_L_L=0;
int32 Tracking_ADC_Val_Sum_C=0;	
int32 Tracking_ADC_Val_Sum_R_R=0;	
int32 Tracking_ADC_Val_Sum_R=0;		                  //循迹传感器AD转换值和   


float Tracking_ADC_Val_Sum=0;                           //内部左右电感和
float Tracking_ADC_Val_Sub=0;                           //内部左右电感差


float point_center_record[10]={0};                        //赛道偏差保存


/*!
 *  @brief      电磁采集初始化
 *  Sample usage:   
 */
void dianci_init(void)
{
    adc_init(ADC0_SE2);              //ADC初始化
    adc_init(ADC0_SE3);
    adc_init(ADC0_SE4);
    adc_init(ADC0_SE5);
    adc_init(ADC0_SE6);
    adc_init(ADC0_SE7);
}
  

/*!
 *  @brief      电磁采集
 *  Sample usage:   1-6个电感
 */
int16 dianci_1(void)
{
  int16 var;
  var = adc_once(ADC0_SE2, ADC_8bit);
  return(var);
}
int16 dianci_2(void)
{
  uint16 var;
  var = adc_once(ADC0_SE3, ADC_8bit);
  return(var);
}
int16 dianci_3(void)
{
  uint16 var;
  var = adc_once(ADC0_SE4, ADC_8bit);
  return(var);
}
int16 dianci_4(void)
{
  uint16 var;
  var = adc_once(ADC0_SE5, ADC_8bit);
  return(var);
}
int16 dianci_5(void)
{
  uint16 var;
  var = adc_once(ADC0_SE6, ADC_8bit);
  return(var);
}
int16 dianci_6(void)
{
  int16 var;
  var = adc_once(ADC0_SE7, ADC_8bit);
  return(var);
}


/*!
 *  @brief      电磁采集处理
 *  Sample usage:   采用（平方的差）比和
 */

float dianci_manage(void)
{
    char i=0,j=0;
  
    for(i=0;i<9;i++)//单次采集递推赋值并更新
    {
        Tracking_ADC_Val_Temp_L[i]=Tracking_ADC_Val_Temp_L[i+1];
        Tracking_ADC_Val_Temp_R[i]=Tracking_ADC_Val_Temp_R[i+1];
        Tracking_ADC_Val_Temp_C[i]=Tracking_ADC_Val_Temp_C[i+1];
        Tracking_ADC_Val_Temp_L_L[i]=Tracking_ADC_Val_Temp_L_L[i+1];
        Tracking_ADC_Val_Temp_R_R[i]=Tracking_ADC_Val_Temp_R_R[i+1];
     }
    Tracking_ADC_Val_Temp_L[9] = dianci_4();
    Tracking_ADC_Val_Temp_L_L[9] = dianci_3();
    Tracking_ADC_Val_Temp_C[9] = dianci_5();
    Tracking_ADC_Val_Temp_R_R[9] = dianci_2();
    Tracking_ADC_Val_Temp_R[9] = dianci_1();
    
    for(j=0;j<10;j++)
  {
    Tracking_ADC_Val_Sum_L+= Tracking_ADC_Val_Temp_L[j]* Weighted_Ration[j];
    Tracking_ADC_Val_Sum_L_L+= Tracking_ADC_Val_Temp_L_L[j]* Weighted_Ration[j];
    Tracking_ADC_Val_Sum_C+= Tracking_ADC_Val_Temp_C[j]* Weighted_Ration[j];
    Tracking_ADC_Val_Sum_R_R+= Tracking_ADC_Val_Temp_R_R[j]* Weighted_Ration[j];
    Tracking_ADC_Val_Sum_R+= Tracking_ADC_Val_Temp_R[j]* Weighted_Ration[j];
    
   
  }
  
   Tracking_Sensor_data_L=Tracking_ADC_Val_Sum_L/ Weighted_Ration_add; 
   Tracking_Sensor_data_L_L=Tracking_ADC_Val_Sum_L_L/ Weighted_Ration_add;
   Tracking_Sensor_data_C=Tracking_ADC_Val_Sum_C/ Weighted_Ration_add;
   Tracking_Sensor_data_R_R=Tracking_ADC_Val_Sum_R_R/ Weighted_Ration_add; 
   Tracking_Sensor_data_R=Tracking_ADC_Val_Sum_R/ Weighted_Ration_add; 
   
   Tracking_Sensor_data_L=(int32) Tracking_Sensor_data_L;
   Tracking_Sensor_data_L_L=(int32) Tracking_Sensor_data_L_L;
   Tracking_Sensor_data_C=(int32) Tracking_Sensor_data_C;
   Tracking_Sensor_data_R_R=(int32) Tracking_Sensor_data_R_R;
   Tracking_Sensor_data_R=(int32) Tracking_Sensor_data_R;
     
   if(Tracking_Sensor_data_L<1) Tracking_Sensor_data_L=1;
   if(Tracking_Sensor_data_L_L<1) Tracking_Sensor_data_L_L=1;
   if(Tracking_Sensor_data_C<1) Tracking_Sensor_data_C=1;
   if(Tracking_Sensor_data_R_R<1) Tracking_Sensor_data_R_R=1;
   if(Tracking_Sensor_data_R<1) Tracking_Sensor_data_R=1;
   
          var[1] = Tracking_Sensor_data_L;
          var[2] = Tracking_Sensor_data_L_L;
          var[3] = (count_left+count_right)/2;
          var[4] = Tracking_Sensor_data_R_R;
          var[5] = Tracking_Sensor_data_R;
   if(Tracking_Sensor_data_L_L-Tracking_Sensor_data_R_R>=40&&Tracking_Sensor_data_R_R<=5&&RoundCenterStart_2==0)
   {
       RoundCenterStart_R=0;
       RoundCenterStart_L=1;
   }
   else if(Tracking_Sensor_data_R_R-Tracking_Sensor_data_L_L>=40&&Tracking_Sensor_data_L_L<=5&&RoundCenterStart_2==0)
   {
     RoundCenterStart_L=0;
     RoundCenterStart_R=1;
   }

    if(Tracking_Sensor_data_L>=180&&Tracking_Sensor_data_R>=180&&Tracking_Sensor_data_R_R<=10&&Tracking_Sensor_data_L_L<=10&&(RoundCenterStart_L==1||RoundCenterStart_R==1))
    {
         RoundCenterStart_2=1;
         speed_flag=1;
       
    }
   if(RoundCenterStart_2==1&&(Tracking_Sensor_data_L_L-Tracking_Sensor_data_R_R>=40||Tracking_Sensor_data_R_R-Tracking_Sensor_data_L_L>=40))
   {
     RoundCenterStart_3=1;
   }
   if(RoundCenterStart_3==1)
   {
     Tracking_ADC_Val_Sub=sqrt(Tracking_Sensor_data_L_L)-sqrt(Tracking_Sensor_data_R_R);
     Tracking_ADC_Val_Sum=Tracking_Sensor_data_L_L+Tracking_Sensor_data_R_R;
     point_center=10000*Tracking_ADC_Val_Sub/Tracking_ADC_Val_Sum; //差和比得到偏差
     RoundCenterStart_4++;
     if(RoundCenterStart_4>=60)
     {
        RoundCenterStart_4=60;
        RoundCenterStart_5=1;
        RoundCenterStart_3=0;
     }
   }
   if(RoundCenterStart_3==0&&RoundCenterStart_5==1)
   {
     Tracking_ADC_Val_Sub=sqrt(Tracking_Sensor_data_L)-sqrt(Tracking_Sensor_data_R+sqrt(Tracking_Sensor_data_L_L)-sqrt(Tracking_Sensor_data_R_R));
     Tracking_ADC_Val_Sum=Tracking_Sensor_data_L+Tracking_Sensor_data_R;
     point_center=10000*Tracking_ADC_Val_Sub/Tracking_ADC_Val_Sum; //差和比得到偏差
     if(Tracking_Sensor_data_R_R>=80&&Tracking_Sensor_data_L_L>=80)
     {
       RoundCenterStart_5=0;
        RoundCenterStart_6=1;
     }
   }
   if(RoundCenterStart_6==1)
   {
     Tracking_ADC_Val_Sub=sqrt(Tracking_Sensor_data_L)-sqrt(Tracking_Sensor_data_R);
       Tracking_ADC_Val_Sum=Tracking_Sensor_data_L+Tracking_Sensor_data_R;
       point_center=10000*Tracking_ADC_Val_Sub/Tracking_ADC_Val_Sum; //差和比得到偏差
     RoundCenterStart_7++;
   }
   if(RoundCenterStart_7==60)
   {
        RoundCenterStart_R=0;
        RoundCenterStart_L=0;
        RoundCenterStart_2=0;
        RoundCenterStart_3=0;
        RoundCenterStart_4=0;
        RoundCenterStart_5=0;
        RoundCenterStart_6=0;
        speed_flag=0;
   }
   
   if(RoundCenterStart_2==0&&RoundCenterStart_3==0)
   {
     Tracking_ADC_Val_Sub=sqrt(Tracking_Sensor_data_L)-sqrt(Tracking_Sensor_data_R);
     Tracking_ADC_Val_Sum=Tracking_Sensor_data_L+Tracking_Sensor_data_R;
     point_center=10000*Tracking_ADC_Val_Sub/Tracking_ADC_Val_Sum; //差和比得到偏差
   }
   

    if(Tracking_Sensor_data_L<=0||Tracking_Sensor_data_R<=0)//防止数据错乱和串道
    {
        if(point_center_record[9]<0&&point_center_record[8]<0&&point_center_record[7]<0)
        {
          point_center=-660;                            //此处的值应该和你车身处于赛道极限位置的值相符
        }
        else if(point_center_record[9]>0&&point_center_record[8]>0&&point_center_record[7]>0)
        {
          point_center=660;
        }
        else
          point_center=0.8*point_center_record[8]+0.15*point_center_record[7]+0.05*point_center_record[6]; 

    }

    if(point_center>=660)//允许最大偏差
      point_center=660;
    if(point_center<=-660)
      point_center=-660;

    if(point_center<=40&&point_center>=-40)
    {
      point_center=0;
    }
    for(i=0;i<9;i++)
    {
      point_center_record[i]=point_center_record[i+1];
    }
    
    point_center_record[9]=point_center;


 
    Tracking_ADC_Val_Sum_R=0;
    Tracking_ADC_Val_Sum_R_R=0;
    Tracking_ADC_Val_Sum_C=0;
    Tracking_ADC_Val_Sum_L_L=0;
    Tracking_ADC_Val_Sum_L=0;

    var[0] = point_center;
    return point_center;
}

