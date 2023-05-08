//
// Created by WYH on 2023/1/19.
//

#include "Servo.h"

/* 定义舵机的角度变量 */
uint16_t servo_angle = 90; // 初始角度为90度

/* 控制舵机角度初始化函数 */
void Servo_init()
{
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, 1500);
}

/* 控制舵机转动的函数 */
void set_servo_rotation(int angular_velocity)
{
    int new_angular_velocity = calculate_servo_pulse(angular_velocity);
    /* 设置PWM输出的脉冲宽度 */
    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, new_angular_velocity);
}

/* 计算舵机PWM脉冲的函数 */
uint16_t calculate_servo_pulse(int angular_velocity_pulse)
{
    uint16_t initial_pulse = 1500;
    int max_angular_velocity_pulse = 200;                                                  // 最大角速度脉冲
    int max_angle_diff = 45;                                                               // 最大角度差
    int angle_diff = max_angle_diff * angular_velocity_pulse / max_angular_velocity_pulse; // 计算角度差
    int new_servo_angle = 90 - angle_diff;                                                 // 修改舵机角度
    new_servo_angle = constrain(new_servo_angle, 0, 180);                                  // 限制舵机角度在0-180度范围内
    uint16_t new_pulse = (new_servo_angle * 2000 / 180) + 500;                             // 计算脉冲宽度
    if (angular_velocity_pulse == 0)
    {
        new_pulse = initial_pulse; // 如果角速度为0，返回初始脉冲
    }
    return new_pulse;
}

/* 限制变量在指定范围内的函数 */
int constrain(int value, int min_value, int max_value)
{
    if (value < min_value)
        return min_value;
    else if (value > max_value)
        return max_value;
    else
        return value;
}
