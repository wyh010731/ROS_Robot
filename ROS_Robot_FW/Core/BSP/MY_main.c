//
// Created by WYH on 2023/1/20.
//

#include "MY_main.h"

/* 定义接收缓冲区 */
uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t rx_index = 0;
/* 定义变量表示是否接收到了帧头 */
uint8_t frame_received = 0;
/* 定义变量 */
uint8_t linear_velocity = 0 , angular_velocity = 0 , lidar_distance = 0;

void my_main()
{
    /*判断激光雷达距离，障碍物距离小于等于20cm时车辆立即停止*/
    if(lidar_distance <= 20){
        Motor_speed(0,0);
        Motor_direction(3);
    }
    else{
        Motor_speed(linear_velocity,linear_velocity);
        Motor_direction(1);
        Servo_angle(2);
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == UART_INSTANCE) {
        /* 如果接收到了帧头，根据不同的帧头类型解析命令 */
        if (frame_received == 1) {
            /* 如果接收到了换行符，则认为一条命令接收完成 */
            if (rx_buffer[rx_index-1] == '\n') {
                /* 解析命令 */
                /* 激光雷达数据解析 */
                int lidar_value = (rx_buffer[1] - '0') * 100000 + (rx_buffer[2] - '0') * 10000 + (rx_buffer[3] - '0') * 10000 + (rx_buffer[4] - '0') * 1000 +
                                  (rx_buffer[5] - '0') * 100 + (rx_buffer[6] - '0') * 10 + (rx_buffer[7] - '0') * 1;
                lidar_distance = lidar_value;
                /* 双面摄像头数据解析 */
                int v_l = (rx_buffer[9] - '0') * 1000 + (rx_buffer[10] - '0') * 100 + (rx_buffer[11] - '0') * 10 + (rx_buffer[12] - '0') * 1;
                int v_r = (rx_buffer[13] - '0') * 1000 + (rx_buffer[14] - '0') * 100 + (rx_buffer[15] - '0') * 10 + (rx_buffer[16] - '0') * 1;
                linear_velocity = v_l;
                angular_velocity = v_r;
                /* 串口1输出 */
                printf("Received lidar_value: %d\r\n", lidar_value);
                printf("Received cmd_vel: v_l=%d, v_r=%d\r\n", v_l, v_r);
                /* OLED字符显示 */
                OLED_ShowString(0,16,(uint8_t *)"linear_velocity:",12,1);
                OLED_ShowString(0,32,(uint8_t *)"angular_velocity:",12,1);
                OLED_ShowString(0,48,(uint8_t *)"lidar_distance:",12,1);
                /* OLED数据显示 */
                OLED_ShowNum(100,16,v_l,3,12,1);
                OLED_ShowNum(100,32,v_r,3,12,1);
                OLED_ShowNum(100,48,lidar_value,3,12,1);
                /* OLED屏幕刷新 */
                OLED_Refresh();
                /* 清空接收缓冲区和帧头标志位 */
                memset(rx_buffer, 0, RX_BUFFER_SIZE);
                rx_index = 0;
                frame_received = 0;
                /* 重新开启接收中断 */
                HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
            }
                /* 继续接收数据 */
            else {
                rx_index++;
                if (rx_index >= RX_BUFFER_SIZE) {
                    /* 缓冲区已满，清空接收缓冲区和帧头标志位 */
                    memset(rx_buffer, 0, RX_BUFFER_SIZE);
                    rx_index = 0;
                    frame_received = 0;
                    /* 重新开启接收中断 */
                    HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
                }
                else {
                    HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
                }
            }
        }
            /* 如果没有接收到帧头，则判断是否接收到了帧头 */
        else {
            if (rx_buffer[0] == FRAME_HEAD_1) {
                frame_received = 1;
            }
            /* 清空接收缓冲区 */
            memset(rx_buffer, 0, RX_BUFFER_SIZE);
            rx_index = 0;
            /* 重新开启接收中断 */
            HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
        }
    }
}