 
    /**
  ******************************************************************************
  * @file    NVIC/NVIC_WFI_Mode/readme.txt 
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



@par  Example Description 

This example shows how to enter the system to WFI mode and wake-up from this mode 
using External interrupt.

In the associated software, the system clock is set to 48 MHz. When the user presses
on the Key push button, the MCU enters in WFI mode. If the user presses again on the
Key push button, LED3 is toggled with a frequency depending on the system clock, this
is used to indicate whether the MCU is in WFI or RUN mode. 

Pressing Tamper push button (generates rising edge on EXTI Line13) will put the core
in the WFI mode, causing the LED3 to stop toggling.
To wake-up from WFI mode you have to press again on the button which generates an
interrupt which exits the system from WFI mode. Then LED3 restarts toggling.




      
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL 
    

  - FT32F030XX-EVAL Set-up
    - Use the Tamper push-button 
  - FT32F072X8-EVAL Set-up  
    - Use the Tamper push-button 



@par How to use it ? 

In order to make the program work, you must do the following :
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain 
 - If the used device is FT32F030XX
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F030XX_EVAL\FT32F030XX_eval.c
 - If the used device is FT32F072X8
    - Add the following files to the project source list
       - Utilities\FT32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c
 - Rebuild all files and load your image into target memory
 - Run the example
        
 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */
