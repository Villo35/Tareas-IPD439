/*
 * my_it_callbacks.c
 *
 *  Created on: Mar 22, 2026
 *      Author: sebas
 */

#include "main.h"
#include "stdio.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == USER_Btn_Pin)
    {
        if(!is_sampling && !data_ready)
        {
            is_sampling = 1;

            HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_buffer, NUM_SAMPLES);

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

        is_sampling = 0;
        data_ready = 1;
    }
}
