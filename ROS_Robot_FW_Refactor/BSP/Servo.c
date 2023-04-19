//
// Created by WYH on 2023/1/19.
//

#include "Servo.h"

/* �������ĽǶȱ��� */
uint16_t servo_angle = 90; // ��ʼ�Ƕ�Ϊ90��

/* ���ƶ���Ƕȳ�ʼ������ */
void Servo_init()
{
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 1500);
}

/* ���ƶ��ת���ĺ��� */
void set_servo_rotation(int angular_velocity)
{
    int new_angular_velocity = calculate_servo_pulse(angular_velocity);
    /* ����PWM����������� */
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, new_angular_velocity);
}

/* ������PWM����ĺ��� */
uint16_t calculate_servo_pulse(int angular_velocity_pulse)
{
    uint16_t initial_pulse = 1500;
    int max_angular_velocity_pulse = 200;                                                  // �����ٶ�����
    int max_angle_diff = 45;                                                               // ���ǶȲ�
    int angle_diff = max_angle_diff * angular_velocity_pulse / max_angular_velocity_pulse; // ����ǶȲ�
    int new_servo_angle = 90 - angle_diff;                                                 // �޸Ķ���Ƕ�
    new_servo_angle = constrain(new_servo_angle, 0, 180);                                  // ���ƶ���Ƕ���0-180�ȷ�Χ��
    uint16_t new_pulse = (new_servo_angle * 2000 / 180) + 500;                             // ����������
    if (angular_velocity_pulse == 0)
    {
        new_pulse = initial_pulse; // ������ٶ�Ϊ0�����س�ʼ����
    }
    return new_pulse;
}

/* ���Ʊ�����ָ����Χ�ڵĺ��� */
int constrain(int value, int min_value, int max_value)
{
    if (value < min_value)
        return min_value;
    else if (value > max_value)
        return max_value;
    else
        return value;
}
