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
#include "../userDefined.h"

#include "gFlightCompute.h"
#include "misc/string.h"
#include "misc/maths.h"

static void gMonitoring_sendMonitoring();
static void gMonitoring_receiveMonitoring();
static void gMonitoring_terminal_print(char *aReceived, UInt8 aReceivedLength);
static void gMonitoring_terminal_set(char *aReceived, UInt8 aReceivedLength);
static bool gMonitoring_getNumber(float* number, char * aReceived, UInt8 aReceivedLength);


//-----------------------------------
// Monitoring initialisation
//-----------------------------------
void gMonitoring_Setup()
{
	//Configure UART, as it's used to transmit datas
	mRs232_Setup();

	//Get delay for low speed monitoring
	gMonitoring.aDelay = mDelay_GetDelay(kPit0, 25);

	//Clear string (RX)
	UInt8 i = 0;
	for (i=0; i<kMonitoringStringLength; i++)
	{
		gMonitoring.aDataString[i] = '\0';
	}

	//Clear string (TX)
	for (i=0; i<50; i++)
	{
		gMonitoring.aReceived[i] = '\0';
	}
	gMonitoring.aReceivedIdx=0;


}

//-----------------------------------
// Run the monitoring
//-----------------------------------
void gMonitoring_Run()
{
	if(mDelay_IsDelayDone(kPit0, gMonitoring.aDelay)==true)
	{
		//Limit frequency of calling, because monitoring consumes time!
		mDelay_ReStart(kPit0, gMonitoring.aDelay, 50);

		//Enable monitoring with switch 4
		if(mSwitches_Get(kMaskSwitch4))
		{
			gMonitoring_sendMonitoring();
			gMonitoring_receiveMonitoring();
		}
	}
}



static void gMonitoring_sendMonitoring()
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
	gMonitoring.aDataString[8] =  (gReceiver.aChannels[kReceiverThrottle]>>8);
	gMonitoring.aDataString[9] =  (gReceiver.aChannels[kReceiverThrottle] & 0xFF);
	gMonitoring.aDataString[10] = (gReceiver.aChannels[kReceiverYaw]>>8);
	gMonitoring.aDataString[11] = (gReceiver.aChannels[kReceiverYaw] & 0xFF);
	gMonitoring.aDataString[12] = (gReceiver.aChannels[kReceiverPitch]>>8);
	gMonitoring.aDataString[13] = (gReceiver.aChannels[kReceiverPitch] & 0xFF);
	gMonitoring.aDataString[14] = (gReceiver.aChannels[kReceiverRoll]>>8);
	gMonitoring.aDataString[15] = (gReceiver.aChannels[kReceiverRoll] & 0xFF);
	gMonitoring.aDataString[16] = (gReceiver.aChannels[kReceiverGear]>>8);
	gMonitoring.aDataString[17] = (gReceiver.aChannels[kReceiverGear] & 0xFF);
	gMonitoring.aDataString[18] = (gReceiver.aChannels[kReceiverAux1]>>8);
	gMonitoring.aDataString[19] = (gReceiver.aChannels[kReceiverAux1] & 0xFF);
	gMonitoring.aDataString[20] = (gReceiver.aChannels[kReceiverAux2]>>8);
	gMonitoring.aDataString[21] = (gReceiver.aChannels[kReceiverAux2] & 0xFF);
	gMonitoring.aDataString[22] = (gReceiver.aChannels[kReceiverAux3]>>8);
	gMonitoring.aDataString[23] = (gReceiver.aChannels[kReceiverAux3] & 0xFF);
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
	UInt8 i;

	//Avoid a \r\n
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

	//Transmit datas on USB with switch 5
	if(mSwitches_Get(kMaskSwitch5))
	{
		mRs232_WriteStringFixedSize(kUart3USB, gMonitoring.aDataString, kMonitoringStringLength);

	}

	//Transmit datas on BT with switch 6
	if(mSwitches_Get(kMaskSwitch6))
	{
		mRs232_WriteStringFixedSize(kUart4Aux, gMonitoring.aDataString, kMonitoringStringLength);

	}
}



