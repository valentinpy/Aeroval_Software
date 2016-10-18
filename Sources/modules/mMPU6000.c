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

#include "mMPU6000.h"

//-------------------------------------------------------------------
// Basic setup of the sensor
//-------------------------------------------------------------------
void mMPU6000_Setup(gIMUSensorStruct *aValuesStruct)
{
	//Configure I2C bus
	iI2C_Config();
	iI2C_Enable(kI2c0);

	while(iI2C_GetData8(kI2c0, MPU6000_ADDR_W, MPU6000_WHOAMI) != 0x68); //Verification that the sensor is here

	//Reset registers
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_PWR_MGMT_1, 0x80);

	//Wait 10 ms after reset
	UInt16 aDelayMPU6000 = mDelay_GetDelay(kPit0, 10);
	while(mDelay_IsDelayDone(kPit0, aDelayMPU6000)==false);
	mDelay_DelayRelease(kPit0, aDelayMPU6000);

	//Choose gyro Z as time reference
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_PWR_MGMT_1, MPU6000_CLK_SEL_PLLGYROZ);

	//Sample rate, filter, range
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_SMPLRT_DIV, 0x00); // Sample rate = gyro rate /(1+SMPLRT_DIV)
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_CONFIG, MPU6000_BITS_DLPF_CFG_188HZ); //Digital Low Pass Filter activated (gyro: 188Hz, accel: 184Hz) => gyro rate = 1kHz => sample rate = 1kHz
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_GYRO_CONFIG, MPU6000_BITS_FS_1000DPS); //Gyro full range: +-1000dps
	iI2C_SetData8(kI2c0, MPU6000_ADDR_W, MPU6000_ACCEL_CONFIG, MPU6000_BITS_FS_4G); //Accel full range: +-4G


	//TODO Improv: config mag + add MagOutput =1
	//TODO Improv: config DMP

	//Init output struct
	aValuesStruct->MagOutput = 0;
	aValuesStruct->AccelOutput = 1;
	aValuesStruct->GyroOutput = 1;
	aValuesStruct->TempOutput = 1;
	aValuesStruct->PressureOutput = 0;
	aValuesStruct->EulerOutput = 0;
	aValuesStruct->QOutput = 0;
	aValuesStruct->AltitudeOutput = 0;
}

//-------------------------------------------------------------------
// Run sensor
//-------------------------------------------------------------------
void mMPU6000_Open(void)
{
}

//-------------------------------------------------------------------
// Stop sensor
//-------------------------------------------------------------------
void mMPU6000_Close(void)
{
}

//-------------------------------------------------------------------
// Read heading, pitch, roll and timestamp
// *aResultStruct: pointer over a structure of type EM7180_DataStruct in which the values are stored (QX, QY, QZ, QTime)
//-------------------------------------------------------------------
void mMPU6000_GetValues(gIMUSensorStruct *aValuesStruct)
{
	//Burst read
	UInt8 aValues[14];
	iI2C_GetData(kI2c0, MPU6000_ADDR_W, MPU6000_ACCEL_XOUT_H, 14, aValues);

	//Store data read in the right place in the array
	aValuesStruct->RawAccelX = 256 * aValues[0] + aValues[1];
	aValuesStruct->RawAccelY = 256 * aValues[2] + aValues[3];
	aValuesStruct->RawAccelZ = 256 * aValues[4] + aValues[5];
	aValuesStruct->RawGyroX = 256 * aValues[8] + aValues[9];
	aValuesStruct->RawGyroY = 256 * aValues[10] + aValues[11];
	aValuesStruct->RawGyroZ = 256 * aValues[12] + aValues[13];
	aValuesStruct->RawTemp = 256 * aValues[6] + aValues[7];
}
