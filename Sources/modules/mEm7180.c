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

#include "mEM7180.h"

//-----------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Basic setup of the sensor
//-------------------------------------------------------------------
void mEM7180_Setup(gIMUSensorStruct *aValuesStruct)
{
	//Configure I2C bus
	iI2C_Config();
	iI2C_Enable(kI2c0);

	// Hardware reset of EM7180 module
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_ResetRequest, 0x01);

	// Wait for reset
	//TODO Should read interrupt instead of waiting
	UInt16 aDelay = mDelay_GetDelay(kPit0, 100);
	while(mDelay_IsDelayDone(kPit0, aDelay)==false);
	mDelay_DelayRelease(kPit0, aDelay);

	// Check EEPROM detected by SENTRAL
	while(FALSE == (0x01 & iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SentralStatus)));

	// Check Configuration file uploaded from EEPROM to SENTRAL
	while(FALSE == (0x01 & (iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SentralStatus) >> 1)));

	// Check if upload has successfull finished (CRC = OK)
	//TODO
	if(FALSE == (0x01 & (iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SentralStatus) >> 2)))
	{
		//mRs232_SendString("[Sentral / INFO]	Configuration file successfully uploaded!\r\n");
	}
	else
	{
		//mRs232_SendString("[Sentral / ERROR]	Failed to upload configuration file!\r\n");
	}

	// Check
	while(FALSE == (0x01 & (iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SentralStatus) >> 3)));

	// Set MagRate register to 30Hz
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_MagRate, 0x1E);
	// Set AccelRate register to 100Hz
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_AccelRate, 0x0A);
	// Set GyroRate register to 200Hz
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_GyroRate, 0x14);
	// Set QRateDivisor to 1 (Related to GyroRate -> 200Hz / QRateDivisor)
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_QRateDivisor, 0x01);
	//Set AlgorithmControl register (enable heading, pitch and roll)
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_AlgorithmControl, 0x06);
	// Set EnableEvent register (enable interrupt when: reset, error, new quaternion available)
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_EnableEvents, 0x07);

	aValuesStruct->MagOutput = 1;
	aValuesStruct->AccelOutput = 1;
	aValuesStruct->GyroOutput = 1;
	aValuesStruct->TempOutput = 0;
	aValuesStruct->PressureOutput = 0;
	aValuesStruct->EulerOutput = 1;
	aValuesStruct->QOutput = 0;
	aValuesStruct->AltitudeOutput = 0;
}

//-------------------------------------------------------------------
// Run sensor algorithm
//-------------------------------------------------------------------
void mEM7180_Open()
{
	// Enable run Sentral sensor algorithm
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_HostControl, 0x01);
}

//-------------------------------------------------------------------
// Stop sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Close()
{
	// Disable run Sentral sensor algorithm
	iI2C_SetData8(kI2c0, EM7180_ADDR_W, EM7180_HostControl, 0x00);
}

//-------------------------------------------------------------------
// Get status, for debug purpose
//-------------------------------------------------------------------
void mEM7180_readStatus()
{
	UInt8 aTmp=0;
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_HostControl); //0x1
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_EventStatus);	//0x3c
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SensorStatus); //0x0
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_SentralStatus); //0x3
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_AlgorithmStatus); // read mag calibration incomplete
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_FeatureFlags);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ActualMagRate); // read 30 => 30HZ
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ActualAccelRate); //read 12 => 120Hz :)
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ActualGyroRate); //read 20 => 200Hz :)
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ErrorRegister);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_AlgorithmControl); //read 6 => raw data enable: ok for gyro, HPR output => heading/pitch/roll instead of quaternions!
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ROMVersion1);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ROMVersion2);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_RAMVersion1);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_RAMVersion2);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_ProductID);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_RevisionID);
	aTmp = iI2C_GetData8(kI2c0, EM7180_ADDR_W, EM7180_RunStatus);
}

//-------------------------------------------------------------------
// Read all IMU values provided by sensor
// *aResultStruct: pointer over a structure of type EM7180_DataStruct in which the values are stored (QX, QY, QZ, QTime,...)
void mEm7180_GetValues(gIMUSensorStruct *aValuesStruct)
{
	Int32 kEuler_to_urad = 1000000;

	//Buffer to burst read into
	UInt8 aTmp[42];

	//Burst read
	iI2C_GetData(kI2c0, EM7180_ADDR_W, EM7180_QX, 42, aTmp);

	//Use an union to assemble 4 UInt8 in a Float32
	floatcharUnion aTmpUnionToFloat[3];
	aTmpUnionToFloat[0].s[0] = aTmp[0];
	aTmpUnionToFloat[0].s[1] = aTmp[1];
	aTmpUnionToFloat[0].s[2] = aTmp[2];
	aTmpUnionToFloat[0].s[3] = aTmp[3];

	aTmpUnionToFloat[1].s[0] = aTmp[4];
	aTmpUnionToFloat[1].s[1] = aTmp[5];
	aTmpUnionToFloat[1].s[2] = aTmp[6];
	aTmpUnionToFloat[1].s[3] = aTmp[7];

	aTmpUnionToFloat[2].s[0] = aTmp[8];
	aTmpUnionToFloat[2].s[1] = aTmp[9];
	aTmpUnionToFloat[2].s[2] = aTmp[0xA];
	aTmpUnionToFloat[2].s[3] = aTmp[0xB];

	//Assign the variables from buffer
	aValuesStruct->EulerDeltaTime_us  = (256*aTmp[0x11]+aTmp[0x10]);
	aValuesStruct->EulerHeading_urad =	(Int32)(kEuler_to_urad 	* aTmpUnionToFloat[0].f);
	aValuesStruct->EulerPitch_urad =	(Int32)(kEuler_to_urad 	* aTmpUnionToFloat[1].f);
	aValuesStruct->EulerRoll_urad =		(Int32)(kEuler_to_urad 	* aTmpUnionToFloat[2].f);

	aValuesStruct->RawMagX = 			(256*aTmp[0x13]+aTmp[0x12]);
	aValuesStruct->RawMagY = 			(256*aTmp[0x15]+aTmp[0x14]);
	aValuesStruct->RawMagZ = 			(256*aTmp[0x17]+aTmp[0x16]);
	aValuesStruct->RawMagDeltaTime = 	(256*aTmp[0x19]+aTmp[0x18]);

	aValuesStruct->RawAccelX = 			(256*aTmp[0x1B]+aTmp[0x1A]);
	aValuesStruct->RawAccelY = 			(256*aTmp[0x1D]+aTmp[0x1C]);
	aValuesStruct->RawAccelZ = 			(256*aTmp[0x1F]+aTmp[0x1E]);
	aValuesStruct->RawAccelDeltaTime = 	(256*aTmp[0x21]+aTmp[0x20]);


	aValuesStruct->RawGyroX = 			(256*aTmp[0x23]+aTmp[0x22]);
	aValuesStruct->RawGyroY = 			(256*aTmp[0x25]+aTmp[0x24]);
	aValuesStruct->RawGyroZ = 			(256*aTmp[0x27]+aTmp[0x26]);
	aValuesStruct->RawGyroDeltaTime = 	(256*aTmp[0x29]+aTmp[0x28]);
}
