#ifndef __MY_IO_PORT_H__
#define __MY_IO_PORT_H__

#include "thread.h"

// PA0
// Battery Voltage Measure
#define BAT_VOLTAGE_Port GPIOA
#define BAT_VOLTAGE GPIO_Pin_0
// PA1  Cell Number Option
#define CELL_NUMBER_OPTION_Port GPIOA
#define CELL_NUMBER_OPTION_PIN GPIO_Pin_1
// PA2  Vin Voltage Measure
#define VIN_VOLTAGE_MEASURE_Port GPIOA
#define VIN_VOLTAGE_MEASURE_Pin GPIO_Pin_2
// PA3   Frequency Option
#define PWM_FREQUENCY_OPTION_Port GPIOA
#define PWM_FREQUENCY_OPTION_Pin GPIO_Pin_3
// PA4   Charge Current
#define CHARGE_CURRENT_Port GPIOA
#define CHARGE_CURRENT_Pin GPIO_Pin_4
// PA8   PWM_Buck
#define PWM_BUCK_Port GPIOA
#define PWM_BUCK_Pin GPIO_Pin_8
// PA9  PWM_Boost
#define PWM_BOOST_Port GPIOA
#define PWM_BOOST_Pin GPIO_Pin_9
// PA10 VBAT_M_ON/OFF
#define BAT_VOLTAGE_MEASURE_ON_OFF_Port GPIOA
#define BAT_VOLTAGE_MEASURE_ON_OFF_Pin GPIO_Pin_10
// PA11  Single Cell Full Voltage Option
#define SINGLE_CELL_FULL_VOLTAGE_OPT1_Port GPIOA
#define SINGLE_CELL_FULL_VOLTAGE_OPT1_Pin GPIO_Pin_11
// PA12  Single Cell Full Voltage Option
#define SINGLE_CELL_FULL_VOLTAGE_OPT2_Port GPIOA
#define SINGLE_CELL_FULL_VOLTAGE_OPT2_Pin GPIO_Pin_12
// PA15
#define FAN_C_Port GPIOA
#define FAN_C_Pin GPIO_Pin_15
#define FAN_C_PIN_H() GPIO_SetBits(FAN_C_Port, FAN_C_Pin)
#define FAN_C_PIN_L() GPIO_ResetBits(FAN_C_Port, FAN_C_Pin)
#define FAN_C_IO(n) (n ? (FAN_C_PIN_H()) : (FAN_C_PIN_L()))

// PB0
// BLED_B
#define BLED_B_Port GPIOB
#define BLED_B_Pin GPIO_Pin_0
#define BLED_B_PIN_H() GPIO_SetBits(BLED_B_Port, BLED_B_Pin)
#define BLED_B_PIN_L() GPIO_ResetBits(BLED_B_Port, BLED_B_Pin)
#define BLED_B_IO(n) (n ? (BLED_B_PIN_H()) : (BLED_B_PIN_L()))
// PB1  NO FUNCTION
// PB2 Charge_EN
#define CHARGE_EN_Port GPIOB
#define CHARGE_EN_Pin GPIO_Pin_2
#define CHARGE_EN_H() GPIO_SetBits(CHARGE_EN_Port, CHARGE_EN_Pin)
#define CHARGE_EN_L() GPIO_ResetBits(CHARGE_EN_Port, CHARGE_EN_Pin)
#define CHARGE_EN(n) (n ? (CHARGE_EN_H()) : (CHARGE_EN_L()))
// PB3 Gate_driver_EN
#define GATE_DRIVER_EN_Port GPIOB
#define GATE_DRIVER_EN_Pin GPIO_Pin_3
#define GATE_DRIVER_EN_H() GPIO_SetBits(GATE_DRIVER_EN_Port, GATE_DRIVER_EN_Pin)
#define GATE_DRIVER_EN_L() GPIO_ResetBits(GATE_DRIVER_EN_Port, GATE_DRIVER_EN_Pin)
#define GATE_DRIVER_EN(n) (n ? (GATE_DRIVER_EN_H()) : (GATE_DRIVER_EN_L()))
// PB4  Output 5V for Save Power
#define OUTPUT_5V_Port GPIOB
#define OUTPUT_5V_Pin GPIO_Pin_4
#define OUTPUT_5V_PIN_H() GPIO_SetBits(OUTPUT_5V_Port, OUTPUT_5V_Pin)
#define OUTPUT_5V_PIN_L() GPIO_ResetBits(OUTPUT_5V_Port, OUTPUT_5V_Pin)
#define OUTPUT_5V(n) (n ? (OUTPUT_5V_PIN_H()) : (OUTPUT_5V_PIN_L()))
// PB5  
#define GLED_B_Port GPIOB
#define GLED_B_Pin GPIO_Pin_5
#define GLED_B_PIN_H() GPIO_SetBits(GLED_B_Port, GLED_B_Pin)
#define GLED_B_PIN_L() GPIO_ResetBits(GLED_B_Port, GLED_B_Pin)
#define GLED_B_IO(n) (n ? (GLED_B_PIN_H()) : (GLED_B_PIN_L()))
// PB6 TXD
// PB7 RXD
// PB8  UnderSnr_SCL
#define SCL_Port GPIOB
#define SCL_Pin GPIO_Pin_8
#define SCL_PIN_H() GPIO_SetBits(SCL_Port, SCL_Pin)
#define SCL_PIN_L() GPIO_ResetBits(SCL_Port, SCL_Pin)
#define SCL_IO(n) (n ? (SCL_PIN_H()) : (SCL_PIN_L()))
// PB9 UnderSnr_SDA
#define SDA_Port GPIOB
#define SDA_Pin GPIO_Pin_9
#define SDA_PIN_H() GPIO_SetBits(SDA_Port, SDA_Pin)
#define SDA_PIN_L() GPIO_ResetBits(SDA_Port, SDA_Pin)
#define SDA_IO(n) (n ? (SDA_PIN_H()) : (SDA_PIN_L()))
#define IO_TX_Port GPIOB
#define IO_TX_Pin GPIO_Pin_6
#define IO_TX_H() GPIO_SetBits(IO_TX_Port, IO_TX_Pin)
#define IO_TX_L() GPIO_ResetBits(IO_TX_Port, IO_TX_Pin)
#define IO_TX(n) (n ? (IO_TX_H()) : (IO_TX_L()))
// PB10
// PB11
// PB12
// PB13
#define UL_Port GPIOB
#define UL_Pin GPIO_Pin_13
#define UL_PIN_H() GPIO_SetBits(UL_Port, UL_Pin)
#define UL_PIN_L() GPIO_ResetBits(UL_Port, UL_Pin)
#define UL_IO(n) (n ? (UL_PIN_H()) : (UL_PIN_L()))
// PB14
#define VL_Port GPIOB
#define VL_Pin GPIO_Pin_14
#define VL_PIN_H() GPIO_SetBits(VL_Port, VL_Pin)
#define VL_PIN_L() GPIO_ResetBits(UL_Port, VL_Pin)
#define VL_IO(n) (n ? (VL_PIN_H()) : (VL_PIN_L()))
// PB15
#define WL_Port GPIOB
#define WL_Pin GPIO_Pin_15
#define WL_PIN_H() GPIO_SetBits(WL_Port, WL_Pin)
#define WL_PIN_L() GPIO_ResetBits(UL_Port, WL_Pin)
#define WL_IO(n) (n ? (WL_PIN_H()) : (WL_PIN_L()))

