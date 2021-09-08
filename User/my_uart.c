#include "my_uart.h"
#include "my_io_port.h"

sys_t sys = {0};

/*---------------------------------------------------------------------------*/
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */

#define LOW_LEVEL  0
#define HIGH_LEVEL 1

#define WAVE_DLY (49) // 19200bps 52us

static void SendByte(Byte dat)
{
    __IO u8 i, j;
    DI();

    IO_TX(0);

    for(i = 0; i < WAVE_DLY; i++)
    {
        NOP();
    }

    for(i = 0; i < 8; i++, dat >>= 1)
    {
        if(ValBit(dat, 0))
        {

            IO_TX(1);
            NOP();
        }
        else
        {

            IO_TX(0);
            NOP();
            NOP();
            NOP();
            NOP();
        }

        for(j = 0; j < WAVE_DLY; j++)
        {
            NOP();
        }
    }

    IO_TX(1);

    for(i = 0; i < WAVE_DLY; i++)
    {
        NOP();
    }
    EI();
}
/*-----------------------------------------------------------*/
/** \brief   SerialPort update used for Debug
 *
 * \param
 * \param
 * \return
 *
 */
//115200 baudrate
#define DEBUG_VALUES sys

void deBug_info(void)
{
    static u8 status = 0;
    static dly_t dly;
    static u8 i;

    if(status)
    {
        if(i < sizeof(sys))
        {
            Byte* p = (Byte*)&sys;
            SendByte(*(p + i));
            //SendByte(0x55);
            i++;
        }
        else
        {
            delay_set(&dly);
            status = 0;
            i = 0;
            sys.inc++;
        }
    }
    else
    {
        if(delay_interval(&dly, 100))
        {
            status++;
        }
    }
}
