//
// Created by WYH on 2023/2/22.
//

#ifndef ROS_ROBOT_ENCODER_H
#define ROS_ROBOT_ENCODER_H

#include "main.h"
#include "tim.h"
#include "stdio.h"

void Encoder_init(void);
uint8_t Encoder_Get_Data();

#endif //ROS_ROBOT_ENCODER_H
