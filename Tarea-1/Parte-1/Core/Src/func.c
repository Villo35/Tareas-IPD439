/*
 * func.c
 *
 *  Created on: Mar 17, 2026
 *      Author: Sebastián Villegas
 */

#include "stdint.h"
#include "stdlib.h"

void llenar_array(uint8_t *arr, int size) {
    for (size_t i = 0; i < size; i++) {
        arr[i] = (uint8_t)(rand() % 256);
    }
}
/*
uint8_t* crear_array(int size)
{
    if (size <= 0)
    	return NULL;

    uint8_t *arr = (uint8_t*)malloc(size * sizeof(uint8_t));
    if (arr == NULL)
    	return NULL;

    for (int i = 0; i < size; i++)
    {
        arr[i] = (uint8_t)(rand() % 256);
    }

    return arr;
}
*/
