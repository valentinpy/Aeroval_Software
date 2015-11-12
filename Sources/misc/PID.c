/*
 * PID.c
 *
 *  Created on: 11 nov. 2015
 *      Author: valentinpy
 */
#include "PID.h"




void misc_ResetPID(PIDdata* aPID)
{
	UInt8 i;
	for(i=0; i<3; i++)
	{
		aPID[i].aIntegral=0;
		aPID[i].aPreviousError=0;
		aPID[i].aPreviousTime = sTicker100Us[0];
	}
}

void misc_PID(float* aOutput, PIDdata* aPIDstruct, float aTarget, float aMeasured, UInt16 aTime)
{
	float aDeltaTime;
	float aError, aProportional, aDerivative;

	aDeltaTime = (float)(aTime - aPIDstruct->aPreviousTime);

	//Constrain time if abnormal
	if (aDeltaTime <1.0)
	{
		aDeltaTime = 1.0;
	}
	else if (aDeltaTime >1000.0)
	{
		aDeltaTime = 1000.0; //100ms ?
	}

	//Constrain integral
	if(aPIDstruct->aIntegral > aPIDstruct->aWindupGuard)
	{
		aPIDstruct->aIntegral = aPIDstruct->aWindupGuard;
	}
	else if(aPIDstruct->aIntegral < -aPIDstruct->aWindupGuard)
	{
		aPIDstruct->aIntegral = -aPIDstruct->aWindupGuard;
	}

	//Compute error
	aError = (aTarget - aMeasured);
	gFlightCompute.aError = aTarget; //DEBUG

	//Compute separate terms
	aProportional = (aError * aPIDstruct->aKp);
	aPIDstruct->aIntegral += (aError * aPIDstruct->aKi * aDeltaTime);
	aDerivative = ((aError-(aPIDstruct->aPreviousError)) * aPIDstruct->aKd)/aDeltaTime;

	//Compute output
	*aOutput = aProportional + (aPIDstruct->aIntegral) + aDerivative;

	//Sore previous parameters
	aPIDstruct->aPreviousTime = aTime;
	aPIDstruct->aPreviousError= aError;
}
