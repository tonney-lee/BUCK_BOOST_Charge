#include "sem.h"

SIZE_T SEM[SEM_MAX];
SIZE_T MUTEX[MUTEX_MAX];
/********************************************/ /**
 * \brief    
 *
 * \param
 * \param
 * \return
 *
 ***********************************************/
SIZE_T getSem(SIZE_T* k)
{
    if(*k)
    {
        *k = 0;
        return 1;
    }

    return 0;
}