static void gMonitoring_receiveMonitoring()
{
	//Receive data from BT with switch 7 if monitoring is activated with switch 4
	if(mSwitches_Get(kMaskSwitch7))
	{
		//Read and store data
		while((mRs232_ReadDataFromBuffer(kUart4Aux, &gMonitoring.aReceived[gMonitoring.aReceivedIdx])==false) && (gMonitoring.aReceived[gMonitoring.aReceivedIdx]!='\n')) //Read from UART 4 while data available and not EOL
		{
			gMonitoring.aReceivedIdx++;

			//Avoid buffer overfow
			if(gMonitoring.aReceivedIdx > 49)
			{
				gMonitoring.aReceivedIdx=49;
			}
		}

		if(gMonitoring.aReceived[gMonitoring.aReceivedIdx]=='\n')
		{

			//if a-z => print infos. if A-Z => set data
			if( (gMonitoring.aReceived[0]>='a') && (gMonitoring.aReceived[0]<='z') )
			{
				gMonitoring_terminal_print(gMonitoring.aReceived, gMonitoring.aReceivedIdx-1); //length - 1, because we don't care about the \r

			}
			else if( (gMonitoring.aReceived[0]>='A') && (gMonitoring.aReceived[0]<='Z') )
			{
				gMonitoring_terminal_set(gMonitoring.aReceived, gMonitoring.aReceivedIdx-1); //length - 1, because we don't care about the \r
			}

			//Print shell
			mRs232_WriteString(kUart4Aux, "> ");

			//Clear the buffer as the command is finished
			UInt8 i;
			for (i=0; i<=gMonitoring.aReceivedIdx; i++)
			{
				gMonitoring.aReceived[i] = '\0';
			}
			gMonitoring.aReceivedIdx=0;
		}
	}
}

static void gMonitoring_terminal_print(char *aReceived, UInt8 aReceivedLength)
{
	switch(aReceived[0])
	{
	case 'h': //help
		mRs232_WriteString(kUart4Aux,
				"v: print version\r\n"
				"i: print informations\r\n"
				"h: print this help\r\n"
		);
		break;

	case 'i': //get infos
		mRs232_WriteString(kUart4Aux, "Aeroval: Valentin Py, https://github.com/valentinpy/Aeroval_Software\0");
		break;

	case 'v': //get version
		mRs232_WriteString(kUart4Aux, "Aeroval " AEROVAL_VERSION ", compilation date: "__DATE__ " at " __TIME__ "\0");

		break;

	case 'p':
		if(aReceivedLength >=4) //Assert that we have at least 4 chars
		{
			float toReturn;
			char toPrint[9];

			if 		((aReceived[1] == 'a') && (aReceived[2] == 'r') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDAngle[kRoll].aKp;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'r') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDAngle[kRoll].aKi;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'r') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDAngle[kRoll].aKd;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'p') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDAngle[kPitch].aKp;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'p') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDAngle[kPitch].aKi;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'p') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDAngle[kPitch].aKd;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'y') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDAngle[kYaw].aKp;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'y') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDAngle[kYaw].aKi;
			else if ((aReceived[1] == 'a') && (aReceived[2] == 'y') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDAngle[kYaw].aKd;

			else if ((aReceived[1] == 'r') && (aReceived[2] == 'r') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDRate[kRoll].aKp;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'r') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDRate[kRoll].aKi;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'r') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDRate[kRoll].aKd;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'p') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDRate[kPitch].aKp;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'p') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDRate[kPitch].aKi;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'p') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDRate[kPitch].aKd;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'y') && (aReceived[3] == 'p')) toReturn = gFlightCompute.aPIDRate[kYaw].aKp;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'y') && (aReceived[3] == 'i')) toReturn = gFlightCompute.aPIDRate[kYaw].aKi;
			else if ((aReceived[1] == 'r') && (aReceived[2] == 'y') && (aReceived[3] == 'd')) toReturn = gFlightCompute.aPIDRate[kYaw].aKd;
			else
			{
				toReturn = 0;
			}

			//Print the value with precision of 3 digits
			toReturn *= 1000;
			string_Int32toCharArrayDec( (Int32)toReturn, toPrint );
			toPrint[11] = toPrint[10];
			toPrint[10] = toPrint[9];
			toPrint[9] = toPrint[8];
			toPrint[8] = '.';

			mRs232_WriteString(kUart4Aux, toPrint);

		}
		break;

	default:
		mRs232_WriteString(kUart4Aux, "Please enter a valid command or 'h' for help.");
		break;
	}

	mRs232_WriteString(kUart4Aux, "\r\n");
}


