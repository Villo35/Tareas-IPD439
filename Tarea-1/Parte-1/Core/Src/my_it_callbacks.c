/*
 * my_it_callbacks.c
 *
 *  Created on: Mar 19, 2026
 *      Author: sebas
 */
#include "main.h"

void DmaXferCompleteCallback(DMA_HandleTypeDef *hdma)
{
    HAL_GPIO_WritePin(GPIOA, LD2_Pin, GPIO_PIN_RESET);
}
