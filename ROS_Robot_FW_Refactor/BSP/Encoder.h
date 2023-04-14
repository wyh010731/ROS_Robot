//
// Created by WYH on 2023/2/22.
//

#ifndef ROS_ROBOT_ENCODER_H
#define ROS_ROBOT_ENCODER_H

#include "main.h"
#include "tim.h"
#include "stdio.h"

void Encoder_init(void);
// 获取电机1的转速
void Get_Motor1_Speed(void);
// 获取电机2的转速
void Get_Motor2_Speed(void);
float Calculate_Speed(uint32_t count, uint32_t* timestamp, TIM_HandleTypeDef* htim);
#endif //ROS_ROBOT_ENCODER_H