// PC13
// DC_IN
#define DC_IN_Port GPIOC
#define DC_IN_Pin GPIO_Pin_13
#define DC_IN_IO() GPIO_ReadInputDataBit(DC_IN_Port, DC_IN_Pin)
// PC14
// PWR_1
#define POWER_Port GPIOC
#define POWER_Pin GPIO_Pin_14
#define POWER_PIN_H() GPIO_SetBits(POWER_Port, POWER_Pin)
#define POWER_PIN_L() GPIO_ResetBits(POWER_Port, POWER_Pin)
#define POWER_IO(n) (n ? (POWER_PIN_H()) : (POWER_PIN_L()))
// PC15
// BT_RESET
#define BT_RESET_Port GPIOC
#define BT_RESET_Pin GPIO_Pin_15
#define BT_RESET_PIN_H() GPIO_SetBits(BT_RESET_Port, BT_RESET_Pin)
#define BT_RESET_PIN_L() GPIO_ResetBits(BT_RESET_Port, BT_RESET_Pin)
#define BT_RESET_IO(n) (n ? (BT_RESET_PIN_H()) : (BT_RESET_PIN_L()))
// PF0
// BV_ON
#define BV_ON_Port GPIOF
#define BV_ON_Pin GPIO_Pin_0
#define BV_ON_PIN_H() GPIO_SetBits(BV_ON_Port, BV_ON_Pin)
#define BV_ON_PIN_L() GPIO_ResetBits(BV_ON_Port, BV_ON_Pin)
#define BV_ON_IO(n) (n ? (BV_ON_PIN_H()) : (BV_ON_PIN_L()))
// PF1
// MODE
#define MODE_Port GPIOF
#define MODE_Pin GPIO_Pin_1
#define MODE_IO() GPIO_ReadInputDataBit(MODE_Port, MODE_Pin)

// PF6
// FI_C
#define FI_C_Port GPIOF
#define FI_C_Pin GPIO_Pin_6
#define FI_C_PIN_H() GPIO_SetBits(FI_C_Port, FI_C_Pin)
#define FI_C_PIN_L() GPIO_ResetBits(FI_C_Port, FI_C_Pin)
#define FI_C_IO(n) (n ? (FI_C_PIN_H()) : (FI_C_PIN_L()))

// PF7
// BI_C
#define BI_C_Port GPIOF
#define BI_C_Pin GPIO_Pin_7
#define BI_C_PIN_H() GPIO_SetBits(BI_C_Port, BI_C_Pin)
#define BI_C_PIN_L() GPIO_ResetBits(BI_C_Port, BI_C_Pin)
#define BI_C_IO(n) (n ? (BI_C_PIN_H()) : (BI_C_PIN_L()))

void PowerOn_Init(void);
void PowerStop_Init(void);
void IO_Int_Init(void);
async IO_Test(thread_t *pt);

#endif
