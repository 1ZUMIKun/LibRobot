#include "stm32f4xx_hal.h"

#define vk       (1000.0)           //平移系数
#define X_value  (vk*0.5)           //左右方向速度系数
#define Y_value  (vk*0.8660254038)  //前后方向速度系数
#define L_value  (2.0)              //旋转系数，轮子到轴的距离
#define Max_PWM  (5000)

typedef struct {
    uint8_t Class;
    uint8_t Number;
    uint8_t Mode;
    int16_t realCurrent;
    int16_t realVelocity;
    int32_t realPosition;
    uint8_t CTL1;
    uint8_t CTL2;
    uint8_t DSIN;
    uint16_t ASIN;
    int16_t realPWM;
    CAN_HandleTypeDef* hcan;
} MotorDataType;

void PrintMotorState(MotorDataType* Motor);
void ChassisDriverV(MotorDataType* Motor, double vX,double vY,double vYaw);

void MotorReset(CAN_HandleTypeDef* hcan, uint16_t ID);                     //单个电机：0x+组号(0-7)+编号(1-F)+功能序号(0) 广播：0x+组号(0-7)+编号(0)+功能序号(0)
void MotorModeChoose(CAN_HandleTypeDef* hcan, uint16_t ID, uint8_t Mode);  //单个电机：0x+组号(0-7)+编号(1-F)+功能序号(1) 广播：0x+组号(0-7)+编号(0)+功能序号(1)
void MotorOC(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm);      //功能序号(2)开环模式
void MotorV(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm, int16_t temp_velocity);       //功能序号(4)速度模式
void MotorVP(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm, int16_t temp_velocity, int32_t temp_position);    //功能序号(6)速度位置模式
void MotorReportCAN(CAN_HandleTypeDef* hcan, uint16_t ID, uint8_t t1, uint8_t t2); //功能序号(A),t1为电流速度位置发送周期，t2为电平状态、pwm值发送周期


void MotorReset2(MotorDataType* Motor);                     
void MotorModeChoose2(MotorDataType* Motor, uint8_t Mode);                      //更改电机模式
void MotorOC2(MotorDataType* Motor, int16_t temp_pwm);                          //功能序号(2)开环模式
void MotorV2(MotorDataType* Motor, int16_t temp_pwm, int16_t temp_velocity);    //功能序号(4)速度模式
void MotorVP2(MotorDataType* Motor, int16_t temp_pwm, int16_t temp_velocity, int32_t temp_position);    //功能序号(6)速度位置模式
void MotorReportCAN2(MotorDataType* Motor, uint8_t t1, uint8_t t2);             //功能序号(A),t1为电流速度位置发送周期，t2为电平状态、pwm值发送周期


