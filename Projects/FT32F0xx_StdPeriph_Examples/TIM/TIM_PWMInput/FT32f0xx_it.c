    /**
  ******************************************************************************
  * @file    TIM/TIM_PWMInput/FT32f0xx_it.c
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
#include "FT32f0xx_it.h"

/** @addtogroup FT32F0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup TIM_PWMInput
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t IC2Value = 0;
__IO uint16_t DutyCycle = 0;
__IO uint32_t Frequency = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 FT32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_FT32f0xx.s).                                               */
/******************************************************************************/
/**
  * @brief  This function handles TIM3 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM3_IRQHandler(void)
{
  /* Clear TIM3 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);

  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(TIM3);

  if (IC2Value != 0)
  {
    /* Duty cycle computation */
    DutyCycle = (TIM_GetCapture1(TIM3) * 100) / IC2Value;

    /* Frequency computation */
    Frequency = SystemCoreClock / IC2Value;
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
