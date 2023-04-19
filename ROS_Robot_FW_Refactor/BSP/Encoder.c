//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

// 定义转速计算相关的变量
int last_encoder_count = 0;
int pulse_count = 0;
int rpm = 0;

/* 初始化 TIM2/TIM3 定时器为编码器模式 */
void Encoder_init(void) {
  /* 启动 TIM2/TIM3 定时器的编码器模式 */
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

int Read_Encoder(uint8_t TIMX)
{
  int Encoder_TIM;
  switch (TIMX)
  {
  case 2:Encoder_TIM = (short)TIM2 -> CNT; TIM2 -> CNT = 0;break;
  case 3:Encoder_TIM = (short)TIM3 -> CNT; TIM3 -> CNT = 0;break;
  default: Encoder_TIM = 0;
  }
  return Encoder_TIM;
}

// 计算电机转速的函数
int Calculate_Motor_RPM(int motor_value)
{
		
    // 计算电机转速（单位为RPM）
    rpm = motor_value * 60 / (4 * 13 * 30); // 假设四倍频和减速比都是已知的
		
    return rpm;
}
