//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

// ����ת�ټ�����صı���
int last_encoder_count = 0;
int pulse_count = 0;
int rpm = 0;

/* ��ʼ�� TIM2/TIM3 ��ʱ��Ϊ������ģʽ */
void Encoder_init(void) {
  /* ���� TIM2/TIM3 ��ʱ���ı�����ģʽ */
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

// ������ת�ٵĺ���
int Calculate_Motor_RPM(int motor_value)
{
		
    // ������ת�٣���λΪRPM��
    rpm = motor_value * 60 / (4 * 13 * 30); // �����ı�Ƶ�ͼ��ٱȶ�����֪��
		
    return rpm;
}
