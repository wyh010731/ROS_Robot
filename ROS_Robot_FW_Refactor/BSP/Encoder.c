//
// Created by WYH on 2023/2/22.
//

#include "Encoder.h"

// �����������ʱ���
static uint32_t timestamp1 = 0;
static uint32_t timestamp2 = 0;
static uint32_t count1 = 0;
static uint32_t count2 = 0;

// ����ת�ٱ���
static float speed1 = 0;
static float speed2 = 0;

/* ��ʼ�� TIM2/TIM3 ��ʱ��Ϊ������ģʽ */
void Encoder_init(void) {
  /* ���� TIM2/TIM3 ��ʱ���ı�����ģʽ */
  HAL_TIM_Encoder_Start(&htim2, TIM_CHANNEL_ALL);
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

// �жϻص�����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
  if (htim->Instance == TIM2) {
    // ������1���ٶ�
    speed1 = Calculate_Speed(count1, &timestamp1, &htim2);
  } else if (htim->Instance == TIM3) {
    // ������2���ٶ�
    speed2 = Calculate_Speed(count2, &timestamp2, &htim3);
  }
}


// �������ٶȵĺ���
float Calculate_Speed(uint32_t count, uint32_t* timestamp, TIM_HandleTypeDef* htim) {
  // ��ȡ��ǰʱ��
  uint32_t current_time = HAL_GetTick();

  // �������ٶ�
  float speed = (count * 4 - __HAL_TIM_GET_COUNTER(htim)) * 60.0 / (1000.0 * (current_time - *timestamp));

  // ����ʱ����ͼ�����
  *timestamp = current_time;
  count = __HAL_TIM_GET_COUNTER(htim);

  return speed;
}


// ��ȡ���1���ٶ�
void Get_Motor1_Speed(void) {
  // ������1���ٶ�
  speed1 = Calculate_Speed(count1, &timestamp1, &htim2);

  // ��ӡ����ٶ�
  printf("Motor 1 speed: %f RPM\r\n", speed1);
}

// ��ȡ���2���ٶ�
void Get_Motor2_Speed(void) {
  // ������2���ٶ�
  speed2 = Calculate_Speed(count2, &timestamp2, &htim3);

  // ��ӡ����ٶ�
  printf("Motor 2 speed: %f RPM\r\n", speed2);
}
