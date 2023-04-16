//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"


int32_t count1 = 0;
int32_t count2 = 0;


/* 初始化 TIM2/TIM3 定时器为编码器模式 */
void Encoder_init(void) {
  /* 启动 TIM2/TIM3 定时器的编码器模式 */
  HAL_TIM_Encoder_Start_IT(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start_IT(&htim3, TIM_CHANNEL_ALL);
}

// 中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    count1 += (int32_t)__HAL_TIM_GET_COUNTER(&htim2);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
    printf("Motor 1 count: %d\r\n", count1);
  } else if (htim->Instance == TIM3) {
    count2 += (int32_t)__HAL_TIM_GET_COUNTER(&htim3);
    __HAL_TIM_SET_COUNTER(&htim3, 0);
    printf("Motor 2 count: %d\r\n", count2);
  }
}
