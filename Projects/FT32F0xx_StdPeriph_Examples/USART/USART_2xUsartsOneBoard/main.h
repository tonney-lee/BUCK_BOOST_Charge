   /**
  ******************************************************************************
  * @file    USART/USART_2xUsartsOneBoard/main.h 
  * @author  AE
  * @version V1.0.0
  * @date    29-MAR-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 FMD</center></h2>
  *
  *
  *        http://www.fremontmicro.com
  *

  *
  ******************************************************************************
  */
  
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Includes ------------------------------------------------------------------*/
#include "FT32f0xx.h"
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE       44
#define USART_MAX_INDEX   2
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
