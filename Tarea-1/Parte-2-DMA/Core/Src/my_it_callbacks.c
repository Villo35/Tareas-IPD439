/*
 * my_it_callbacks.c
 *
 *  Created on: Mar 22, 2026
 *      Author: sebas
 */

#include "main.h"
#include "stdio.h"

#define NUM_SAMPLES 80

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim3;
extern UART_HandleTypeDef huart2;


extern volatile uint16_t adc_buffer[NUM_SAMPLES];
extern volatile uint8_t is_sampling;
extern volatile uint8_t data_ready;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == B1_Pin)
    {
        if(!is_sampling && !data_ready)
        {
            is_sampling = 1;

            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, NUM_SAMPLES);
        	HAL_GPIO_WritePin(Indicador_GPIO_Port, Indicador_Pin, GPIO_PIN_SET);
            HAL_TIM_Base_Start(&htim3);
        }
    }
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    if(hadc->Instance == ADC1)
    {
        HAL_TIM_Base_Stop(&htim3);

        HAL_ADC_Stop_DMA(&hadc1);
    	HAL_GPIO_WritePin(Indicador_GPIO_Port, Indicador_Pin, GPIO_PIN_RESET);

        is_sampling = 0;
        data_ready = 1;
    }
}
