#ifndef __MY_IO_PORT_H__
#define __MY_IO_PORT_H__

#include "thread.h"

//PC13
//DC_IN
#define DC_IN_Port GPIOC
#define DC_IN_Pin  GPIO_Pin_13
#define DC_IN_IO() GPIO_ReadInputDataBit(DC_IN_Port, DC_IN_Pin)
//PC14
//PWR_1
#define POWER_Port    GPIOC
#define POWER_Pin     GPIO_Pin_14
#define POWER_PIN_H() GPIO_SetBits(POWER_Port, POWER_Pin)
#define POWER_PIN_L() GPIO_ResetBits(POWER_Port, POWER_Pin)
#define POWER_IO(n)   (n ? (POWER_PIN_H()) : (POWER_PIN_L()))
//PC15
//BT_RESET
#define BT_RESET_Port    GPIOC
#define BT_RESET_Pin     GPIO_Pin_15
#define BT_RESET_PIN_H() GPIO_SetBits(BT_RESET_Port, BT_RESET_Pin)
#define BT_RESET_PIN_L() GPIO_ResetBits(BT_RESET_Port, BT_RESET_Pin)
#define BT_RESET_IO(n)   (n ? (BT_RESET_PIN_H()) : (BT_RESET_PIN_L()))
//PF0
//BV_ON
#define BV_ON_Port    GPIOF
#define BV_ON_Pin     GPIO_Pin_0
#define BV_ON_PIN_H() GPIO_SetBits(BV_ON_Port, BV_ON_Pin)
#define BV_ON_PIN_L() GPIO_ResetBits(BV_ON_Port, BV_ON_Pin)
#define BV_ON_IO(n)   (n ? (BV_ON_PIN_H()) : (BV_ON_PIN_L()))
//PF1
//MODE
#define MODE_Port GPIOF
#define MODE_Pin  GPIO_Pin_1
#define MODE_IO() GPIO_ReadInputDataBit(MODE_Port, MODE_Pin)
//PA0
//MFB
#define MFB_Port GPIOA
#define MFB_Pin  GPIO_Pin_0
#define MFB_IO() GPIO_ReadInputDataBit(MFB_Port, MFB_Pin)
//PA1
//BAT_NTC

//PA2
//FIR_PWM
#define FIR_PWM_Port    GPIOA
#define FIR_PWM_Pin     GPIO_Pin_2
#define FIR_PWM_PIN_H() GPIO_SetBits(FIR_PWM_Port, FIR_PWM_Pin)
#define FIR_PWM_PIN_L() GPIO_ResetBits(FIR_PWM_Port, FIR_PWM_Pin)
#define FIR_PWM_IO(n)   (n ? (FIR_PWM_PIN_H()) : (FIR_PWM_PIN_L()))

//PA3
//BT_V

//PA4
//MOTOR_CUR

//PA7
//Charge_Current

//PB0
//BLED_B
#define BLED_B_Port    GPIOB
#define BLED_B_Pin     GPIO_Pin_0
#define BLED_B_PIN_H() GPIO_SetBits(BLED_B_Port, BLED_B_Pin)
#define BLED_B_PIN_L() GPIO_ResetBits(BLED_B_Port, BLED_B_Pin)
#define BLED_B_IO(n)   (n ? (BLED_B_PIN_H()) : (BLED_B_PIN_L()))

//PB1
//VBUS_V

//PB2
//TEC_PWR
#define TEC_PWR_Port    GPIOB
#define TEC_PWR_Pin     GPIO_Pin_2
#define TEC_PWR_PIN_H() GPIO_SetBits(TEC_PWR_Port, TEC_PWR_Pin)
#define TEC_PWR_PIN_L() GPIO_ResetBits(TEC_PWR_Port, TEC_PWR_Pin)
#define TEC_PWR_IO(n)   (n ? (TEC_PWR_PIN_H()) : (TEC_PWR_PIN_L()))

//PB10
//HB

//PB11
//HC

//PB12
//HA

//PB13
//UL
#define UL_Port    GPIOB
#define UL_Pin     GPIO_Pin_13
#define UL_PIN_H() GPIO_SetBits(UL_Port, UL_Pin)
#define UL_PIN_L() GPIO_ResetBits(UL_Port, UL_Pin)
#define UL_IO(n)   (n ? (UL_PIN_H()) : (UL_PIN_L()))

//PB14
//VL
#define VL_Port    GPIOB
#define VL_Pin     GPIO_Pin_14
#define VL_PIN_H() GPIO_SetBits(VL_Port, VL_Pin)
#define VL_PIN_L() GPIO_ResetBits(UL_Port, VL_Pin)
#define VL_IO(n)   (n ? (VL_PIN_H()) : (VL_PIN_L()))

