/*
 * Copyright (C) 2015-2016 Valentin Py
 *
 * This file is part of Aeroval.
 *
 * Aeroval is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Aeroval is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SOURCES_MMPU6000_H_
#define SOURCES_MMPU6000_H_

#include "../misc/def.h"
#include "../interfaces/iI2C.h"
#include "../misc/def.h"
#include "mDelay.h"


//MPU 6000 I2C address
#define MPU6000_ADDR_W 0xD2
#define MPU6000_ADDR_R 0xD3

// MPU 6000 registers
#define MPU6000_SMPLRT_DIV		0x19
#define MPU6000_CONFIG			0x1A
#define MPU6000_GYRO_CONFIG		0x1B
#define MPU6000_ACCEL_CONFIG	0x1C
#define MPU6000_FIFO_EN			0x23
#define MPU6000_INT_PIN_CFG		0x37
#define MPU6000_INT_ENABLE		0x38
#define MPU6000_INT_STATUS		0x3A
#define MPU6000_ACCEL_XOUT_H	0x3B
#define MPU6000_ACCEL_XOUT_L	0x3C
#define MPU6000_ACCEL_YOUT_H	0x3D
#define MPU6000_ACCEL_YOUT_L	0x3E
#define MPU6000_ACCEL_ZOUT_H	0x3F
#define MPU6000_ACCEL_ZOUT_L	0x40
#define MPU6000_TEMP_OUT_H		0x41
#define MPU6000_TEMP_OUT_L		0x42
#define MPU6000_GYRO_XOUT_H		0x43
#define MPU6000_GYRO_XOUT_L		0x44
#define MPU6000_GYRO_YOUT_H		0x45
#define MPU6000_GYRO_YOUT_L		0x46
#define MPU6000_GYRO_ZOUT_H		0x47
#define MPU6000_GYRO_ZOUT_L		0x48
#define MPU6000_USER_CTRL		0x6A
#define MPU6000_PWR_MGMT_1		0x6B
#define MPU6000_PWR_MGMT_2		0x6C
#define MPU6000_FIFO_COUNTH		0x72
#define MPU6000_FIFO_COUNTL		0x73
#define MPU6000_FIFO_R_W		0x74
#define MPU6000_WHOAMI			0x75



// Configuration bits
#define MPU6000_BIT_SLEEP					0x40
#define MPU6000_BIT_H_RESET					0x80
#define MPU6000_BITS_CLKSEL					0x07
#define MPU6000_CLK_SEL_PLLGYROX			0x01
#define MPU6000_CLK_SEL_PLLGYROZ			0x03
#define MPU6000_EXT_SYNC_GYROX				0x02
#define MPU6000_BITS_FS_250DPS          	0x00
#define MPU6000_BITS_FS_500DPS          	0x08
#define MPU6000_BITS_FS_1000DPS         	0x10
#define MPU6000_BITS_FS_2000DPS         	0x18
#define MPU6000_BITS_FS_4G					0x08

#define MPU6000_BITS_FS_MASK            	0x18
#define MPU6000_BITS_DLPF_CFG_256HZ_NOLPF2  0x00
#define MPU6000_BITS_DLPF_CFG_188HZ         0x01
#define MPU6000_BITS_DLPF_CFG_98HZ          0x02
#define MPU6000_BITS_DLPF_CFG_42HZ          0x03
#define MPU6000_BITS_DLPF_CFG_20HZ          0x04
#define MPU6000_BITS_DLPF_CFG_10HZ          0x05
#define MPU6000_BITS_DLPF_CFG_5HZ           0x06
#define MPU6000_BITS_DLPF_CFG_2100HZ_NOLPF  0x07
#define MPU6000_BITS_DLPF_CFG_MASK          0x07
#define MPU6000_BIT_INT_ANYRD_2CLEAR    	0x10
#define MPU6000_BIT_RAW_RDY_EN				0x01
#define MPU6000_BIT_I2C_IF_DIS          	0x10
#define MPU6000_BIT_INT_STATUS_DATA			0x01


//-------------------------------------------------------------------
// Basic setup of the sensor
//-------------------------------------------------------------------
void mMPU6000_Setup(gIMUSensorStruct *aValuesStruct);

//-------------------------------------------------------------------
// Run sensor
//-------------------------------------------------------------------
void mMPU6000_Open(void);

//-------------------------------------------------------------------
// Stop sensor
//-------------------------------------------------------------------
void mMPU6000_Close(void);

//-------------------------------------------------------------------
// Read heading, pitch, roll and timestamp
// *aResultStruct: pointer over a structure of type EM7180_DataStruct in which the values are stored (QX, QY, QZ, QTime)
//-------------------------------------------------------------------
void mMPU6000_GetValues(gIMUSensorStruct *aValuesStruct);


#endif /* SOURCES_MMPU6000_H_ */
