//
// Created by WYH on 2023/1/19.
//

#include "Servo.h"

/* 定义舵机的角度变量 */
uint16_t servo_angle = 90; // 初始角度为90度

/* 控制舵机角度初始化函数 */
void Servo_init()
{
    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	__HAL_TIM_SET_COMPARE(&htim4 , TIM_CHANNEL_3 , 1500);
}

/* 控制舵机角度的函数 */
void set_servo_angle(uint16_t angle)
{
    uint16_t pulse_width = (angle * 2000 / 180) + 500; // 计算脉冲宽度
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pulse_width); // 设置PWM输出的脉冲宽度

}

/* 计算舵机角度的函数 */
int calculate_servo_angle(int angular_velocity)
{
    int max_angular_velocity = 200; // 最大角速度
    int max_angle_diff = 45; // 最大角度差
    int angle_diff = max_angle_diff * angular_velocity / max_angular_velocity; // 计算角度差
//    int angle_diff = max_angle_diff - (max_angle_diff * angular_velocity / max_angular_velocity);
    int new_servo_angle = 90 - angle_diff; // 修改舵机角度
    new_servo_angle = constrain(new_servo_angle, 0, 180); // 限制舵机角度在0-180度范围内

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
