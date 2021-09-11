#include "my_adc.h"
#include "my_io_port.h"

#define ADC1_DR_Address 0x40012440
__IO uint16_t RegularConvData_Tab[7];
/**
  * @brief  DMA channel1 configuration
  * @param  None
  * @retval None
  */
static void DMA_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    DMA_InitTypeDef DMA_InitStructure;
    /* DMA1 clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    /* DMA1 Channel1 Config */
    DMA_DeInit(DMA1_Channel1);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_DR_Address;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)RegularConvData_Tab;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = SIZEOF_ARR(RegularConvData_Tab);
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &DMA_InitStructure);
    //
    /* Enable DMA1 Channel1 Transfer Complete interrupt */
    DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
    /* Enable DMA1 channel1 IRQ Channel */
    NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    //
    /* DMA1 Channel1 enable */
    DMA_Cmd(DMA1_Channel1, ENABLE);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */

static void ADC_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    /* ADC1 and TIM1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    /* ADC1 DeInit */
    ADC_DeInit(ADC1);
    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);
    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStructure);
    /* Convert the ADC1 Channel11 and channel10 with 239.5 Cycles as sampling time */
    ADC_ChannelConfig(ADC1, ADC_Channel_1, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_3, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_4, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_5, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_6, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_7, ADC_SampleTime_1_5Cycles);
    ADC_ChannelConfig(ADC1, ADC_Channel_9, ADC_SampleTime_1_5Cycles);
    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);
    /* ADC DMA request in circular mode */
    ADC_DMARequestModeConfig(ADC1, ADC_DMAMode_Circular);
    /* Enable ADC_DMA */
    ADC_DMACmd(ADC1, ENABLE);
    /* Enable the ADC peripheral */
    ADC_Cmd(ADC1, ENABLE);
    /* Wait the ADRDY flag */
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY))
        ;
    /* ADC1 regular Software Start Conv */
    ADC_StartOfConversion(ADC1);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void ADCInit(void)
{
    ADC_Config();
    DMA_Config();
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */

/**
  * @brief  This function handles DMA1 Channel 1 interrupt request.
  * @param  None
  * @retval None
  */
void DMA1_Channel1_IRQHandler(void)
{
    /* Test on DMA1 Channel1 Transfer Complete interrupt */
    if(DMA_GetITStatus(DMA1_IT_TC1))
    {
        /* DMA1 finished the transfer of SrcBuffer */
        /* Clear DMA1 Channel1 Half Transfer, Transfer Complete and Global interrupt pending bits */
        DMA_ClearITPendingBit(DMA1_IT_GL1);
        static SIZE_T n = 0;
        n ^= 0x01;
        BI_C_IO(n);
    }
}

async ADC_Update(thread_t* pt)
{
    Thread_BEGIN;
    {
        while(1)
        {
            /* Test DMA1 TC flag */
            //Thread_Wait_Until((DMA_GetFlagStatus(DMA1_FLAG_TC1)) == RESET);
            /* Clear DMA TC flag */
            //DMA_ClearFlag(DMA1_FLAG_TC1);
            Thread_Yield();
        }
    }
    Thread_END;
}
/**
 * @description: 
 * @param {u8} size
 * @return {*}
 */
u16 filter(u16* array, u8 size)
{
    u8 j, k;

    for(j = 0; j < size - 1; j++)
    {
        for(k = 0; k < size - j - 1; k++)
        {
            if(array[k] > array[k + 1])
            {
                u16 temp = array[k];
                array[k] = array[k + 1];
                array[k + 1] = temp;
            }
        }
    }

    //return (array[(size - 1) / 2]);
    return (array[(size - 1)]);
}
