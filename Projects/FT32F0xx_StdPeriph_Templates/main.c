/**
  ******************************************************************************
  * @file    PWR/PWR_Stop/main.c 
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
#include "thread.h"
#include "usr.h"
/** @addtogroup FT32f0xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup PWR_Stop
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

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

    /* SysTick interrupt each 10 ms */
    if(SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while(1)
            ;
    }
    NVIC_SetPriority(SysTick_IRQn, 0x0);
    Thread_Start(user, &threadInfo.status);
    TaskRun();
    while(1)
    {
    }
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* KEY can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while(1)
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
