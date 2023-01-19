//
// Created by WYH on 2023/1/19.
//

#include "Servo.h"


void Servo_init()
{
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1500);
}

void Servo_angle(uint8_t angle)
{
    switch (angle) {
        case 0:
            __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,500); //-90業
            break;
        case 1:
            __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1000); //-45業
            break;
        case 2:
            __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,1500); //0業
            break;
        case 3:
            __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,2000); //45業
            break;
        case 4:
            __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,2500); //90業
            break;
        default:
            printf("error\n");
    }
}

