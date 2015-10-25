/*
 * gMonitoring.c
 *
 *  Created on: 11 août 2015
 *      Author: valentinpy
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

		mDelay_ReStart(kPit0, gMonitoring.aDelay, 25);

		if(mSwitches_Get(kMaskSwitch0))
		{
			//Generate string
			gMonitoring.aDataString[0] = 'L';
			gMonitoring.aDataString[1] = ':';

			gMonitoring.aDataString[2] = (gAttitudeSensors.aHeading_mrad >> 8);
			gMonitoring.aDataString[3] = (gAttitudeSensors.aHeading_mrad & 0xFF);
			gMonitoring.aDataString[4] = (gAttitudeSensors.aPitch_mrad >> 8);
			gMonitoring.aDataString[5] = (gAttitudeSensors.aPitch_mrad & 0xFF);
			gMonitoring.aDataString[6] = (gAttitudeSensors.aRoll_mrad >> 8);
			gMonitoring.aDataString[7] = (gAttitudeSensors.aRoll_mrad & 0xFF);
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
			gMonitoring.aDataString[24] = (gMotors.aMotorsValues[0]>>8);
			gMonitoring.aDataString[25] = (gMotors.aMotorsValues[0] & 0xFF);
			gMonitoring.aDataString[26] = (gMotors.aMotorsValues[1]>>8);
			gMonitoring.aDataString[27] = (gMotors.aMotorsValues[1] & 0xFF);
			gMonitoring.aDataString[28] = (gMotors.aMotorsValues[2]>>8);
			gMonitoring.aDataString[29] = (gMotors.aMotorsValues[2] & 0xFF);
			gMonitoring.aDataString[30] = (gMotors.aMotorsValues[3]>>8);
			gMonitoring.aDataString[31] = (gMotors.aMotorsValues[3] & 0xFF);
			gMonitoring.aDataString[32] = (gMotors.aMotorsValues[4]>>8);
			gMonitoring.aDataString[33] = (gMotors.aMotorsValues[4] & 0xFF);
			gMonitoring.aDataString[34] = (gMotors.aMotorsValues[5]>>8);
			gMonitoring.aDataString[35] = (gMotors.aMotorsValues[5] & 0xFF);
			gMonitoring.aDataString[36] = (gMotors.aMotorsValues[6]>>8);
			gMonitoring.aDataString[37] = (gMotors.aMotorsValues[6] & 0xFF);
			gMonitoring.aDataString[38] = (gMotors.aMotorsValues[7]>>8);
			gMonitoring.aDataString[39] = (gMotors.aMotorsValues[7] & 0xFF);
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
			gMonitoring.aDataString[69] = 0;

			//String is NULL terminated
			gMonitoring.aDataString[kMonitoringStringLength-1] = '\0';
			int i;
			for (i=2; i<kMonitoringStringLength-1; i++) //2..68
			{
				//Avoid a "L:"
				if((gMonitoring.aDataString[i] == 'L') && (gMonitoring.aDataString[i+1]==':'))
				{
					gMonitoring.aDataString[i] = 255;
				}

				//Avoid a \r\n
				if((gMonitoring.aDataString[i] == '\r') && (gMonitoring.aDataString[i+1]=='\n'))
				{
					gMonitoring.aDataString[i] = 255;
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
