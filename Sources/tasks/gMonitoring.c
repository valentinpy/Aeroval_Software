/*
 * Copyright (C) 2015 Valentin Py
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

#include "gMonitoring.h"

//-----------------------------------
// Monitoring initialisation
//-----------------------------------
void gMonitoring_Setup()
{
	//Configure UART, as it's used to transmit datas
	mRs232_Setup();

	//Get delay for low speed monitoring
	gMonitoring.aDelay = mDelay_GetDelay(kPit0, 25);

	//Clear string
	UInt8 i = 0;
	for (i=0; i<kMonitoringStringLength; i++)
	{
		gMonitoring.aDataString[i] = '\0';
	}
}

//-----------------------------------
// Run the monitoring
//-----------------------------------
void gMonitoring_Run()
{

	//loop
	if(mDelay_IsDelayDone(kPit0, gMonitoring.aDelay)==true)
	{

		mDelay_ReStart(kPit0, gMonitoring.aDelay, 50);

		if(mSwitches_Get(kMaskSwitch4))
		{
			//Generate string
			gMonitoring.aDataString[0] = 0x0D;
			gMonitoring.aDataString[1] = 0x0A;
			gMonitoring.aDataString[2] = (Int16)(gAttitudeSensors.aHeading_rad*1000) >> 8;		//Transmit float as milli-rad
			gMonitoring.aDataString[3] = (Int16)(gAttitudeSensors.aHeading_rad*1000) & 0xFF;
			gMonitoring.aDataString[4] = (Int16)(gAttitudeSensors.aPitch_rad*1000) >> 8;
			gMonitoring.aDataString[5] = (Int16)(gAttitudeSensors.aPitch_rad*1000) & 0xFF;
			gMonitoring.aDataString[6] = (Int16)(gAttitudeSensors.aRoll_rad*1000) >> 8;
			gMonitoring.aDataString[7] = (Int16)(gAttitudeSensors.aRoll_rad*1000) & 0xFF;
			gMonitoring.aDataString[8] =  (gReceiver.aChannels[0]>>8);
			gMonitoring.aDataString[9] =  (gReceiver.aChannels[0] & 0xFF);
			gMonitoring.aDataString[10] = (gReceiver.aChannels[1]>>8);
			gMonitoring.aDataString[11] = (gReceiver.aChannels[1] & 0xFF);
			gMonitoring.aDataString[12] = (gReceiver.aChannels[2]>>8);
			gMonitoring.aDataString[13] = (gReceiver.aChannels[2] & 0xFF);
			gMonitoring.aDataString[14] = (gReceiver.aChannels[3]>>8);
			gMonitoring.aDataString[15] = (gReceiver.aChannels[3] & 0xFF);
			gMonitoring.aDataString[16] = (gReceiver.aChannels[4]>>8);
			gMonitoring.aDataString[17] = (gReceiver.aChannels[4] & 0xFF);
			gMonitoring.aDataString[18] = (gReceiver.aChannels[5]>>8);
			gMonitoring.aDataString[19] = (gReceiver.aChannels[5] & 0xFF);
			gMonitoring.aDataString[20] = (gReceiver.aChannels[6]>>8);
			gMonitoring.aDataString[21] = (gReceiver.aChannels[6] & 0xFF);
			gMonitoring.aDataString[22] = (gReceiver.aChannels[7]>>8);
			gMonitoring.aDataString[23] = (gReceiver.aChannels[7] & 0xFF);
			gMonitoring.aDataString[24] = (gMotors.aMotorsValuesOut[0]>>8);
			gMonitoring.aDataString[25] = (gMotors.aMotorsValuesOut[0] & 0xFF);
			gMonitoring.aDataString[26] = (gMotors.aMotorsValuesOut[1]>>8);
			gMonitoring.aDataString[27] = (gMotors.aMotorsValuesOut[1] & 0xFF);
			gMonitoring.aDataString[28] = (gMotors.aMotorsValuesOut[2]>>8);
			gMonitoring.aDataString[29] = (gMotors.aMotorsValuesOut[2] & 0xFF);
			gMonitoring.aDataString[30] = (gMotors.aMotorsValuesOut[3]>>8);
			gMonitoring.aDataString[31] = (gMotors.aMotorsValuesOut[3] & 0xFF);
			gMonitoring.aDataString[32] = (gMotors.aMotorsValuesOut[4]>>8);
			gMonitoring.aDataString[33] = (gMotors.aMotorsValuesOut[4] & 0xFF);
			gMonitoring.aDataString[34] = (gMotors.aMotorsValuesOut[5]>>8);
			gMonitoring.aDataString[35] = (gMotors.aMotorsValuesOut[5] & 0xFF);
			gMonitoring.aDataString[36] = (gMotors.aMotorsValuesOut[6]>>8);
			gMonitoring.aDataString[37] = (gMotors.aMotorsValuesOut[6] & 0xFF);
			gMonitoring.aDataString[38] = (gMotors.aMotorsValuesOut[7]>>8);
			gMonitoring.aDataString[39] = (gMotors.aMotorsValuesOut[7] & 0xFF);
			gMonitoring.aDataString[40] = (gMotors.aServosValues[0] >>8);
			gMonitoring.aDataString[41] = (gMotors.aServosValues[0] & 0xFF);
			gMonitoring.aDataString[42] = (gMotors.aServosValues[1] >>8);
			gMonitoring.aDataString[43] = (gMotors.aServosValues[1] & 0xFF);
			gMonitoring.aDataString[44] = (gMotors.aServosValues[2] >>8);
			gMonitoring.aDataString[45] = (gMotors.aServosValues[2] & 0xFF);
			gMonitoring.aDataString[46] = (gMotors.aServosValues[3] >>8);
			gMonitoring.aDataString[47] = (gMotors.aServosValues[3] & 0xFF);
			gMonitoring.aDataString[48] = (gAltitudeSensors.aSonarValues[0]>>8);
			gMonitoring.aDataString[49] = (gAltitudeSensors.aSonarValues[0] & 0xFF);
			gMonitoring.aDataString[50] = (gAltitudeSensors.aSonarValues[1]>>8);
			gMonitoring.aDataString[51] = (gAltitudeSensors.aSonarValues[1] & 0xFF);
			gMonitoring.aDataString[52] = (gAltitudeSensors.aSonarValues[2]>>8);
			gMonitoring.aDataString[53] = (gAltitudeSensors.aSonarValues[2] & 0xFF);
			gMonitoring.aDataString[54] = (gAltitudeSensors.aSonarValues[3]>>8);
			gMonitoring.aDataString[55] = (gAltitudeSensors.aSonarValues[3] & 0xFF);
			gMonitoring.aDataString[56] = (gAltitudeSensors.aSonarValues[4]>>8);
			gMonitoring.aDataString[57] = (gAltitudeSensors.aSonarValues[4] & 0xFF);
			gMonitoring.aDataString[58] = (gAltitudeSensors.aSonarValues[5]>>8);
			gMonitoring.aDataString[59] = (gAltitudeSensors.aSonarValues[5] & 0xFF);
			gMonitoring.aDataString[60] = (gAltitudeSensors.aBaroValue >> 8);
			gMonitoring.aDataString[61] = (gAltitudeSensors.aBaroValue & 0xFF);
			gMonitoring.aDataString[62] = (gMiscSensors.aBatteryVoltage_mV >> 8);
			gMonitoring.aDataString[63] = (gMiscSensors.aBatteryVoltage_mV & 0xFF);
			gMonitoring.aDataString[64] = (gMiscSensors.aBatteryCurrent_A >> 8);
			gMonitoring.aDataString[65] = (gMiscSensors.aBatteryCurrent_A & 0xFF);
			gMonitoring.aDataString[66] = (gMiscSensors.aBatteryUsedCapacity_mAh >> 8);
			gMonitoring.aDataString[67] = (gMiscSensors.aBatteryUsedCapacity_mAh & 0xFF);
			gMonitoring.aDataString[68] = (gFlightCompute.aState);
			gMonitoring.aDataString[69] = (Int16)(gAttitudeSensors.aHeadingRate_rads*1000) >>8; //Transmit as milli-rad/s
			gMonitoring.aDataString[70] = (Int16)(gAttitudeSensors.aHeadingRate_rads*1000) & 0xFF;
			gMonitoring.aDataString[71] = (Int16)(gAttitudeSensors.aPitchRate_rads*1000) >>8;
			gMonitoring.aDataString[72] = (Int16)(gAttitudeSensors.aPitchRate_rads*1000) & 0xFF;
			gMonitoring.aDataString[73] = (Int16)(gAttitudeSensors.aRollRate_rads*1000) >>8;
			gMonitoring.aDataString[74] = (Int16)(gAttitudeSensors.aRollRate_rads*1000) & 0xFF;
			gMonitoring.aDataString[75] = (Int16)(gFlightCompute.aError*1000) >>8;
			gMonitoring.aDataString[76] = (Int16)(gFlightCompute.aError*1000) & 0xFF;
			gMonitoring.aDataString[77] = 0;
			gMonitoring.aDataString[78] = 0;
			gMonitoring.aDataString[79] = 0;


			//String is NULL terminated
			gMonitoring.aDataString[kMonitoringStringLength-1] = '\0';
			int i;
//			for (i=2; i<kMonitoringStringLength-1; i++) //2..79
//			{
//				//Avoid a \r\n
//				if((gMonitoring.aDataString[i] == 0x0D) && (gMonitoring.aDataString[i+1]==0x0A))
//				{
//					gMonitoring.aDataString[i] = 0;
//				}
//			}
			for(i=2; i<kMonitoringStringLength; i++)
			{
				if(gMonitoring.aDataString[i] == 0x0D)
				{
					gMonitoring.aDataString[i] = 0x0C;
				}
				if(gMonitoring.aDataString[i] == 0x0A)
				{
					gMonitoring.aDataString[i] = 0x09;
				}
			}


			//Transmit datas
			mRs232_WriteStringFixedSize(kUart3USB, gMonitoring.aDataString, kMonitoringStringLength);

			//Tests
			mRs232_WriteStringFixedSize(kUart4Aux, gMonitoring.aDataString, kMonitoringStringLength);
		}


		if(mSwitches_Get(kMaskSwitch1))
		{
			UInt8 aReceivedDatas[256];
			UInt8 i = 0;
			while(mRs232_ReadDataFromBuffer(kUart3USB, aReceivedDatas+i)==false)
			{
				i++;
			}

			mRs232_WriteString(kUart3USB, aReceivedDatas);
		}
	}
}
