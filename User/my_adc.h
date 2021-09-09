#ifndef __MY_ADC_H__
#define __MY_ADC_H__
#include "thread.h"
/*------------------------------------------------------------------------*/
void ADCInit(void);
async ADC_Update(thread_t* pt);
u16 filter(u16* array, u8 size);
/*------------------------------------------------------------------------*/
#endif
