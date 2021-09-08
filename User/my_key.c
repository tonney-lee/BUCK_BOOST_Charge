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

#define ShortKeyTime 5

static const key_t _KEY[6] = {
    {0, 0, 50, 7, 0, 0},   //
    {0, 0, 45, 100, 0, 0}, //DC IN
    {0, 0, 100, 7, 0, 0},
    {0, 0, 100, 7, 0, 0},
    {0, 0, 100, 7, 0, 0},
    {0, 0, 250, 250, 0, 0},
};

key_t KEY[6] = {
    {0, 0, 50, 7, 0, 0},
    {0, 0, 45, 100, 0, 0},
    {0, 0, 100, 7, 0, 0},
    {0, 0, 100, 7, 0, 0},
    {0, 0, 100, 7, 0, 0},
    {0, 0, 250, 250, 0, 0},
};
/*-----------------------------------------------------------*/
/** \brief  reset key update value
 *
 * \param
 * \param
 * \return
 *
 */

void rst_keyUpdate(void)
{
    memcpy((void*)KEY, (const void*)_KEY, sizeof(_KEY) - sizeof(_KEY[5]));
}
/*-----------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

//ADC channel
//AN2 AN3 AN4 AN5 1.2v
//MG NTC
//BAT NTC
//BT V
//MOTOR CURRENT

void key_Update(void)
{
    static dly_t dly;
    // key_t *p = sys.KEY;
    key_t* p = KEY;

    if(delay_interval(&dly, 10))
    {
        delay_set(&dly);

        
  
        //MG NTC  100C
        (sys.adc_values[0] < 259 || sys.adc_values[0] > 3800) ? (KEY[2].keyIn = 0) : (KEY[2].keyIn = 1);
        //BAT NTC 65C
        (sys.adc_values[2] < 703 || sys.adc_values[2] > 3800) ? (KEY[3].keyIn = 0) : (KEY[3].keyIn = 1);
        //12A  protect 5m    0.060V
        (sys.adc_values[3] * 5000ul / 4096 * 2ul >= 60) ? (KEY[4].keyIn = 0) : (KEY[4].keyIn = 1);
        //9V  undervoltage BAT V
        (sys.adc_values[1] * 5000ul / 4096 * 2ul <= 3000) ? (KEY[5].keyIn = 0) : (KEY[5].keyIn = 1);

        for(u8 i = 0; i < SIZEOF_ARR(KEY); i++, p++)
        {
            u8 key_pressed = p->keyIn;
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
                        if(p->time >= ShortKeyTime)
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
}
