//
// Created by WYH on 2023/1/20.
//

#include "MY_usart.h"

uint8_t Rx_Data[255] = {0};  // ���ݻ���
uint8_t uLength = 0;         // ���ݳ��ȼ�����
uint8_t aRxBuff;             // ��ǰ����

typedef union{
    float data;
    uint8_t data8[4];
}data_u;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//���ջص�����
{

}