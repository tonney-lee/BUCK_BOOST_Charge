/**
  @page TIM_6Steps TIM 6 Steps example
  
  @verbatim
  ******************** (C) COPYRIGHT 2014 FMD *******************
  * @file    TIM/TIM_6steps/readme.txt 
  * @author  AE
  * @version V1.0.0
  * @date    29-MAR2021
  * @brief   TIM 6Steps Description.
  ******************************************************************************
  
@par Example Description 

This example shows how to configure the TIM1 peripheral to generate 6 Steps.
The FT32f0xx TIM1 peripheral offers the possibility to program in advance the 
configuration for the next TIM1 outputs behaviour (step) and change the configuration
of all the channels at the same time. This operation is possible when the COM 
(commutation) event is used.
The COM event can be generated by software by setting the COM bit in the TIM1_EGR
register or by hardware (on TRC rising edge).
In this example, a software COM event is generated each 100 ms: using the SysTick 
interrupt.
The TIM1 is configured in Timing Mode, each time a COM event occurs, a new TIM1
configuration will be set in advance.

The break Polarity is used at High level.

The following Table describes the TIM1 Channels states:
 @verbatim
              -----------------------------------------------
             | Step1 | Step2 | Step3 | Step4 | Step5 | Step6 |
   ----------------------------------------------------------
  |Channel1  |   1   |   0   |   0   |   0   |   0   |   1   |
   ----------------------------------------------------------
  |Channel1N |   0   |   0   |   1   |   1   |   0   |   0   |
   ----------------------------------------------------------
  |Channel2  |   0   |   0   |   0   |   1   |   1   |   0   |
   ----------------------------------------------------------
  |Channel2N |   1   |   1   |   0   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3  |   0   |   1   |   1   |   0   |   0   |   0   |
   ----------------------------------------------------------
  |Channel3N |   0   |   0   |   0   |   0   |   1   |   1   |
   ----------------------------------------------------------
 
        - TIM1_CH3  pin (PA.10)
        - TIM1_CH1N pin (PA.07)  
        - TIM1_CH2  pin (PA.09)  
        - TIM1_CH3N pin (PB.01)
        - TIM1_CH1  pin (PA.08)  
        - TIM1_CH2N pin (PB.00)    
     - Connect the TIM1 break pin TIM1_BKIN pin (PB.12) to the GND. To generate a 
       break event, switch this pin level from 0V to 3.3V. 
  


@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - Select the appropriate workspace 
 - Rebuild all files and load your image into target memory
 - Run the example

 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */
