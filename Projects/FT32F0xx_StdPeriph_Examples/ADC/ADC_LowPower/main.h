 /**
  ******************************************************************************
  * @file    ADC/ADC_LowPower/main.h 
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
#ifdef USE_FT32F030XX_EVAL
  #include "FT32F030XX_eval.h"
  #include "FT32F030XX_eval_lcd.h"
#else 
  #include "FT32F072X8_eval.h"
  #include "FT32F072X8_eval_lcd.h" 
#endif /* USE_FT32F030XX_EVAL */
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