static void gMonitoring_terminal_set(char *aReceived, UInt8 aReceivedLength)
{
	switch(aReceived[0])
	{
	case 'P':
		if(aReceivedLength >=4) //Assert that we have at least 4 chars
		{
			float readNumber=0;

			if(gMonitoring_getNumber(&readNumber, aReceived+5, aReceivedLength-5)==true) //Get the number a the position >5 (after 4chars+space)
			{
				if 		((aReceived[1] == 'A') && (aReceived[2] == 'R') && (aReceived[3] == 'P')) gFlightCompute.aPIDAngle[kRoll].aKp	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'R') && (aReceived[3] == 'I')) gFlightCompute.aPIDAngle[kRoll].aKi	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'R') && (aReceived[3] == 'D')) gFlightCompute.aPIDAngle[kRoll].aKd	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'P') && (aReceived[3] == 'P')) gFlightCompute.aPIDAngle[kPitch].aKp	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'P') && (aReceived[3] == 'I')) gFlightCompute.aPIDAngle[kPitch].aKi	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'P') && (aReceived[3] == 'D')) gFlightCompute.aPIDAngle[kPitch].aKd	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'Y') && (aReceived[3] == 'P')) gFlightCompute.aPIDAngle[kYaw].aKp	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'Y') && (aReceived[3] == 'I')) gFlightCompute.aPIDAngle[kYaw].aKi	= readNumber;
				else if ((aReceived[1] == 'A') && (aReceived[2] == 'Y') && (aReceived[3] == 'D')) gFlightCompute.aPIDAngle[kYaw].aKd	= readNumber;

				else if ((aReceived[1] == 'R') && (aReceived[2] == 'R') && (aReceived[3] == 'P')) gFlightCompute.aPIDRate[kRoll].aKp	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'R') && (aReceived[3] == 'I')) gFlightCompute.aPIDRate[kRoll].aKi	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'R') && (aReceived[3] == 'D')) gFlightCompute.aPIDRate[kRoll].aKd	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'P') && (aReceived[3] == 'P')) gFlightCompute.aPIDRate[kPitch].aKp	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'P') && (aReceived[3] == 'I')) gFlightCompute.aPIDRate[kPitch].aKi	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'P') && (aReceived[3] == 'D')) gFlightCompute.aPIDRate[kPitch].aKd	= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'Y') && (aReceived[3] == 'P')) gFlightCompute.aPIDRate[kYaw].aKp		= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'Y') && (aReceived[3] == 'I')) gFlightCompute.aPIDRate[kYaw].aKi		= readNumber;
				else if ((aReceived[1] == 'R') && (aReceived[2] == 'Y') && (aReceived[3] == 'D')) gFlightCompute.aPIDRate[kYaw].aKd		= readNumber;
				else
				{
					mRs232_WriteString(kUart4Aux, "Please enter a correct location\r\n");
				}
			}
			else
			{
				mRs232_WriteString(kUart4Aux, "Please enter a valid number\r\n");
			}
		}
	}
}



static bool gMonitoring_getNumber(float* number, char * aReceived, UInt8 aReceivedLength)
{

	//*number = sCharTab[0]*10^index +  sCharTab[1]*10^(index-1) +... + sCharTab[index]*10^(index-index)
	UInt8 i = 0;
	UInt8 pointPosition = 0;

	*number=0;

	//Convert numbers to ASCII
	for(i=0; i< aReceivedLength; i++)
	{
		if ( (aReceived[i] >= '0') && (aReceived[i] <= '9') )
		{
			aReceived[i] -='0';
		}
		else
		{
			//Avoid non numerical numbers
			return false;
		}
	}

	//For all received characters
	for(i=0; i<aReceivedLength; i++)
	{
		//*number = sCharTab[0]*10^index +  sCharTab[1]*10^(index-1) +... + sCharTab[index]*10^(index-index)
		*number+= (float)(aReceived[i] * maths_UInt32Power(10, aReceivedLength-i-1));
	}

	*number/=1000.0;

	return true;


}

