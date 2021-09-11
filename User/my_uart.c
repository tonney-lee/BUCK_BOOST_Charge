#include "my_uart.h"
#include "my_io_port.h"

sys_t sys = {0};

void UartInit(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    /* USART1 Pins configuration ************************************************/
    /* Connect pin to Periph */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_0);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_0);

    /* Configure pins as AF pushpull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    NVIC_InitTypeDef NVIC_InitStructure;
    /* USART1 IRQ Channel configuration */
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = 0x01;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_InitTypeDef USART_InitStructure;
    USART_InitStructure.USART_BaudRate = 9600;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART1, &USART_InitStructure);

    /* Enable 2xUSARTs Receive interrupts */
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    /* Enable the 2xUSARTs */
    USART_Cmd(USART1, ENABLE);
}
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

typedef struct
{
    u8* txAddr;
    u8 txCount;

} TS_Uart;

TS_Uart s_Uart;

#define BUFFER_SIZE 20

__IO SIZE_T uart1_rcv_buf_index = 0;
__IO SIZE_T Uart1ReceivedFlag;
u8 uart1_rcv_buf[BUFFER_SIZE];
u8 ble_rcv_buf[BUFFER_SIZE];
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void ble_rcv_callback()
{
}
/**
 * @description: 
 * @param {u8*} txBuf
 * @param {SIZE_T} tx_num
 * @return {*}
 */
void UartSend(u8* txBuf, SIZE_T tx_num)
{
    if(tx_num < 1U)
    {
        return;
    }

    s_Uart.txAddr = (byte*)txBuf;
    s_Uart.txCount = tx_num;
    USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
void USART1_IRQHandler(void)
{
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        // /* Read one byte from the receive data register */
        Uart1ReceivedFlag = TRUE;
        uart1_rcv_buf[uart1_rcv_buf_index++] = (USART_ReceiveData(USART1) & 0x7F);
        uart1_rcv_buf_index %= BUFFER_SIZE;
    }

    if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
    {
        if(s_Uart.txCount > 0U)
        {
            USART_SendData(USART1, *(s_Uart.txAddr));
            s_Uart.txAddr++;
            s_Uart.txCount--;
        }
        else
        {
            USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
        }
    }
}
/**
 * @description: 
 * @param {thread_t*} pt
 * @return {*}
 */
async uart1_Rcv_Update(thread_t* pt)
{
    Thread_BEGIN;
    {
        for(;;)
        {
            Thread_Wait_Until(Uart1ReceivedFlag);
        rcvRepeat:
            ClrSem(Uart1ReceivedFlag);
            Thread_Sleep_Until(25, Uart1ReceivedFlag);
            if(Uart1ReceivedFlag)
            {
                goto rcvRepeat;
            }
            memcpy(ble_rcv_buf, uart1_rcv_buf, uart1_rcv_buf_index);
            memset(&ble_rcv_buf[uart1_rcv_buf_index], 0, BUFFER_SIZE - uart1_rcv_buf_index);
            uart1_rcv_buf_index = 0;
            ble_rcv_callback();
        }
    }
    Thread_END
}

/**
 * @description: 
 * @param {thread_t*} pt
 * @return {*}
 */
async uart_send_test(thread_t* pt)
{
    Thread_BEGIN;
    {
        while(1)
        {
            static const u8 test[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            UartSend((void*)test, sizeof(test));
            Thread_Sleep(100);
        }
    }
    Thread_END;
}
