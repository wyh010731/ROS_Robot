//
// Created by WYH on 2023/2/22.
//

#ifndef ROS_ROBOT_ENCODER_H
#define ROS_ROBOT_ENCODER_H

#include "main.h"
#include "tim.h"
#include "stdio.h"
#include <stdlib.h>

void Encoder_init(void);
int Read_Encoder(uint8_t TIMX);
int Calculate_Motor_RPM(int motor_value);
#endif //ROS_ROBOT_ENCODER_H