//PB15
//WL
#define WL_Port    GPIOB
#define WL_Pin     GPIO_Pin_15
#define WL_PIN_H() GPIO_SetBits(WL_Port, WL_Pin)
#define WL_PIN_L() GPIO_ResetBits(UL_Port, WL_Pin)
#define WL_IO(n)   (n ? (WL_PIN_H()) : (WL_PIN_L()))

//PA8
//UH

//PA9
//VH

//PA10
//WH

//PA11
//PWM_C

//PA12
//LED2
#define LED2_Port    GPIOA
#define LED2_Pin     GPIO_Pin_12
#define LED2_PIN_H() GPIO_SetBits(LED2_Port, LED2_Pin)
#define LED2_PIN_L() GPIO_ResetBits(LED2_Port, LED2_Pin)
#define LED2_IO(n)   (n ? (LED2_PIN_H()) : (LED2_PIN_L()))

//PF6
//FI_C
#define FI_C_Port    GPIOF
#define FI_C_Pin     GPIO_Pin_6
#define FI_C_PIN_H() GPIO_SetBits(FI_C_Port, FI_C_Pin)
#define FI_C_PIN_L() GPIO_ResetBits(FI_C_Port, FI_C_Pin)
#define FI_C_IO(n)   (n ? (FI_C_PIN_H()) : (FI_C_PIN_L()))

//PF7
//BI_C
#define BI_C_Port    GPIOF
#define BI_C_Pin     GPIO_Pin_7
#define BI_C_PIN_H() GPIO_SetBits(BI_C_Port, BI_C_Pin)
#define BI_C_PIN_L() GPIO_ResetBits(BI_C_Port, BI_C_Pin)
#define BI_C_IO(n)   (n ? (BI_C_PIN_H()) : (BI_C_PIN_L()))

//PA15
//FAN_C
#define FAN_C_Port    GPIOA
#define FAN_C_Pin     GPIO_Pin_15
#define FAN_C_PIN_H() GPIO_SetBits(FAN_C_Port, FAN_C_Pin)
#define FAN_C_PIN_L() GPIO_ResetBits(FAN_C_Port, FAN_C_Pin)
#define FAN_C_IO(n)   (n ? (FAN_C_PIN_H()) : (FAN_C_PIN_L()))

//PB3
//LED1
#define LED1_Port    GPIOB
#define LED1_Pin     GPIO_Pin_3
#define LED1_PIN_H() GPIO_SetBits(LED1_Port, LED1_Pin)
#define LED1_PIN_L() GPIO_ResetBits(LED1_Port, LED1_Pin)
#define LED1_IO(n)   (n ? (LED1_PIN_H()) : (LED1_PIN_L()))

//PB4
//RLED_B
#define RLED_B_Port    GPIOB
#define RLED_B_Pin     GPIO_Pin_4
#define RLED_B_PIN_H() GPIO_SetBits(RLED_B_Port, RLED_B_Pin)
#define RLED_B_PIN_L() GPIO_ResetBits(RLED_B_Port, RLED_B_Pin)
#define RLED_B_IO(n)   (n ? (RLED_B_PIN_H()) : (RLED_B_PIN_L()))

//PB5
//GLED_B
#define GLED_B_Port    GPIOB
#define GLED_B_Pin     GPIO_Pin_5
#define GLED_B_PIN_H() GPIO_SetBits(GLED_B_Port, GLED_B_Pin)
#define GLED_B_PIN_L() GPIO_ResetBits(GLED_B_Port, GLED_B_Pin)
#define GLED_B_IO(n)   (n ? (GLED_B_PIN_H()) : (GLED_B_PIN_L()))

//PB6
//TXD

//PB7
//RXD

//PB8
//UnderSnr_SCL
#define SCL_Port    GPIOB
#define SCL_Pin     GPIO_Pin_8
#define SCL_PIN_H() GPIO_SetBits(SCL_Port, SCL_Pin)
#define SCL_PIN_L() GPIO_ResetBits(SCL_Port, SCL_Pin)
#define SCL_IO(n)   (n ? (SCL_PIN_H()) : (SCL_PIN_L()))

//PB9
//UnderSnr_SDA
#define SDA_Port    GPIOB
#define SDA_Pin     GPIO_Pin_9
#define SDA_PIN_H() GPIO_SetBits(SDA_Port, SDA_Pin)
#define SDA_PIN_L() GPIO_ResetBits(SDA_Port, SDA_Pin)
#define SDA_IO(n)   (n ? (SDA_PIN_H()) : (SDA_PIN_L()))

#define IO_TX_Port GPIOB
#define IO_TX_Pin  GPIO_Pin_6
#define IO_TX_H()  GPIO_SetBits(IO_TX_Port, IO_TX_Pin)
#define IO_TX_L()  GPIO_ResetBits(IO_TX_Port, IO_TX_Pin)
#define IO_TX(n)   (n ? (IO_TX_H()) : (IO_TX_L()))

void PowerOn_Init(void);
void PowerStop_Init(void);
void IO_Int_Init(void);
async IO_Test(thread_t* pt);

#endif