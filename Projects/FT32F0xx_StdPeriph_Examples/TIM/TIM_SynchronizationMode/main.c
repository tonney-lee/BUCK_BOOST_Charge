  /**
  ******************************************************************************
  * @file    TIM/TIM_SynchronizationMode/main.c
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

/** @addtogroup TIM_SynchronizationMode
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void TIM_Config(void);

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

  /* TIM1/3 Configuration */
  TIM_Config();

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Configure the TIM1/3 Pins.
  * @param  None
  * @retval None
  */
static void TIM_Config(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
  /* TIM3 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

  /* GPIOA and GPIOB clocks enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB, ENABLE);

  /* GPIOB Configuration: PB4(TIM3 CH1) as alternate function push-pull ------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Connect TIM pins to AF1 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_1);

  /* GPIOA Configuration: PA8(TIM1 CH1) as alternate function push-pull ------*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Connect TIM pins to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);

  /* Timers synchronisation in cascade mode ----------------------------
     1/TIM1 is configured as Master Timer:
         - PWM Mode is used
         - The TIM1 Update event is used as Trigger Output  

     2/TIM3 is slave for TIM1,
         - PWM Mode is used
         - The ITR1(TIM1) is used as input trigger 
         - Gated mode is used, so start and stop of slave counter are controlled
           by the Master trigger output signal(TIM1 update event).

     In this example TIM1 input clock (TIM1CLK) is set to APB1 clock (PCLK1).   
       TIM1CLK = PCLK1  
       PCLK1 = HCLK 
       => TIM1CLK = HCLK = SystemCoreClock = 48 MHz

     The TIM1 is running at:
         TIM1 frequency = (TIM1 counter clock)/ (TIM1 period + 1) = 187.5 KHz 
     and duty cycle = TIM1_CCR1/(TIM1_ARR + 1) = 25%.

     The slave Timer TIM3 is running at TIM1 clock:
         (TIM1 frequency)/ (TIM3 period + 1) = 46.87 KHz
     and duty cycle equal = TIM3_CCR1/(TIM3_ARR + 1) = 25%
  
       The Master Timer TIM1 is running at TIM1 counter clock:
       TIM1 frequency = (TIM1 counter clock)/ (TIM1 period + 1) = 187.5 KHz 
       and the duty cycle = TIM1_CCR1/(TIM1_ARR + 1) = 25%.

 
     Note: 
     SystemCoreClock variable holds HCLK frequency and is defined in system_FT32f0xx.c file.
     Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
     function to update SystemCoreClock variable value. Otherwise, any configuration
     based on this variable will be incorrect. 
  --------------------------------------------------------------------------- */

  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 255;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  TIM_TimeBaseStructure.TIM_Period = 3;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* Master Configuration in PWM1 Mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 64;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  /* Select the Master Slave Mode */
  TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);

  /* Master Mode selection */
  TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);

  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);


  /* Slaves Configuration: PWM1 Mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 1;

  TIM_OC1Init(TIM3, &TIM_OCInitStructure);

  /* Slave Mode selection: TIM3 */
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);
  TIM_SelectInputTrigger(TIM3, TIM_TS_ITR0);
 
  /* TIM enable counter */
  TIM_Cmd(TIM3, ENABLE);
  TIM_Cmd(TIM1, ENABLE);

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
