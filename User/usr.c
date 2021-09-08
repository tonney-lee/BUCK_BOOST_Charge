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
        Thread_Start(IO_Test, &threadInfo.status);

        while(1)
        {
            Thread_Yield();
        }
    }
    Thread_END;
}
