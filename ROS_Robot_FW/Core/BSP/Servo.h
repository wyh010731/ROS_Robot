//
// Created by WYH on 2023/1/19.
//

#ifndef ROS_ROBOT_SERVO_H
#define ROS_ROBOT_SERVO_H

#include "main.h"
#include "stdio.h"
#include "tim.h"
#include "stdint.h"

void Servo_init();
void set_servo_angle(uint16_t angle);
int calculate_servo_angle(int angular_velocity);
int constrain(int value, int min_value, int max_value);
#endif //ROS_ROBOT_SERVO_H
