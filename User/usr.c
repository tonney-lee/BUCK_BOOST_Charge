#include "usr.h"

/**
 * @description: 
 * @param {*}
 * @return {*}
 */

async user(thread_t* pt)
{
    Thread_BEGIN;
    {
        PowerOn_Init();
        Time1Initial();  //MOTOR & PWM_C
        Time3Initial();  //RGB
        Time15Initial(); //FIR
        ADCInit();
        Thread_Start(IO_Test, &threadInfo.status);
        Thread_Start(ADC_Update, &threadInfo.status);

        while(1)
        {
            Thread_Yield();
        }
    }
    Thread_END;
}
