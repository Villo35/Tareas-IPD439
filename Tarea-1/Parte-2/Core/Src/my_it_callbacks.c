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
            sample_index = 0;
            is_sampling = 1;
            HAL_TIM_Base_Start_IT(&htim3);
        }
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM3)
    {
        if(is_sampling)
        {
            HAL_ADC_Start(&hadc1);

            if(HAL_ADC_PollForConversion(&hadc1, 1) == HAL_OK)
            {
                adc_buffer[sample_index] = HAL_ADC_GetValue(&hadc1);
                sample_index++;
            }

            if(sample_index >= NUM_SAMPLES)
            {
                is_sampling = 0;
                data_ready = 1;
                HAL_TIM_Base_Stop_IT(&htim3);
            }
        }
    }
}
