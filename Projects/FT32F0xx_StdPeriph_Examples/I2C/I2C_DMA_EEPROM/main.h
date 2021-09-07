 /**
  ******************************************************************************
  * @file    I2C/I2C_DMA_EEPROM/main.h 
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
  #include "FT32F030XX_eval_i2c_ee.h"
#else 
  #include "FT32F072X8_eval.h"
  #include "FT32F072X8_eval_lcd.h"
  #include "FT32F072X8_eval_i2c_ee.h"
#endif /* USE_FT32F030XX_EVAL */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define I2C1_TDR_Address    (I2C1_BASE+0X28)
#define I2C1_RXD_Address    (I2C1_BASE+0X24)


/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
