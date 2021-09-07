 /**
  ******************************************************************************
  * @file    CRC/CRC_8BitsCRCMessage/main.h
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


/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup FT32f0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup CRC_8BitsCRCMessage
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define countof(a)             (uint8_t)(sizeof(a) / sizeof(*(a)))
#define BUFFER_SIZE            (countof(CRCBuffer) - 1)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t CRCBuffer[] = "FT32f0xx CortexM0 Device running on FT32F072X8-EVAL";
uint8_t ComputedCRC = 0;
uint8_t ExpectedCRC = 0x5D; /* The expected CRC value of CRCBuffer using the
                               polynomial X32 + X26 + X23 + X22 + X16 + X12 + X11 + 
                                              X10 +X8 + X7 + X5 + X4 + X2+ X + 1 */


/* Private function prototypes -----------------------------------------------*/
static void CRC_Config(uint8_t poly);
static uint8_t CRC_8BitsCompute(uint8_t* data, uint32_t size);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_FT32f0xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_FT32f0xx.c file
     */

  /* Initialize LEDs available on FT32F072X8-EVAL board */
  FT_EVAL_LEDInit(LED1);
  FT_EVAL_LEDInit(LED3);

  /* The expected CRC value of CRCBuffer using the
                               polynomial X32 + X26 + X23 + X22 + X16 + X12 + X11 + 
                                              X10 +X8 + X7 + X5 + X4 + X2+ X + 1 */
  CRC_Config(0x4C11DB7);

  /* Compute the CRC value of the 8-bit buffer: CRCBuffer */
  ComputedCRC = CRC_8BitsCompute(CRCBuffer, BUFFER_SIZE);

  /* Check if the computed CRC matches the expected one */
  if (ComputedCRC != ExpectedCRC)
  {
    /* Turn on LD3 */
    FT_EVAL_LEDOn(LED3);
  }
  else
  {
    /* Turn on LD1 */
    FT_EVAL_LEDOn(LED1);
  }
  
  /* Infinite loop */
  while(1)
  {
  }
}

/**
  * @brief  Configure CRC peripheral to use 8-bit polynomials
  * @param  poly: the CRC polynomial
  * @retval None
  */
static void CRC_Config(uint8_t poly)
{
  /* Enable CRC AHB clock interface */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);

  /* DeInit CRC peripheral */
  CRC_DeInit();
  
  /* Init the INIT register */
  CRC_SetInitRegister(0);
	/* Reset the CRC calculation unit */
  CRC->CR = CRC_CR_RESET;
  
  /* Select 8-bit polynomial size */
  CRC_PolynomialSizeSelect(CRC_PolSize_8);
  
  /* Set the polynomial coefficients */
  CRC_SetPolynomial(poly);
}

/**
  * @brief  Compute CRC value for input message
  * @param  data: pointer at uint8_t
  * @param  size: the size of the input message
  * @retval The computed CRC value
  */
static uint8_t CRC_8BitsCompute(uint8_t* data, uint32_t size)
{
  uint8_t* dataEnd = data+size;

  /* Reset CRC data register to avoid overlap when computing new data stream */
  CRC_ResetDR();

  while(data < dataEnd)
  {
    /* Write the input data in the CRC data register */
    CRC_CalcCRC8bits(*data++);
  }
  /* Return the CRC value */
  return (uint8_t)CRC_GetCRC();
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
