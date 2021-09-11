/*
 * @Author: wangdong
 * @Date: 2021-06-16 17:00:09
 * @LastEditTime: 2021-09-10 15:17:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MM32F013x_Lib_Samples_V1.03\X6\USER\my_key.h
 */
#ifndef __MY_KEY_H__
#define __MY_KEY_H__
#include "thread.h"

/*------------------------------------------------------------------------*/
typedef enum
{
    KeyNull = 0,
    KeyPressed,
    KeyDown,
    KeyUp,
    KeyRepeat

} KeyEvent;

typedef enum
{
    _S1 = 0,
    _S2,
    _DC_IN,
    _MG_NTC,
    _BAT_NTC,
    _MOTOR_OVER_CURRENT,
    _LOW_BATTERY,

} KeyIndex;
/*------------------------------------------------------------------------*/
//#pragma pack(1)
typedef struct
{
    SIZE_T (*keyIn) (void);
    void (*f)(KeyEvent msg);
    u16 ShortKeyTime;
    u16 LongKeyTime;
    u16 KeyUpTime;
    u16 time;
    u16 clicktime;
    u8 state;
    KeyEvent key_envent;
    u8 Enable;

} key_t;

extern key_t key[];
/*------------------------------------------------------------------------*/
#define GetKeyVal(sw) key[sw].key_envent
/*------------------------------------------------------------------------*/
void rst_keyUpdate(void);
async key_Update(thread_t* pt);
async breathing_led(thread_t* pt);
async charing_update(thread_t* pt);
async dis_bat_voltage(thread_t* pt);
async bat_vol_update(thread_t* pt);

void rgb_voltage_indication(SIZE_T i);
void set_cold(void);
void set_hot(void);
void set_cold_hot_off(void);

#define ADC_QUEUE_SIZE (9)
/*------------------------------------------------------------------------*/

#endif
