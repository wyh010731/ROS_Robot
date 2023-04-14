//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

// 定义计数器和时间戳
static uint32_t timestamp1 = 0;
static uint32_t timestamp2 = 0;
static uint32_t count1 = 0;
static uint32_t count2 = 0;

// 定义转速变量
static float speed1 = 0;
static float speed2 = 0;

/* 初始化 TIM2/TIM3 定时器为编码器模式 */
void Encoder_init(void) {
  /* 启动 TIM2/TIM3 定时器的编码器模式 */
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

// 中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    // 计算电机1的速度
    speed1 = Calculate_Speed(count1, &timestamp1, &htim2);
  } else if (htim->Instance == TIM3) {
    // 计算电机2的速度
    speed2 = Calculate_Speed(count2, &timestamp2, &htim3);
  }
}


// 计算电机速度的函数
float Calculate_Speed(uint32_t count, uint32_t* timestamp, TIM_HandleTypeDef* htim) {
  // 获取当前时间
  uint32_t current_time = HAL_GetTick();

  // 计算电机速度
  float speed = (count * 4 - __HAL_TIM_GET_COUNTER(htim)) * 60.0 / (1000.0 * (current_time - *timestamp));

  // 更新时间戳和计数器
  *timestamp = current_time;
  count = __HAL_TIM_GET_COUNTER(htim);

  return speed;
}


// 获取电机1的速度
void Get_Motor1_Speed(void) {
  // 计算电机1的速度
  speed1 = Calculate_Speed(count1, &timestamp1, &htim2);

  // 打印电机速度
  printf("Motor 1 speed: %f RPM\r\n", speed1);
}

// 获取电机2的速度
void Get_Motor2_Speed(void) {
  // 计算电机2的速度
  speed2 = Calculate_Speed(count2, &timestamp2, &htim3);

  // 打印电机速度
  printf("Motor 2 speed: %f RPM\r\n", speed2);
}
