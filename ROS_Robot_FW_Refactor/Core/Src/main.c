/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <string.h>
#include "../BSP/Servo.h"
#include "../BSP/Motor.h"
#include "../BSP/Encoder.h"
#include "../BSP/oled.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define UART_INSTANCE USART2
#define UART_BAUDRATE 115200
#define UART_IRQ USART2_IRQn
/* 定义缓冲区大小 */
#define RX_BUFFER_SIZE 32
#define FRAME_HEAD_1 '#'
#define FRAME_HEAD_2 '@'
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* 定义接收缓冲区 */
uint8_t rx_buffer[RX_BUFFER_SIZE];
uint8_t rx_index = 0;
/* 定义变量表示是否接收到了帧头 */
uint8_t frame_received = 0;
/* 定义变量 */
uint8_t linear_velocity = 0 , angular_velocity = 0 , lidar_distance = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM4_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	printf("初始化\r\n");
  /* 舵机初始化 */
  Servo_init();
  /* 舵电机初始化 */
  Motor_init();
  /* 编码器初始化 */
  Encoder_init();
	HAL_UART_Receive_IT(&huart2, &rx_buffer[rx_index], 1);
  /* OLED初始化 */
  OLED_Init();
  OLED_ColorTurn(0);
  /* 显示字符串 "Autopilot System" */
  OLED_ShowString(15,0,(uint8_t *)"Autopilot System",12,1);
  /* OLED屏幕刷新 */
  OLED_Refresh();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* 自定义主函数 */
void my_main()
{
    /* 判断激光雷达距离，障碍物距离小于等于20cm时车辆立即停止 */
    if(lidar_distance <= 20){
        Motor_speed(0,0);
        Motor_direction(3);
    }
    else{
        Motor_speed(linear_velocity,linear_velocity);
        Motor_direction(1);
        /* 计算舵机转向角度 */
        int new_servo_angle = calculate_servo_angle(angular_velocity);
        /* 设定舵机转向角度 */
        set_servo_angle(new_servo_angle);
    }
}

/* 串口回调函数解析数据 */
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

/* printf重映像 */
int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch, 1, 100);
	return (ch);
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
