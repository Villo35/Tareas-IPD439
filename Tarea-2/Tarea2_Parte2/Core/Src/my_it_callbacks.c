/*
 * my_it_callbacks.c
 *
 *  Created on: Apr 7, 2026
 *      Author: sebas
 */


#include "main.h"
#include "stdio.h"
#include "cmsis_os.h"

extern osMessageQueueId_t S1_ColaHandle;
extern float rx_buffer;
extern UART_HandleTypeDef huart2;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if(huart->Instance == USART2) {
        osMessageQueuePut(S1_ColaHandle, &rx_buffer, 0, 0);

        HAL_UART_Receive_IT(&huart2, (uint8_t*)&rx_buffer, sizeof(float));
    }
}
