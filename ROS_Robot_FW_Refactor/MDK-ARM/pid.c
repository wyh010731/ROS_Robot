//
// Created by WYH on 2023/4/17.
//

#include "pid.h"

// 声明PID控制器变量
double Kp, Ki, Kd;  // PID增益
double integral = 0, derivative = 0;  // 积分误差和导数误差
double error, last_error;  // 误差和上一次误差
double setpoint, feedback;  // 目标值和反馈值
double output;  // PID输出

// 初始化PID控制器
void pid_init(double _Kp, double _Ki, double _Kd) {
    Kp = _Kp;
    Ki = _Ki;
    Kd = _Kd;
    integral = 0;
    derivative = 0;
    last_error = 0;
}

// 计算PID输出
double pid_compute(double _setpoint, double _feedback, double dt) {
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
