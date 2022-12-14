/**
  ******************************************************************************
  * @file    CRC/CRC_TwoBoards/main.c 
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

/** @addtogroup CRC_TwoBoards
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t TxBuffer[] = "USART Interrupt Example: Communication between two USART using Interrupt";
uint8_t RxBuffer [RXBUFFERSIZE];

__IO JOYState_TypeDef PressedButton  = JOY_NONE;
__IO uint8_t RxIndex = 0x00;
__IO uint8_t TxIndex = 0x00;

/* Private function prototypes -----------------------------------------------*/
static void USART_Config(void);
static void SysTickConfig(void);
static void CRC_Config(uint8_t poly);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontrollers clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_FT32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_FT32f30x.c file
     */ 
  
  /* USART configuration -----------------------------------------------------*/
  USART_Config();
  
  /* SysTick configuration ---------------------------------------------------*/
  SysTickConfig();
  
  /* Initialize LEDs mounted on FT32303C-EVAL board */
  FT_EVAL_LEDInit(LED1);
  FT_EVAL_LEDInit(LED2);
  FT_EVAL_LEDInit(LED3);
 
  /* Configure the CRC peripheral to use the polynomial x8 + x7 + x6 + x4 + x2 + 1 */
  CRC_Config(0xD5);
  
#ifdef MODE_TRANSMITTER
  /* ------------------ USART in mode Tramitter ------------------------------*/

  /* Configure the external interrupt "Joystick SEL" button */
  FT_EVAL_PBInit(BUTTON_SEL, BUTTON_MODE_EXTI);

  /* Forever loop */
  while (1)
  {
    
    /*Wait "JOY_SEL" to start data transfer */
    if ((PressedButton != JOY_NONE))
    {
      /* Enable the USARTx transmit data register empty interrupt */
      USART_ITConfig(USARTx, USART_IT_TXE, ENABLE);
      /* Set PressedButton to default value */
      PressedButton = JOY_NONE;
    }
  }
#else
  /* ------------------ USART in mode Receiver -------------------------------*/
  /* Enable the USARTx receive data register not empty interrupt */
  USART_ITConfig(USARTx, USART_IT_RXNE, ENABLE);

  /* Infinite loop */
  while(1)
  {
  }
  
#endif /* MODE_TRANSMITTER */
}

/**
  * @brief  Configures the USART Peripheral.
  * @param  None
  * @retval None
  */
static void USART_Config(void)
{
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* Enable GPIO clock */
  RCC_AHBPeriphClockCmd(USARTx_TX_GPIO_CLK | USARTx_RX_GPIO_CLK, ENABLE);
  
  /* Enable USART clock */
  USARTx_APBPERIPHCLOCK(USARTx_CLK, ENABLE);
  
  /* Connect PXx to USARTx_Tx */
  GPIO_PinAFConfig(USARTx_TX_GPIO_PORT, USARTx_TX_SOURCE, USARTx_TX_AF);
  
  /* Connect PXx to USARTx_Rx */
  GPIO_PinAFConfig(USARTx_RX_GPIO_PORT, USARTx_RX_SOURCE, USARTx_RX_AF);
  
  /* Configure USART Tx and Rx as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = USARTx_TX_PIN;
  GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = USARTx_RX_PIN;
  GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStructure);

  /* USARTx configuration ----------------------------------------------------*/
  /* USARTx configured as follow:
  - BaudRate = 230400 baud  
  - Word Length = 8 Bits
  - One Stop Bit
  - No parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;//230400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USARTx, &USART_InitStructure);
  
  /* NVIC configuration: Enable the USARTx Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USARTx_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* Enable USART */
  USART_Cmd(USARTx, ENABLE);

}

/**
  * @brief  Configure a SysTick Base time to 10 ms.
  * @param  None
  * @retval None
  */
static void SysTickConfig(void)
{
  /* Setup SysTick Timer for 10ms interrupts  */
  if (SysTick_Config(SystemCoreClock / 100))
  {
    /* Capture error */
    while (1);
  }
  /* Configure the SysTick handler priority */
  NVIC_SetPriority(SysTick_IRQn, 0x0);
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


/************************ (C) COPYRIGHT FMD *****END OF FILE****/
