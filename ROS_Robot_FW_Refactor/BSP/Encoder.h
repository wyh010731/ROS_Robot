//
// Created by WYH on 2023/2/22.
//

#ifndef ROS_ROBOT_ENCODER_H
#define ROS_ROBOT_ENCODER_H

#include "main.h"
#include "tim.h"
#include "stdio.h"

void Encoder_init(void);
// ��ȡ���1��ת��
void Get_Motor1_Speed(void);
// ��ȡ���2��ת��
void Get_Motor2_Speed(void);
float Calculate_Speed(uint32_t count, uint32_t* timestamp, TIM_HandleTypeDef* htim);
#endif //ROS_ROBOT_ENCODER_H
