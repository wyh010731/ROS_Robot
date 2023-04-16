//
// Created by WYH on 2023/2/22.
//

#ifndef ROS_ROBOT_ENCODER_H
#define ROS_ROBOT_ENCODER_H

#include "main.h"
#include "tim.h"
#include "stdio.h"

void Encoder_init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif //ROS_ROBOT_ENCODER_H
