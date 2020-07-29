#include "MotorDriver.h"
#include "stm32f4xx_hal.h"
#include "stdio.h"

void ChassisDriverV(MotorDataType* Motor, double vX, double vY, double vYaw){           //速度取0-1之间
    int16_t V1,V2,V3;
    V1 = (-X_value*vX + L_value*vYaw);
    V2 = (X_value*vX - Y_value*vY + L_value*vYaw);
    V3 = (X_value*vX + Y_value*vY + L_value*vYaw);
    MotorV2(&Motor[0], Max_PWM, V1);
    MotorV2(&Motor[1], Max_PWM, V2);
    MotorV2(&Motor[2], Max_PWM, V3);
}

void MotorReset2(MotorDataType* Motor){
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x00;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x00;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = 0x55;
    Motor->hcan->pTxMsg->Data[1] = 0x55;
    Motor->hcan->pTxMsg->Data[2] = 0x55;
    Motor->hcan->pTxMsg->Data[3] = 0x55;
    Motor->hcan->pTxMsg->Data[4] = 0x55;
    Motor->hcan->pTxMsg->Data[5] = 0x55;
    Motor->hcan->pTxMsg->Data[6] = 0x55;
    Motor->hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(Motor->hcan, 1);
}

void MotorModeChoose2(MotorDataType* Motor, uint8_t Mode){
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x01;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x01;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = Mode;
    Motor->hcan->pTxMsg->Data[1] = 0x55;
    Motor->hcan->pTxMsg->Data[2] = 0x55;
    Motor->hcan->pTxMsg->Data[3] = 0x55;
    Motor->hcan->pTxMsg->Data[4] = 0x55;
    Motor->hcan->pTxMsg->Data[5] = 0x55;
    Motor->hcan->pTxMsg->Data[6] = 0x55;
    Motor->hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(Motor->hcan, 1);
    Motor->Mode = Mode + 1;
}

void MotorOC2(MotorDataType* Motor, int16_t temp_pwm){
    if(Motor->Mode != 0x02){
        printf("OC Mode ERROR ,Mode=%d",Motor->Mode);
        return;
    }
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x04;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x04;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    Motor->hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    Motor->hcan->pTxMsg->Data[2] = 0x55;
    Motor->hcan->pTxMsg->Data[3] = 0x55;
    Motor->hcan->pTxMsg->Data[4] = 0x55;
    Motor->hcan->pTxMsg->Data[5] = 0x55;
    Motor->hcan->pTxMsg->Data[6] = 0x55;
    Motor->hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(Motor->hcan, 1);
}

void MotorV2(MotorDataType* Motor, int16_t temp_pwm, int16_t temp_velocity){
    if(Motor->Mode != 0x04){
        printf("V Mode ERROR ,Mode=%d",Motor->Mode);
        return;
    }
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x04;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x04;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    Motor->hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    Motor->hcan->pTxMsg->Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    Motor->hcan->pTxMsg->Data[3] = (unsigned char)(temp_velocity&0xff);
    Motor->hcan->pTxMsg->Data[4] = 0x55;
    Motor->hcan->pTxMsg->Data[5] = 0x55;
    Motor->hcan->pTxMsg->Data[6] = 0x55;
    Motor->hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(Motor->hcan, 1);
}

void MotorVP2(MotorDataType* Motor, int16_t temp_pwm, int16_t temp_velocity, int32_t temp_position){
    if(Motor->Mode != 0x06){
        printf("VP Mode ERROR ,Mode=%d",Motor->Mode);
        return;
    }
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x06;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x06;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    Motor->hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    Motor->hcan->pTxMsg->Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    Motor->hcan->pTxMsg->Data[3] = (unsigned char)(temp_velocity&0xff);
    Motor->hcan->pTxMsg->Data[4] = (unsigned char)((temp_position>>24)&0xff);
    Motor->hcan->pTxMsg->Data[5] = (unsigned char)((temp_position>>16)&0xff);
    Motor->hcan->pTxMsg->Data[6] = (unsigned char)((temp_position>>8)&0xff);
    Motor->hcan->pTxMsg->Data[7] = (unsigned char)(temp_position&0xff);
    HAL_CAN_Transmit(Motor->hcan, 1);
}

void MotorReportCAN2(MotorDataType* Motor, uint8_t t1, uint8_t t2){
    Motor->hcan->pTxMsg->StdId = (Motor->Class<<8) + (Motor->Number<<4) + 0x0A;
    Motor->hcan->pTxMsg->ExtId = (Motor->Class<<8) + (Motor->Number<<4) + 0x0A;
    Motor->hcan->pTxMsg->IDE = CAN_ID_STD;
    Motor->hcan->pTxMsg->RTR = CAN_RTR_DATA;
    Motor->hcan->pTxMsg->DLC = 8;
    Motor->hcan->pTxMsg->Data[0] = t1;
    Motor->hcan->pTxMsg->Data[1] = t2;
    Motor->hcan->pTxMsg->Data[2] = 0x55;
    Motor->hcan->pTxMsg->Data[3] = 0x55;
    Motor->hcan->pTxMsg->Data[4] = 0x55;
    Motor->hcan->pTxMsg->Data[5] = 0x55;
    Motor->hcan->pTxMsg->Data[6] = 0x55;
    Motor->hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(Motor->hcan, 1);
}

