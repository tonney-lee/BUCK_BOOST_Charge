#include "usr.h"

/**
 * @description:
 * @param {*}
 * @return {*}
 */

async user(thread_t *pt)
{
    Thread_BEGIN;
    {
        PowerOn_Init();
        IO_Int_Init();
        Time1Initial();  // MOTOR & PWM_C
        Time3Initial();  // RGB
        Time15Initial(); // FIR
        ADCInit();
        UartInit();
        //
        Thread_Start(ADC_Update, &threadInfo.status);
        Thread_Start(key_Update, &threadInfo.status);
        Thread_Start(uart1_Rcv_Update, &threadInfo.status);
        Thread_Start(uart_send_test, &threadInfo.status);
        // Thread_Start(IO_Test, &threadInfo.status);

        while (1)
        {
            Thread_Yield();
        }
    }
    Thread_END;
}
