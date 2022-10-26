#include "my_key.h"
#include "my_uart.h"
#include "my_io_port.h"
/*-----------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

SIZE_T S1_PIN(void);
SIZE_T S2_PIN(void);
SIZE_T DC_IN_PIN(void);
SIZE_T MOTOR_NTC_PIN(void);
SIZE_T MOTOR_CUR_PIN(void);
SIZE_T BAT_NTC_PIN(void);
SIZE_T BAT_LOW_BATTERY_TEST(void);

SIZE_T S1_PIN(void)
{
    return MODE_IO();
}
SIZE_T S2_PIN(void)
{
    //return MFB_IO();
}
SIZE_T DC_IN_PIN(void)
{
    return !DC_IN_IO();
}
SIZE_T MOTOR_NTC_PIN(void)
{
    return 0;
}
SIZE_T MOTOR_CUR_PIN(void)
{
    return 0;
}
SIZE_T BAT_NTC_PIN(void)
{
    return 0;
}
SIZE_T BAT_LOW_BATTERY_TEST(void)
{
    return 0;
}

void DC_IN_CB(KeyEvent msg);
void S1_CB(KeyEvent msg);
void S2_CB(KeyEvent msg);
void Motor_temp_protect_cb(KeyEvent msg);
void Motor_cur_protect_cb(KeyEvent msg);
void BAT_temp_protect_cb(KeyEvent msg);
void BAT_low_battery_protect_cb(KeyEvent msg);
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void DC_IN_CB(KeyEvent msg)
{
    switch(msg)
    {
        case KeyDown:
        {
        }
        break;

        case KeyUp:
        {
        }
        break;
    }
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void S1_CB(KeyEvent msg)
{
    switch(msg)
    {
        case KeyDown:
        {
        }
        break;

        case KeyUp:
        {
        }
        break;
    }
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void S2_CB(KeyEvent msg)
{
    switch(msg)
    {
        case KeyDown:
        {
        }
        break;

        case KeyUp:
        {
        }
        break;
    }
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void Motor_temp_protect_cb(KeyEvent msg)
{
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void Motor_cur_protect_cb(KeyEvent msg)
{
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void BAT_temp_protect_cb(KeyEvent msg)
{
}
/**
 * @description: 
 * @param {KeyEvent} msg
 * @return {*}
 */
void BAT_low_battery_protect_cb(KeyEvent msg)
{
    switch(msg)
    {
        case KeyDown:
        {
        }
        break;

        case KeyUp:
        {
        }
        break;
    }
}

key_t key[] = {
    {S1_PIN, S1_CB, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
    {S2_PIN, S2_CB, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
    {DC_IN_PIN, DC_IN_CB, 7, 200, 100, 0, 0, 0, KeyNull, TRUE},
    {MOTOR_NTC_PIN, Motor_temp_protect_cb, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
    {MOTOR_CUR_PIN, Motor_cur_protect_cb, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
    {BAT_NTC_PIN, BAT_temp_protect_cb, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
    {BAT_LOW_BATTERY_TEST, BAT_low_battery_protect_cb, 7, 100, 7, 0, 0, 0, KeyNull, TRUE},
};

/**
 * @description: reset key Object value
 * @param {*}
 * @return {*}
 */
void rst_keyUpdate(void)
{
    //memcpy((void*)key, (const void*)_key, sizeof(_key) - sizeof(_key[0]));
}
/**
 * @description: key value update
 * @param none
 * @return none
 */
void keyDrv(void)
{
    key_t* p = key;

    for(SIZE_T i = 0; i < SIZEOF_ARR(key); i++, p++)
    {
        SIZE_T key_pressed = p->keyIn();
        p->key_envent = KeyNull;

        switch(p->state)
        {
            case 0:
            {
                if(!key_pressed)
                {
                    p->state++;
                }
            }
            break;

            case 1:
            {
                p->time++;

                if(key_pressed)
                {
                    if(p->time >= p->ShortKeyTime)
                    {
                        p->key_envent = KeyPressed;
                    }

                    p->time = 0;
                    p->state = 0;
                }
                else if(p->time >= p->LongKeyTime)
                {
                    p->key_envent = KeyDown;
                    p->state++;
                }
            }
            break;

            case 2:
            {
                if(key_pressed)
                {
                    if(++(p->time) >= p->KeyUpTime)
                    {
                        p->key_envent = KeyUp;
                        p->time = 0;
                        p->state = 0;
                    }
                }
                else
                {
                    p->key_envent = KeyRepeat;
                }
            }
            break;
        }
    }
}

/**
 * @description: call callback fuction for key value handle
 * @param {*}
 * @return {*}
 */
void keyHandle(void)
{
    key_t* p = key;
    //
    for(SIZE_T i = 0; i < SIZEOF_ARR(key); i++, p++)
    {
        if(p->key_envent)
        {
            if(p->Enable && p->f)
            {
                p->f(p->key_envent);
                //
                if(p->key_envent == KeyUp)
                {
                    p->clicktime = 0;
                }
            }
            //
            p->key_envent = KeyNull;
        }
    }
}

/**
 * @description: 
 * @param {thread_t*} pt
 * @return {*}
 */
async key_Update(thread_t* pt)
{
    Thread_BEGIN;
    {
        while(1)
        {
            keyDrv();
            keyHandle();
            Thread_Sleep(10);
        }
    }
    Thread_END;
}
