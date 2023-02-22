//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

uint8_t Get_data=0;

void Encoder_init()
{
    HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

uint8_t Encoder_Get_Data()
{
    Get_data = __HAL_TIM_GET_COUNTER(&htim2);
    printf("Encoder Data:%s",&Get_data);
    return Get_data;
}