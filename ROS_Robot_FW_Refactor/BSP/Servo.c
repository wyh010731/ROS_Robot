//
// Created by WYH on 2023/1/19.
//

#include "Servo.h"

/* �������ĽǶȱ��� */
uint16_t servo_angle = 90; // ��ʼ�Ƕ�Ϊ90��

/* ���ƶ���Ƕȳ�ʼ������ */
void Servo_init()
{
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim4 , TIM_CHANNEL_3 , 1500);
}

/* ���ƶ���Ƕȵĺ��� */
void set_servo_angle(uint16_t angle)
{
    uint16_t pulse_width = (angle * 2000 / 180) + 500; // ����������
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pulse_width); // ����PWM�����������

}

/* �������Ƕȵĺ��� */
int calculate_servo_angle(int angular_velocity)
{
    int max_angular_velocity = 200; // �����ٶ�
    int max_angle_diff = 45; // ���ǶȲ�
    int angle_diff = max_angle_diff * angular_velocity / max_angular_velocity; // ����ǶȲ�
//    int angle_diff = max_angle_diff - (max_angle_diff * angular_velocity / max_angular_velocity);
    int new_servo_angle = 90 - angle_diff; // �޸Ķ���Ƕ�
    new_servo_angle = constrain(new_servo_angle, 0, 180); // ���ƶ���Ƕ���0-180�ȷ�Χ��

    return new_servo_angle;
}

int constrain(int value, int min_value, int max_value)
{
    if (value < min_value)
        return min_value;
    else if (value > max_value)
        return max_value;
    else
        return value;
}
