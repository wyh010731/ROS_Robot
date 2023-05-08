//
// Created by WYH on 2023/4/17.
//

#ifndef ROS_ROBOT_PID_H
#define ROS_ROBOT_PID_H

#include "main.h"
void pid_init(float _Kp, float _Ki, float _Kd);
float pid_compute(float _setpoint, float _feedback, float dt);
#endif //ROS_ROBOT_PID_H
