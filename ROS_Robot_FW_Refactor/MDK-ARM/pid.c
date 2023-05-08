//
// Created by WYH on 2023/4/17.
//

#include "pid.h"

// 声明PID控制器变量
float Kp, Ki, Kd;                   // PID增益
float integral = 0, derivative = 0; // 积分误差和导数误差
float error, last_error;            // 误差和上一次误差
float setpoint, feedback;           // 目标值和反馈值
float output;                       // PID输出

// 初始化PID控制器
void pid_init(float _Kp, float _Ki, float _Kd)
{
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
    integral = 0;
    derivative = 0;
    last_error = 0;
}

// 计算PID输出
float pid_compute(float _setpoint, float _feedback, float dt)
{
    setpoint = _setpoint;
    feedback = _feedback;

    // 计算误差和误差变化率
    error = setpoint - feedback;
    derivative = (error - last_error) / dt;

    // 计算积分误差
    integral += error * dt;

    // 计算PID输出
    output = Kp * error + Ki * integral + Kd * derivative;

    // 更新上一次误差
    last_error = error;

    return output;
}
