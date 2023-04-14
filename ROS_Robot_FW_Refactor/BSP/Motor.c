//
// Created by WYH on 2023/1/19.
//

#include "Motor.h"

/*
 * �����ʼ��
 */
void Motor_init()
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //����PWM
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);

    printf("Motor init OK!\n");
}

/*
 * �趨���ת��Ƶ��
 * PWMAΪ���1
 * PWMBΪ���2
 */
void Motor_speed(uint32_t PWM_A,uint32_t PWM_B) //�趨PWMƵ��
{
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWM_A);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWM_B);
}

/*
 * ѡ������ת����
 * 1Ϊ�����ת
 * 2Ϊ�����ת
 */
void Motor_direction(uint8_t direction)
{
    switch (direction) {
        case 1://��ת
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);   //IN1
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET); //IN2

            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);   //IN3
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET); //IN4
            break;
        case 2://��ת
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET); //IN1
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);   //IN2

            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET); //IN3
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);   //IN4
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);

            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
            break;
    }

}
