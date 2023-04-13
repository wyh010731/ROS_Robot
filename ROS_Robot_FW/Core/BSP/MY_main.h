//
// Created by WYH on 2023/1/20.
//

#ifndef ROS_ROBOT_MY_MAIN_H
#define ROS_ROBOT_MY_MAIN_H

#include "main.h"
#include "usart.h"

#include "oled.h"
#include <string.h>
#include <stdio.h>
#include "Motor.h"
#include "Servo.h"

#define UART_INSTANCE USART2
#define UART_BAUDRATE 115200
#define UART_IRQ USART2_IRQn

/* 定义缓冲区大小 */
#define RX_BUFFER_SIZE 32
#define FRAME_HEAD_1 '#'
#define FRAME_HEAD_2 '@'

void my_main(void);

#endif //ROS_ROBOT_MY_MAIN_H
