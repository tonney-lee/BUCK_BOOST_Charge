  /**
  ******************************************************************************
  * @file    TIM/TIM_PWMInput/readme.txt 
  * @author  AE
  * @version V1.0.0
  * @date    29-MAR-2021
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2021 FMD</center></h2>
  *
  *
  *        http://www.fremontmicro.com
  *

  *
  ******************************************************************************
  */


@par Example Description 

This example shows how to use the TIM peripheral to measure the frequency and 
duty cycle of an external signal.

The TIM3 Clock frequency is set to SystemCoreClock(Hz), the Prescaler is 0 so the 
counter clock is SystemCoreClock(Hz).
SystemCoreClock is set to 48 MHz in this example.

TIM3 is configured in PWM Input Mode: the external signal is connected to 
TIM3 Channel2 used as input pin.

To measure the frequency and the duty cycle we use the TIM3 CC2 interrupt request,
so In the TIM3_IRQHandler routine, the frequency and the duty cycle of the external 
signal are computed. 

The "Frequency" variable contains the external signal frequency:
  TIM3 counter clock = SystemCoreClock
  Frequency = TIM3 counter clock / TIM3_CCR2 in Hz 

The "DutyCycle" variable contains the external signal duty cycle:
   DutyCycle = (TIM3_CCR1*100)/(TIM3_CCR2) in %.

The minimum frequency value to measure is 733 Hz (TIM3 counter clock / CCR MAX). 
 



         


  - FT32F030XX-EVAL Set-up
    - Connect the external signal to the TIM3 CH2 pin (PA.07) to measure the frequency and 
      duty cycle 
  - FT32F072X8-EVAL Set-up
    - Connect the external signal to the TIM3 CH2 pin (PA.07) to measure the frequency and 
      duty cycle 




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