void PrintMotorState(MotorDataType* Motor){
    printf("id=%x,C=%dmA,V=%d,P=%d\n", Motor->Number, Motor->realCurrent, Motor->realVelocity, Motor->realPosition);
}







void MotorReset(CAN_HandleTypeDef* hcan, uint16_t ID) {
    hcan->pTxMsg->StdId = ID;             //设置标准标识符
    hcan->pTxMsg->ExtId = ID;             //设置扩展标示符
    hcan->pTxMsg->IDE = CAN_ID_STD;       //标准帧
    hcan->pTxMsg->RTR = CAN_RTR_DATA;     //数据帧
    hcan->pTxMsg->DLC = 8;                //要发送的数据长度
    hcan->pTxMsg->Data[0] = 0x55;
    hcan->pTxMsg->Data[1] = 0x55;
    hcan->pTxMsg->Data[2] = 0x55;
    hcan->pTxMsg->Data[3] = 0x55;
    hcan->pTxMsg->Data[4] = 0x55;
    hcan->pTxMsg->Data[5] = 0x55;
    hcan->pTxMsg->Data[6] = 0x55;
    hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(hcan, 1);
}

void MotorModeChoose(CAN_HandleTypeDef* hcan, uint16_t ID, uint8_t Mode) {
    hcan->pTxMsg->StdId = ID;
    hcan->pTxMsg->ExtId = ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 8;
    hcan->pTxMsg->Data[0] = Mode;
    hcan->pTxMsg->Data[1] = 0x55;
    hcan->pTxMsg->Data[2] = 0x55;
    hcan->pTxMsg->Data[3] = 0x55;
    hcan->pTxMsg->Data[4] = 0x55;
    hcan->pTxMsg->Data[5] = 0x55;
    hcan->pTxMsg->Data[6] = 0x55;
    hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(hcan, 1);
}

void MotorOC(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm) {
    hcan->pTxMsg->StdId = ID;
    hcan->pTxMsg->ExtId = ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 8;
    hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    hcan->pTxMsg->Data[2] = 0x55;
    hcan->pTxMsg->Data[3] = 0x55;
    hcan->pTxMsg->Data[4] = 0x55;
    hcan->pTxMsg->Data[5] = 0x55;
    hcan->pTxMsg->Data[6] = 0x55;
    hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(hcan, 1);
}

void MotorV(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm, int16_t temp_velocity){
    hcan->pTxMsg->StdId = ID;
    hcan->pTxMsg->ExtId = ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 8;
    hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    hcan->pTxMsg->Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    hcan->pTxMsg->Data[3] = (unsigned char)(temp_velocity&0xff);
    hcan->pTxMsg->Data[4] = 0x55;
    hcan->pTxMsg->Data[5] = 0x55;
    hcan->pTxMsg->Data[6] = 0x55;
    hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(hcan, 1);
}


void MotorVP(CAN_HandleTypeDef* hcan, uint16_t ID, int16_t temp_pwm, int16_t temp_velocity, int32_t temp_position){
    hcan->pTxMsg->StdId = ID;
    hcan->pTxMsg->ExtId = ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 8;
    hcan->pTxMsg->Data[0] = (unsigned char)((temp_pwm >> 8) & 0xff);
    hcan->pTxMsg->Data[1] = (unsigned char)(temp_pwm & 0xff);
    hcan->pTxMsg->Data[2] = (unsigned char)((temp_velocity>>8)&0xff);
    hcan->pTxMsg->Data[3] = (unsigned char)(temp_velocity&0xff);
    hcan->pTxMsg->Data[4] = (unsigned char)((temp_position>>24)&0xff);
    hcan->pTxMsg->Data[5] = (unsigned char)((temp_position>>16)&0xff);
    hcan->pTxMsg->Data[6] = (unsigned char)((temp_position>>8)&0xff);
    hcan->pTxMsg->Data[7] = (unsigned char)(temp_position&0xff);
    HAL_CAN_Transmit(hcan, 1);
}

void MotorReportCAN(CAN_HandleTypeDef* hcan, uint16_t ID, uint8_t t1, uint8_t t2){
    hcan->pTxMsg->StdId = ID;
    hcan->pTxMsg->ExtId = ID;
    hcan->pTxMsg->IDE = CAN_ID_STD;
    hcan->pTxMsg->RTR = CAN_RTR_DATA;
    hcan->pTxMsg->DLC = 8;
    hcan->pTxMsg->Data[0] = t1;
    hcan->pTxMsg->Data[1] = t2;
    hcan->pTxMsg->Data[2] = 0x55;
    hcan->pTxMsg->Data[3] = 0x55;
    hcan->pTxMsg->Data[4] = 0x55;
    hcan->pTxMsg->Data[5] = 0x55;
    hcan->pTxMsg->Data[6] = 0x55;
    hcan->pTxMsg->Data[7] = 0x55;
    HAL_CAN_Transmit(hcan, 1);

}

