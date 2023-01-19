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
void Servo_angle(uint8_t angle);

#endif //ROS_ROBOT_SERVO_H
