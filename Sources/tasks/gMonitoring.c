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
	gMonitoring.aDelay5Hz = mDelay_GetDelay(kPit0, 200);

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
	// 5Hz loop
	if(mDelay_IsDelayDone(kPit0, gMonitoring.aDelay5Hz)==true)
	{
		mDelay_ReStart(kPit0, gMonitoring.aDelay5Hz, 200);

		//Generate string
		snprintf(gMonitoring.aDataString, kMonitoringStringLength, "%d, %d, %d\r\n", (Int16)(1000*gAttitudeSensors.aHeading), (Int16)(1000*gAttitudeSensors.aPitch), (Int16)(1000*gAttitudeSensors.aRoll));

		//String is NULL terminated
		gMonitoring.aDataString[kMonitoringStringLength-1] = '\0';

		//Transmit datas
		mRs232_WriteString(kUart3USB, gMonitoring.aDataString);
	}
}
