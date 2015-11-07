#include "stm32f4xx_hal.h"


/*******************   UART IT   *******************/
//verificar e obter byte
uint8_t GetUSBInBufByte(uint8_t *inbyte);

HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t * data, uint16_t Size);


