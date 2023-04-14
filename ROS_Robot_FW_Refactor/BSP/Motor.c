//
// Created by WYH on 2023/1/19.
//

#include "Motor.h"

/*
 * 电机初始化
 */
void Motor_init()
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1); //启动PWM
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_RESET);

    printf("Motor init OK!\n");
}

/*
 * 设定电机转动频率
 * PWMA为电机1
 * PWMB为电机2
 */
void Motor_speed(uint32_t PWM_A,uint32_t PWM_B) //设定PWM频率
{
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_1,PWM_A);
    __HAL_TIM_SET_COMPARE(&htim1,TIM_CHANNEL_2,PWM_B);
}

/*
 * 选择电机旋转方向
 * 1为电机正转
 * 2为电机反转
 */
void Motor_direction(uint8_t direction)
{
    switch (direction) {
        case 1://正转
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,GPIO_PIN_SET);   //IN1
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET); //IN2

            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,GPIO_PIN_RESET);   //IN3
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,GPIO_PIN_SET); //IN4
            break;
        case 2://反转
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
