#include "LTR553.h"
#include "my_io_port.h"

/**
 * @description: 
 * @param none
 * @return none
 */

#undef IIC_OK
#undef IIC_ERR

#define IIC_OK  0x00
#define IIC_ERR 0xFF

#define IIC_SCL  SCL_IO
#define IIC_SDA  SDA_IO
#define READ_SDA GPIO_ReadInputDataBit(SDA_Port, SDA_Pin)

/**
 * @description:   PA9 SCL   PA10 SDA
 * @param none
 * @return none
 */

void LTR553_IIC_Init(void)
{
    IIC_SCL(1);
    IIC_SDA(1);
}
/**
 * @description: 
 * @param {__IO SIZE_T} t
 * @return {*}
 */
static void delay_us(__IO SIZE_T t)
{
    t *= 3;
    while(t--)
        ;
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void set_SDA_IN(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void set_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB, GPIO_Pin_9);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void IIC_Start(void)
{
    set_SDA_OUT();
    IIC_SDA(1);
    IIC_SCL(1);
    delay_us(4);
    IIC_SDA(0);
    delay_us(4);
    IIC_SCL(0);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void IIC_Stop(void)
{
    set_SDA_OUT();
    IIC_SCL(0);
    IIC_SDA(0);
    delay_us(4);
    IIC_SCL(1);
    IIC_SDA(1);
    delay_us(4);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static u8 IIC_Wait_Ack(void)
{
    __IO SIZE_T ucErrTime = 0;
    set_SDA_IN();
    IIC_SDA(1);
    delay_us(2);
    IIC_SCL(1);
    delay_us(3);
    while(READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL(0);
    return 0;
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void IIC_Ack(void)
{
    IIC_SCL(0);
    set_SDA_OUT();
    IIC_SDA(0);
    delay_us(2);
    IIC_SCL(1);
    delay_us(2);
    IIC_SCL(0);
}
/**
 * @description: 
 * @param {*}
 * @return {*}
 */
static void IIC_NAck(void)
{
    IIC_SCL(0);
    set_SDA_OUT();
    IIC_SDA(1);
    delay_us(2);
    IIC_SCL(1);
    delay_us(2);
    IIC_SCL(0);
}
/**
 * @description: 
 * @param {u8} txd
 * @return {*}
 */
static void IIC_Send_Byte(u8 txd)
{
    SIZE_T i;
    set_SDA_OUT();
    IIC_SCL(0);
    for(i = 0; i < 8; i++)
    {
        if((txd & 0x80) >> 7)
        {
            IIC_SDA(1);
        }
        else
        {
            IIC_SDA(0);
        }
        txd <<= 1;
        delay_us(1);
        IIC_SCL(1);
        delay_us(9);
        IIC_SCL(0);
        delay_us(2);
    }
}
/**
 * @description: 
 * @param {u8} ack
 * @return {*}
 */
static u8 IIC_Read_Byte(u8 ack)
{
    SIZE_T i, receive = 0;
    set_SDA_IN();
    for(i = 0; i < 8; i++)
    {
        IIC_SCL(0);
        delay_us(12);
        IIC_SCL(1);
        receive <<= 1;
        if(READ_SDA)
        {
            receive++;
        }
        delay_us(1);
    }
    if(!ack)
    {
        IIC_NAck();
    }
    else
    {
        IIC_Ack();
    }
    return receive;
}
/*-----------------------------------------------------------------------------------------*/
#define SLAVE_ID 0x23
/*-----------------------------------------------------------------------------------------*/
u8 IIC_WriteReg(u8 slave_id, u8 reg, u8 val)
{
    IIC_Start();
    //
    IIC_Send_Byte(slave_id << 1);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    IIC_Send_Byte(val);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    IIC_Stop();
    delay_us(50);
    return IIC_OK;
}
/**
 * @description: 
 * @param {u8} reg
 * @param {u8} val
 * @return {*}
 */
u8 LTR553_write_reg(u8 reg, u8 val)
{
    return IIC_WriteReg(SLAVE_ID, reg, val);
}
/**
 * @description: 
 * @param {u8} slave_id
 * @param {u8} reg
 * @return {*}
 */
u8 IIC_ReadReg(u8 slave_id, u8 reg)
{
    SIZE_T tmp;
    //
    IIC_Start();
    //
    IIC_Send_Byte(slave_id << 1);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    IIC_Send_Byte(reg);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    IIC_Start();
    //
    IIC_Send_Byte((slave_id << 1) | 0x01);
    if(IIC_Wait_Ack())
    {
        return IIC_ERR;
    }
    //
    tmp = IIC_Read_Byte(0);
    //
    IIC_Stop();
    delay_us(50);
    //
    return tmp;
}
/**
 * @description: 
 * @param {u8} reg
 * @return {*}
 */
u8 LTR553_read_reg(u8 reg)
{
    return IIC_ReadReg(SLAVE_ID, reg);
}

/**
 * @description: 
 * @param {*}
 * @return {*}
 */
u32 ltr553_ps_value;
async LTR553_Update(thread_t* pt)
{
    Thread_BEGIN;
    {
        u8 ret;

        Thread_Sleep(10);

        ret = LTR553_write_reg(LTR553_REG_ALS_CONTR, 0x01); //0x80

        if(ret == IIC_OK)
        {
            ret = LTR553_write_reg(LTR553_REG_PS_LIGHT, 0xff); //0x82
        }

        if(ret == IIC_OK)
        {
            ret = LTR553_write_reg(LTR553_REG_PS_N_PULSES, 0x08); //0x83  0x06
        }

        if(ret == IIC_OK)
        {
            ret = LTR553_write_reg(LTR553_REG_PS_CONTR, 0x03); //0x81
        }

        if(ret > IIC_OK)
        {
            Thread_Interrupt();
        }

        while(1)
        {
            u8 ret1, ret2;
            Thread_Sleep(50);
            ret1 = LTR553_read_reg(LTR553_REG_PS_DATA_1);
            ret2 = LTR553_read_reg(LTR553_REG_PS_DATA_0);
            ltr553_ps_value = ((ret1 << 8) | (ret2 & 0xff));
        }
    }
    Thread_END;
}
