#ifndef _MY_UART_H_
#define _MY_UART_H_
/*---------------------------------------------------------------------------*/
#include "thread.h"

typedef enum
{
    sys_off = 0,
    sys_on,
    sys_dc_in,
    sys_exception,
    sys_sleep,
    sys_init,
    sys_low_bat,

} sys_status_t;

typedef struct
{
    sys_status_t SysStatus;
    u8 rgb_bat_charging_status;
    u16 adc_values[4]; //0:MNTC 1:BT_V 2:BAT_NTC 3:MOTOR_CUR
    u16 pwm_led;
    u16 pwm_target_val;
    u8 moto_level_index;
    u8 rgb_bat_voltage_status;
    u32 inc;
    u8 k2;
    u8 dc_in;
    u16 I;
    u16 v;
    u8 fg_cnt;

} sys_t;
/*---------------------------------------------------------------------------*/
extern sys_t sys;

void UartInit(void);
void UartSend(u8* txBuf, SIZE_T tx_num);
async uart1_Rcv_Update(thread_t* pt);
async uart_send_test(thread_t* pt);
/*---------------------------------------------------------------------------*/
#endif
