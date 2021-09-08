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
    BTN = 0,
    DC_IN,
    MG_NTC,
    BAT_NTC,
    MOTOR_OVER_CURRENT,
    LOW_BATTERY,

} KeyIndex;
/*------------------------------------------------------------------------*/
#ifdef SIMPLE_KEY

typedef struct
{
    u8 keyIn;
    u8 ShortKeyTime;
    u16 LongKeyTime;
    u8 KeyUpTime;
    u16 time;
    u8 state;
    KeyEvent key_envent;

} key_t;

#else

typedef struct
{
    u8 keyIn;
    u8 time;
    u8 LongKeyTime;
    u8 KeyUpTime;
    u8 state;
    KeyEvent key_envent;

} key_t;

#endif

extern key_t KEY[6];
extern u16 clicktime;
/*------------------------------------------------------------------------*/
//#define GetKeyVal(sw) sys.KEY[sw].key_envent
#define GetKeyVal(sw) KEY[sw].key_envent
/*------------------------------------------------------------------------*/
void key_Update(void);
void rst_keyUpdate(void);
/*------------------------------------------------------------------------*/
#endif
