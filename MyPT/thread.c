#include "thread.h"
/*---------------------------------------------------------------------------*/
volatile dly_t gSystick;
pt_thread gTask[MAX_THREADS];
ptThreadInfo threadInfo = {THREAD_WAITING, 0, 0, MAX_THREADS};
/*---------------------------------------------------------------------------*/
void TaskRun(void)
{
    while(1)
    {
        static SIZE_T i;

        for(i = 0; gTask[i].func && i < MAX_THREADS; i++)
        {
            if(gTask[i].status < THREAD_EXITED)
            {
                gTask[i].status = (ThreadStatus)gTask[i].func(&gTask[i].pt);
            }
        }

        RstWatchDog();
    }
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

#define SYSTICK_ADJ 1

SIZE_T delay_interval(dly_t* t, dly_t interval)
{
    dly_t clock = gSystick;
    clock -= *t;
    if(clock >= interval * SYSTICK_ADJ)
        return 1;
    return 0;
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void delay_set(dly_t* t)
{
    *t = gSystick;
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

void Thread_Start(ptFUNC func, ThreadStatus* status)
{
    SIZE_T threadIndex = 0;

    // First find a gap in the array (if there is one)
    while((gTask[threadIndex].func != NULL) && (gTask[threadIndex].func != func) && (threadIndex < MAX_THREADS))
    {
        threadIndex++;
    }

    if(gTask[threadIndex].func == func)
    {
        gTask[threadIndex].pt.lc = 0;
        gTask[threadIndex].status = THREAD_WAITING;

        *status = THREAD_OK;
        return;
    }

    if(threadIndex == MAX_THREADS)
    {
        *status = THREAD_ERR;
        return;
    }

    // If we're here, there is a space in the task array
    gTask[threadIndex].func = func;
    gTask[threadIndex].pt.lc = 0;
    gTask[threadIndex].status = THREAD_WAITING;

    threadInfo.MaxThreadIndex = threadIndex; // return position of task (to allow later deletion)
    threadInfo.SizeofThreadBytes = sizeof(dly_t) + sizeof(pt_thread);
    threadInfo.MaxThread = SIZEOF_ARR(gTask);
    threadInfo.SizeofTaskBytes = threadInfo.MaxThread * threadInfo.SizeofThreadBytes;
    *status = THREAD_OK;
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
ThreadStatus getThreadStatus(ptFUNC func)
{
    SIZE_T threadIndex = 0;

    while((gTask[threadIndex].func != NULL) && (gTask[threadIndex].func != func) && (threadIndex < MAX_THREADS))
    {
        threadIndex++;
    }

    if(gTask[threadIndex].func == func)
    {
        return gTask[threadIndex].status;
    }

    return THREAD_ERR;
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void Thread_Suspend(ptFUNC func, ThreadStatus* status)
{
    SIZE_T threadIndex = 0;

    while((gTask[threadIndex].func != NULL) && (gTask[threadIndex].func != func) && (threadIndex < MAX_THREADS))
    {
        threadIndex++;
    }

    if(gTask[threadIndex].func == func)
    {
        if(gTask[threadIndex].status != THREAD_SUSPENDED)
        {
            gTask[threadIndex].status = THREAD_SUSPENDED;

            *status = THREAD_OK;
            return;
        }
    }

    *status = THREAD_ERR;
}
/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
void Thread_Resume(ptFUNC func, ThreadStatus* status)
{
    SIZE_T threadIndex = 0;

    while((gTask[threadIndex].func != NULL) && (gTask[threadIndex].func != func) && (threadIndex < MAX_THREADS))
    {
        threadIndex++;
    }

    if(gTask[threadIndex].func == func)
    {
        if(gTask[threadIndex].status == THREAD_SUSPENDED)
        {
            gTask[threadIndex].status = THREAD_WAITING;

            *status = THREAD_OK;
            return;
        }
    }

    *status = THREAD_ERR;
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
    //TimingDelay--;
    gSystick++;
}

