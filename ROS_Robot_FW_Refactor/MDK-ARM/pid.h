//
// Created by WYH on 2023/4/17.
//

#ifndef ROS_ROBOT_PID_H
#define ROS_ROBOT_PID_H

#include "main.h"
void pid_init(double _Kp, double _Ki, double _Kd);
double pid_compute(double _setpoint, double _feedback, double dt);
#endif //ROS_ROBOT_PID_H
