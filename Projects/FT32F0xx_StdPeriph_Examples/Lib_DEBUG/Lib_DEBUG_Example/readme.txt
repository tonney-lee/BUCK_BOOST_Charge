  
     /**
  ******************************************************************************
 * @file    Lib_DEBUG/Lib_DEBUG_Example/readme.txt 
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

@par Example  Description 

This example demonstrates how to declare a dynamic peripherals pointers used for
Debug mode.  

To use Debug mode you have to add the FT32f0xx_ip_dbg.c file to your application.
This creates a pointer to the peripheral structure in SRAM. Debugging consequently
becomes easier and all register settings can be obtained by dumping a peripheral 
variable.

When the "USE_FULL_ASSERT" label is uncommented (in FT32f0xx_conf.h file),
the assert_param macro is expanded and run-time checking is enabled in the firmware
library code. The run-time checking allows checking that all the library functions
input value lies within the parameter allowed values.

The associated program simulates wrong parameter passed to library function and the
source of the error is printed on Hyperterminal (through USART).

@note
The Debug mode increases the code size and reduces the code performance. For this
reason, it is recommended to used it only when debugging the application and to
remove it from the final application code.



      
@par Hardware and Software environment

  - This example runs on FT32f0xx devices.
  
  - This example has been tested with FMD FT32F030XX-EVAL and
    FT32F072X8-EVAL i

  - FT32F030XX-EVAL Set-up
      - Connect a null-modem female/female RS232 cable between the DB9 connector CN7
        and PC serial port.
  - FT32F072X8-EVAL Set-up  
      - Connect a null-modem female/female RS232 cable between the DB9 connector CN10
        and PC serial port.

  - Hyperterminal configuration:
    - Word Length = 8 Bits
    - One Stop Bit
    - No parity
    - BaudRate = 115200 baud
    - flow control: None 


@par How to use it ? 

In order to make the program work, you must do the following :
 - Use MicroLib (请勾选 'Use MicroLib' ， 在MDK的OPTION选项中)
 - Copy all source files from this example folder to the template folder under
   Project\FT32f0xx_StdPeriph_Templates
 - Open your preferred toolchain
 - If the used device is FTM32F0xx
    - Add the following files to the project source list
       - Utilities/FTM32_EVAL/FT32F030XX_EVAL/FT32F030XX_eval.c 
       - FT32f0xx_ip_dbg.c
 - If the used device is FTM32F07x8
    - Add the following files to the project source list
       - Utilities\FTM32_EVAL\FT32F072X8_EVAL\FT32F072X8_eval.c 
       - FT32f0xx_ip_dbg.c
 - Rebuild all files and load your image into target memory
 - Run the example
        
 * <h3><center>&copy; COPYRIGHT FMD</center></h3>
 */
