//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

struct Encoder{
    int Get_data;
    int Direction;
}encoder;

void Encoder_init()
{
    HAL_TIM_Encoder_Start(&htim2,TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(&htim3,TIM_CHANNEL_ALL);
}

uint8_t Encoder_Get_Data()
{
    encoder.Direction = __HAL_TIM_IS_TIM_COUNTING_DOWN(&htim2);
    encoder.Get_data = __HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_GET_COUNTER(&htim2) = 0;
    //printf("Encoder Data:%s",&Get_data);
    return encoder.Get_data;
}