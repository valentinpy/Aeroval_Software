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

#include "PID.h"




void pid_ResetPID(PIDdata* aPID)
{
	UInt8 i;
	for(i=0; i<3; i++)
	{
		aPID[i].aIntegral=0;
		aPID[i].aPreviousError=0;
		aPID[i].aPreviousTime = sTicker100Us[0];
	}
}

void pid_PID(float* aOutput, PIDdata* aPIDstruct, float aTarget, float aMeasured, UInt16 aTime)
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
