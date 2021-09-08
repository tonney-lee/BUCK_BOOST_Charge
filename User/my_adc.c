#include "my_adc.h"
#include "my_uart.h"

/*------------------------------------------------- 
 *	函数名称：DelayUs
 *	功能：   短延时函数 --16M-2T--大概快1%左右.
 *	输入参数：Time 延时时间长度 延时时长Time Us
 *	返回参数：无 
 -------------------------------------------------*/
void DelayUs(unsigned char Time)
{
    unsigned char a;
    for(a = 0; a < Time; a++)
    {
        NOP();
    }
}
/*-------------------------------------------------
 *  函数名: ADC_INITIAL
 *	功能：  ADC初始化
 *  输入：  无
 *  输出：  无
 --------------------------------------------------*/
/**
  * @brief  ADC and TIM configuration
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
    ADC_InitTypeDef ADC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOC Periph clock enable */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

    /* ADC1 and TIM1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    /* Configure ADC Channel11 as analog input */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; /* Configure ADC Channel11 as analog input */

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* ADC1 DeInit */
    ADC_DeInit(ADC1);

    /* Initialize ADC structure */
    ADC_StructInit(&ADC_InitStructure);

    /* Configure the ADC1 in continous mode withe a resolution equal to 12 bits  */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC4;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* Convert the ADC1 Channel11 and channel10 with 239.5 Cycles as sampling time */

    ADC_ChannelConfig(ADC1, ADC_Channel_11, ADC_SampleTime_239_5Cycles);

    /* ADC Calibration */
    ADC_GetCalibrationFactor(ADC1);

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
}

/*-------------------------------------------------
 *  函数名: GET_ADC_DATA
 *	功能：  读取通道ADC值
 *  输入：  adcChannel 通道序号
 *  输出：  INT类型AD值(单次采样无滤波)
 --------------------------------------------------*/
u16 GET_ADC_DATA(u8 adcChannel)
{
    return 0;
}
/*---------------------------------------------------------------------------*/
/** \brief  set adc chanel
 *
 * \param
 * \param
 * \return
 *
 */

void set_ADC_CH(u8 ADCchannel)
{
}
/*---------------------------------------------------------------------------*/
/** \brief   get adc value
 *
 * \param
 * \param
 * \return
 *
 */

u16 getADCResult(void)
{
    return 0;
}
/*---------------------------------------------------------------------------*/
/** \brief   adc value update
 *
 * \param
 * \param
 * \return
 *
 */
// ADC channel
// AN2 AN3 AN4 AN5 1.2v
//MG NTC
//BAT NTC
//BT V
//MOTOR CURRENT

void adc_Update()
{
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
