/*
 * @Author: wangdong
 * @Date: 2021-06-16 17:09:40
 * @LastEditTime: 2021-09-12 16:16:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MM32F013x_Lib_Samples_V1.03\X6\USER\my_sc8905.h
 */

#ifndef __SC8905_H__
#define __SC8905_H__

#include "thread.h"
/*-----------------------------------------------------------*/
//#define LTR553_ADDR                  0x46
#define LTR553_ADDR 0x23

#define LTR553_REG_ALS_CONTR         0x80
#define LTR553_REG_PS_CONTR          0x81
#define LTR553_REG_PS_LIGHT          0x82
#define LTR553_REG_PS_N_PULSES       0x83
#define LTR553_REG_PS_MEAS_RATE      0x84
#define LTR553_REG_ALS_MEAS_RATE     0x85
#define LTR553_REG_PART_ID           0x86
#define LTR553_REG_MANUFAC_ID        0x87
#define LTR553_REG_ALS_DATA_CH1_0    0x88
#define LTR553_REG_ALS_DATA_CH1_1    0x89
#define LTR553_REG_ALS_DATA_CH0_0    0x8a
#define LTR553_REG_ALS_DATA_CH0_1    0x8b
#define LTR553_REG_ALS_PS_STATUS     0x8c
#define LTR553_REG_PS_DATA_0         0x8d
#define LTR553_REG_PS_DATA_1         0x8e
#define LTR553_REG_INTERRUPT         0x8f
#define LTR553_REG_PS_THRES_UP_0     0x90
#define LTR553_REG_PS_THRES_UP_1     0x91
#define LTR553_REG_PS_THRES_LOW_0    0x92
#define LTR553_REG_PS_THRES_LOW_1    0x93
#define LTR553_REG_PS_OFFSET_1       0x94
#define LTR553_REG_PS_OFFSET_0       0x95
#define LTR553_REG_ALS_THRES_UP_0    0x97
#define LTR553_REG_ALS_THRES_UP_1    0x98
#define LTR553_REG_ALS_THRES_LOW_0   0x99
#define LTR553_REG_ALS_THRES_LOW_1   0x9a
#define LTR553_REG_INTERRUPT_PERSIST 0x9e
/*-----------------------------------------------------------*/
void LTR553_IIC_Init(void);
u8 LTR553_write_reg(u8 reg, u8 val);
u8 LTR553_read_reg(u8 reg);
async LTR553_Update(thread_t* pt);
/*-----------------------------------------------------------*/
#endif
