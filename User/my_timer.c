
#include "my_timer.h"
#include "my_io_port.h"
#include "my_key.h"
#include "my_uart.h"

/**
 * @brief  ADC and TIM configuration
 * @param  None
 * @retval None
 */
//#define MCU_CLOCK (48)     // (MHz) 主频
#define PWM_FREQUENCY (16) // (kHz) 载波频率
#define Pole_Pairs (5)     // 极对数

/*TIM1的参数设置*/
#define TIM1_Prescaler 0                              //预分频为0
//#define TIM1_Period ((SystemCoreClock / 200000) - 1); //设置初始频率17.57 KHz:
#define TIM1_InitDuty (100)       

#define MCU_CLOCK (48000000U)
#define TIM1_PWM_FREQUENCY (150000U)
#define TIM1_PWM_CLOCK_TICKS (int)(MCU_CLOCK / TIM1_PWM_FREQUENCY)
#define TIM1_PWM_MAX_PULSE (TIM1_PWM_CLOCK_TICKS)
#define TIM1_PWM_PERIOD (TIM1_PWM_MAX_PULSE - 1)                    //初始占空比

#define TIM2_PWM_FREQUENCY (2500U)
#define TIM2_PWM_CLOCK_TICKS (int)(MCU_CLOCK / TIM2_PWM_FREQUENCY)
#define TIM2_PWM_MAX_PULSE (TIM2_PWM_CLOCK_TICKS / 4)
#define TIM2_PWM_PERIOD (TIM2_PWM_MAX_PULSE - 1)

#define TIM3_PWM_FREQUENCY (10000U)
#define TIM3_PWM_CLOCK_TICKS (int)(MCU_CLOCK / TIM3_PWM_FREQUENCY)
#define TIM3_PWM_MAX_PULSE (TIM3_PWM_CLOCK_TICKS / 4)
#define TIM3_PWM_PERIOD (TIM3_PWM_MAX_PULSE - 1)



static void TIM1_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    /* ADC1 and TIM1 Periph clock enable */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    /* TIM1 DeInit */
    TIM_DeInit(TIM1);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = TIM1_Prescaler;
    TIM_TimeBaseStructure.TIM_Period = TIM1_PWM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

    /* Output Compare PWM Mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* low edge by default */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // CHx输出极性:TIM输出比较极性高(PWM输出的电平极性)
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; // CHx输出空闲状态:0
    TIM_OCInitStructure.TIM_Pulse = TIM1_InitDuty;             //初始脉冲

    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC4Init(TIM1, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable);

    /* TIM1 enable counter */
    TIM_Cmd(TIM1, ENABLE);
    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM1, ENABLE);

    TIM_SetCompare1(TIM1, (int)(TIM1_PWM_PERIOD*0.4));                
    TIM_SetCompare2(TIM1, (int)TIM1_PWM_PERIOD); 
    // TIM_SetCompare3(TIM1, 100); //W
    // TIM_SetCompare4(TIM1, 100);
}
/**
 * @description:
 * @param {*}
 * @return {*}
 */
static void TIM3_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* TIM3 DeInit */
    TIM_DeInit(TIM3);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = TIM1_Prescaler;
    TIM_TimeBaseStructure.TIM_Period = TIM3_PWM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    /* Output Compare PWM Mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* low edge by default */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // CHx输出极性:TIM输出比较极性高(PWM输出的电平极性)
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; // CHx输出空闲状态:0
    TIM_OCInitStructure.TIM_Pulse = TIM1_InitDuty;             //初始脉冲

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);

    /* TIM1 enable counter */
    TIM_Cmd(TIM3, ENABLE);
    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
}
/**
 * @description:
 * @param {*}
 * @return {*}
 */
static void TIM15_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

    /* TIM3 DeInit */
    TIM_DeInit(TIM15);
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
    TIM_OCStructInit(&TIM_OCInitStructure);

    /* Time base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = TIM1_Prescaler;
    TIM_TimeBaseStructure.TIM_Period = TIM3_PWM_PERIOD;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);

    /* Output Compare PWM Mode configuration */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; /* low edge by default */
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  // CHx输出极性:TIM输出比较极性高(PWM输出的电平极性)
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set; // CHx输出空闲状态:0
    TIM_OCInitStructure.TIM_Pulse = TIM1_InitDuty;             //初始脉冲

    TIM_OC1Init(TIM15, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM15, TIM_OCPreload_Enable);

    /* TIM1 enable counter */
    TIM_Cmd(TIM15, ENABLE);
    /* Main Output Enable */
    TIM_CtrlPWMOutputs(TIM15, ENABLE);
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void Time1Initial(void)
{
    TIM1_Config();
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void Time3Initial(void)
{
    TIM3_Config();
}

/**
 * @description:
 * @param {*}
 * @return {*}
 */
void Time15Initial(void)
{
    TIM15_Config();
}
