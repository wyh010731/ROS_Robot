//
// Created by WYH on 2023/1/19.
//

#include "Motor.h"

void Motor_init() //电机初始化
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //启动PWM
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);

    printf("Motor init OK!\n");
}

void Motor_speed(uint8_t PWM_A,uint8_t PWM_B) //设定PWM频率
{
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWM_A);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWM_B);
}

void Motor_direction(uint8_t direction)
{
    switch (direction) {
        case 1:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);   //IN1
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET); //IN2
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET); //IN1
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);   //IN2
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);   //IN3
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET); //IN4
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET); //IN3
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);   //IN4
            break;
        case 5:
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET);

            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);
            break;
    }
}