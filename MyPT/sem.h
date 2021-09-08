#ifndef SEM_H_INCLUDED
#define SEM_H_INCLUDED
#include "typedef.h"
/*-----------------------------------------------------------------------------------*/
typedef enum
{
    SEM_BASE = 0,

    //
    SEM_MAX

} SEM_ID;
/*-----------------------------------------------------------------------------------*/
typedef enum
{
    MUTEX_BASE = 0,
    //
    MUTEX_MAX

} MUTEX_ID;
/*-----------------------------------------------------------------------------------*/
extern SIZE_T SEM[];
extern SIZE_T MUTEX[];

SIZE_T getSem(SIZE_T* k);
/*-----------------------------------------------------------------------------------*/

#endif // SEM_H_INCLUDED
