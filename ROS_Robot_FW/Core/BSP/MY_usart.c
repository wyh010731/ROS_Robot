//
// Created by WYH on 2023/1/20.
//

#include "MY_usart.h"

uint8_t Rx_Data[255] = {0};  // 数据缓存
uint8_t uLength = 0;         // 数据长度计数器
uint8_t aRxBuff;             // 当前数据

typedef union{
    float data;
    uint8_t data8[4];
}data_u;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//接收回调函数
{

}