#ifndef __MY_ADC_H__
#define __MY_ADC_H__
#include "thread.h"
/*------------------------------------------------------------------------*/
 
 
/*------------------------------------------------------------------------*/
void ADC_INITIAL(void);
void set_ADC_CH(u8 ADCchannel);
u16 getADCResult(void);
void adc_Update(void);
u16 filter(u16* array, u8 size);
void DelayUs(u8 Time);
void adc_update(void);
/*------------------------------------------------------------------------*/
#endif
