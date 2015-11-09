#include "stm32f4xx_hal.h"


/*******************   UART IT   *******************/
//verificar e obter byte
uint8_t Lib_GetUSBInBufByte(uint8_t *inbyte);

//transmitir informašao por IT
HAL_StatusTypeDef Lib_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t * data, uint16_t Size);

//receber informašao e coloca no buffer circular
void Lib_UART_Receive_IT (uint8_t * data, uint8_t size);
