#ifndef __THREAD_H__
#define __THREAD_H__
/* MyPt V2.3 EES WangDong 2021-06-16 */
/*--------------------------------------------------------------------------------------------------------------------------------*/
#include "FT32f0xx.h"
#include "./pt-1.4/pt.h"
#include "typedef.h"
#include "sem.h"
#include "systick.h"
/*--------------------------------------------------------------------------------------------------------------------------------*/
typedef struct pt thread_t;
typedef char async;
typedef async (*ptFUNC)(thread_t* pt);


typedef enum
{
    THREAD_WAITING = 0,
    THREAD_YIELDED,
    THREAD_EXITED,
    THREAD_ENDED,
    THREAD_SUSPENDED,
    THREAD_OK,
    THREAD_ERR

} ThreadStatus;

typedef struct
{
    ptFUNC func;
    thread_t pt;
    ThreadStatus status;

} pt_thread;

typedef struct
{
    ThreadStatus status;
    u8 SizeofThreadBytes;
    u16 SizeofTaskBytes;
    u8 MaxThreadIndex;
    u8 MaxThread;

} ptThreadInfo;

/*--------------------------------------------------------------------------------------------------------------------------------*/
#define Thread_BEGIN \
    static dly_t dly; \
    PT_BEGIN(pt);
#define Thread_END              PT_END(pt);
#define Thread_Restart()        PT_RESTART(pt)
#define Thread_Yield()          PT_YIELD(pt)
#define Thread_TIMEOUT(SysTick) delay_interval(&dly, SysTick)
#define Thread_Interrupt() \
    do { \
        while(1) { Thread_Yield(); } \
    } while(0)
#define Thread_Wait_Until(cond) PT_WAIT_UNTIL(pt, cond)
#define Thread_Sleep(SysTick) \
    do { \
        delay_set(&dly); \
        Thread_Wait_Until(Thread_TIMEOUT(SysTick)); \
    } while(0)
#define Thread_Sleep_Until(SysTick, cond) \
    do { \
        delay_set(&dly); \
        Thread_Wait_Until(Thread_TIMEOUT(SysTick) || cond); \
    } while(0)
#define Thread_Wait_Sem(x) \
    do { \
        Thread_Wait_Until(x); \
        ClrSem(x); \
    } while(0)
#define Thread_Abort() PT_EXIT(pt)
#define Thread_Join(x) \
    do { \
        Thread_Wait_Until(getThreadStatus(x) == THREAD_EXITED); \
    } while(0)
#define Thread_IsAlive(x) (getThreadStatus(x) < THREAD_EXITED)
#define Thread_Wait_Mutex(x) \
    do { \
        Thread_Wait_Until(!x); \
        SetSem(x); \
    } while(0)
#define Thread_Wait_Until_IT(cond) PT_WAIT_UNTIL_IT(pt, cond)
#define Thread_Sleep_Until_IT(SysTick, cond) \
    do {delay_set((dly);Thread_Wait_Until_IT(Thread_TIMEOUT(SysTick)||cond); \
    } while(0)
#define PT_WAIT_UNTIL_IT(pt, cond) \
    do { \
        DI(); \
        LC_SET((pt)->lc); \
        if(!(cond)) \
        { \
            EI(); \
            return PT_WAITING; \
        } \
        EI(); \
    } while(0)
/*--------------------------------------------------------------------------------------------------------------------------------*/
#define RstWatchDog() \
    { \
        ; \
    }
extern ptThreadInfo threadInfo;
#define DEFINE_MAX_THREADS
#ifndef DEFINE_MAX_THREADS
typedef enum
{
    __io_test,
    __motor_ctl,
    __usr,
    MAX_THREADS
} ThreadList;
#else
#define MAX_THREADS (16)
#endif
/*--------------------------------------------------------------------------------------------------------------------------------*/
extern volatile dly_t gSystick;
extern void SysTickInit(void);
void delay_set(dly_t* t);
SIZE_T delay_interval(dly_t* t, dly_t interval);
/*--------------------------------------------------------------------------------------------------------------------------------*/
void Thread_Start(ptFUNC func, ThreadStatus* status);
ThreadStatus getThreadStatus(ptFUNC func);
void Thread_Suspend(ptFUNC func, ThreadStatus* status);
void Thread_Resume(ptFUNC func, ThreadStatus* status);
void TaskRun(void);
/*--------------------------------------------------------------------------------------------------------------------------------*/
#endif /* __THREAD_H__ */

/** @} */
/** @} */
