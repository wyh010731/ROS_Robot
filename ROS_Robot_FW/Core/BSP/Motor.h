//
// Created by WYH on 2023/1/19.
//

#ifndef ROS_ROBOT_MOTOR_H
#define ROS_ROBOT_MOTOR_H

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "stdio.h"

void Motor_init();
void Motor_speed(uint8_t PWM_A,uint8_t PWM_B);
void Motor_direction(uint8_t direction);

#endif //ROS_ROBOT_MOTOR_H
