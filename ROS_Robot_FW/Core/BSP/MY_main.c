//
// Created by WYH on 2023/1/20.
//

#include "MY_main.h"

/* ������ջ����� */
uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t rx_index = 0;
/* ���������ʾ�Ƿ���յ���֡ͷ */
uint8_t frame_received = 0;
/* ������� */
uint8_t linear_velocity = 0 , angular_velocity = 0 , lidar_distance = 0;

void my_main()
{
    /*�жϼ����״���룬�ϰ������С�ڵ���20cmʱ��������ֹͣ*/
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
        /* ������յ���֡ͷ�����ݲ�ͬ��֡ͷ���ͽ������� */
        if (frame_received == 1) {
            /* ������յ��˻��з�������Ϊһ������������ */
            if (rx_buffer[rx_index-1] == '\n') {
                /* �������� */
                /* �����״����ݽ��� */
                int lidar_value = (rx_buffer[1] - '0') * 100000 + (rx_buffer[2] - '0') * 10000 + (rx_buffer[3] - '0') * 10000 + (rx_buffer[4] - '0') * 1000 +
                                  (rx_buffer[5] - '0') * 100 + (rx_buffer[6] - '0') * 10 + (rx_buffer[7] - '0') * 1;
                lidar_distance = lidar_value;
                /* ˫������ͷ���ݽ��� */
                int v_l = (rx_buffer[9] - '0') * 1000 + (rx_buffer[10] - '0') * 100 + (rx_buffer[11] - '0') * 10 + (rx_buffer[12] - '0') * 1;
                int v_r = (rx_buffer[13] - '0') * 1000 + (rx_buffer[14] - '0') * 100 + (rx_buffer[15] - '0') * 10 + (rx_buffer[16] - '0') * 1;
                linear_velocity = v_l;
                angular_velocity = v_r;
                /* ����1��� */
                printf("Received lidar_value: %d\r\n", lidar_value);
                printf("Received cmd_vel: v_l=%d, v_r=%d\r\n", v_l, v_r);
                /* OLED�ַ���ʾ */
                OLED_ShowString(0,16,(uint8_t *)"linear_velocity:",12,1);
                OLED_ShowString(0,32,(uint8_t *)"angular_velocity:",12,1);
                OLED_ShowString(0,48,(uint8_t *)"lidar_distance:",12,1);
                /* OLED������ʾ */
                OLED_ShowNum(100,16,v_l,3,12,1);
                OLED_ShowNum(100,32,v_r,3,12,1);
                OLED_ShowNum(100,48,lidar_value,3,12,1);
                /* OLED��Ļˢ�� */
                OLED_Refresh();
                /* ��ս��ջ�������֡ͷ��־λ */
                memset(rx_buffer, 0, RX_BUFFER_SIZE);
                rx_index = 0;
                frame_received = 0;
                /* ���¿��������ж� */
                HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
            }
                /* ������������ */
            else {
                rx_index++;
                if (rx_index >= RX_BUFFER_SIZE) {
                    /* ��������������ս��ջ�������֡ͷ��־λ */
                    memset(rx_buffer, 0, RX_BUFFER_SIZE);
                    rx_index = 0;
                    frame_received = 0;
                    /* ���¿��������ж� */
                    HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
                }
                else {
                    HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
                }
            }
        }
            /* ���û�н��յ�֡ͷ�����ж��Ƿ���յ���֡ͷ */
        else {
            if (rx_buffer[0] == FRAME_HEAD_1) {
                frame_received = 1;
            }
            /* ��ս��ջ����� */
            memset(rx_buffer, 0, RX_BUFFER_SIZE);
            rx_index = 0;
            /* ���¿��������ж� */
            HAL_UART_Receive_IT(huart, &rx_buffer[rx_index], 1);
        }
    }
}