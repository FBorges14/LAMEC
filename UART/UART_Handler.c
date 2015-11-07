#include "UART_Handler.h"

/************Constantes****************/
const uint8_t UARTINBUFSIZE  = 250;
const uint8_t UARTOUTBUFSIZE = 250;


/**************Variaveis***************/
uint8_t 	UARTInBuf[UARTINBUFSIZE];		//Buffer recepçao
uint8_t 	UARTOutBuf[UARTOUTBUFSIZE];	//Buffer envio
uint32_t	UARTInBufNumbytes=0;
uint32_t	UARTOutBufNumbytes =0;

uint16_t		UARTInBufNextRead=0;
uint16_t   	UARTInBufNextWrite=0;
uint16_t		UARTOutBufNextRead=0;
uint16_t		UARTOutBufNextWrite=0;

/***************Funçoes****************/
/**
  * @brief  Verifica se existem bytes para ler
  * @retval 1 se houver bytes novos; 0 se nao houver
  */
uint8_t GetUSBInBufNumbytes(void)
{
	if(UARTInBufNextWrite == UARTInBufNextRead)
		return 0;
	else 
		return 1;
}

/**
  * @brief  Retorna 1 byte do buffer circular
  * @param  inbyte: caracter a retornar
  * @retval 1 se houver caracter novo ; 0 se falhar ao obter um caracter novo
  */
uint8_t GetUSBInBufByte(uint8_t *inbyte)
{
  if(GetUSBInBufNumbytes()){
			*inbyte = UARTInBuf[UARTInBufNextRead];
			
			if(UARTInBufNextRead == UARTINBUFSIZE - 1) {
				UARTInBufNextRead = 0; // wrap-around
			} else { 
				UARTInBufNextRead++;
			}
			
			return 1;
	} else {
			return 0;
	}
}

/**
  * @brief  Coloca informaçao recebida num buffer circular 
  * @param  huart: apontador para estrutura UART_HandleTypeDef que tem informaçºao sobre as 
	*                configuraçoes do modulo de UART
  * @param  data: apontador para buffer de informaçao a enviar
  * @param  Size: tamanho de informaçºao a enviar
  * @retval HAL status (HAL_OK , HAL_ERROR , HAL_BUSY)
  */
void UART_Receive_IT (UART_HandleTypeDef *huart)
{	
	uint16_t i=0;
	int Size = huart->RxXferSize;
	
	for( i=0 ; i< Size	; i++)
	{
		UARTInBuf[UARTInBufNextWrite] = huart->pRxBuffPtr[i];
    UARTInBufNumbytes++;

		if(UARTInBufNextWrite == UARTINBUFSIZE - 1) 
       UARTInBufNextWrite = 0;  // wrap-around
    else 
       UARTInBufNextWrite++;	
	}
}

/**
  * @brief  Transmite informaçao pela UART com IT
  * @param  huart: apontador para estrutura UART_HandleTypeDef que tem informaçºao sobre as 
	*                configuraçoes do modulo de UART
  * @param  data: apontador para buffer de informaçao a enviar
  * @param  Size: tamanho de informaçºao a enviar
  * @retval HAL status (HAL_OK , HAL_ERROR , HAL_BUSY)
  */
HAL_StatusTypeDef UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t * data, uint16_t Size)
{
	HAL_StatusTypeDef result;
  result = HAL_UART_Transmit_IT(huart, data , Size );
	
  return result;
}
