///*
// * mEm7180.c
// *
// *  Created on: 7 août 2015
// *      Author: valentinpy
// */
//

#include "mEm7180.h"

#define PI 3.141592653

void mEm7180_Setup()
{
	iI2C_Config();
	iI2C_Enable(kI2c0);

	// Reset hardware du module
	mEm7180_SetData8(ResetReq, 0x01);
	// Wait pour le reset
	UInt16 aDelay = mDelay_GetDelay(kPit0, 100);
	while(mDelay_IsDelayDone(kPit0, aDelay)==false);
	mDelay_DelayRelease(kPit0, aDelay);

	// Check EEPROM detected by SENTRAL
	while(FALSE == (0x01 & mEm7180_GetData8(SentralStatus)));
	// Check Configuration file uploaded from EEPROM to SENTRAL
	while(FALSE == (0x01 & (mEm7180_GetData8(SentralStatus) >> 1)));
	// Check if upload has successfull finished (CRC = OK)
	if(FALSE == (0x01 & (mEm7180_GetData8(SentralStatus) >> 2)))
	{
		//mRs232_SendString("[Sentral / INFO]	Configuration file successfully uploaded!\r\n");
	}
	else
	{
		//mRs232_SendString("[Sentral / ERROR]	Failed to upload configuration file!\r\n");
	}

	// Set MagRate register to 100Hz
	mEm7180_SetData8(MagRate, 0x64);
	// Set AccelRate register to 100Hz
	mEm7180_SetData8(AccelRate, 0x0A);
	// Set GyroRate register to 150Hz
	mEm7180_SetData8(GyroRate, 0x0F);
	// Set QRateDivisor to 1 (Related to GyroRate -> 150Hz / QRateDivisor)
	mEm7180_SetData8(QRateDivisor, 0x01); // -> env 75 Hz (en fait, je dirais plutot 150Hz, ça divise par 1, pas par 2 (?))
	//Set AlgorithmControl register (enable heading, pitch and roll)
	mEm7180_SetData8(AlgorithmControl, 0x06);
	// Set EnableEvent register (enable interrupt when: reset, error, new quaternion available)
	mEm7180_SetData8(EnableEvents, 0x07);
}

void mEm7180_Open()
{
	// Enable run Sentral sensor algorithm
	mEm7180_SetData8(HostControl, 0x01);
}

void mEm7180_Close()
{
	// Disable run Sentral sensor algorithm
	mEm7180_SetData8(HostControl, 0x00);
}

//TODO test
void mEm7180_GetQuaternions(EM7180_DataStruct *aResultStruct)
{
	//X
	(aResultStruct)->QX.s[0] = mEm7180_GetData8(0x0);
	(aResultStruct)->QX.s[1] = mEm7180_GetData8(0x1);
	(aResultStruct)->QX.s[2] = mEm7180_GetData8(0x2);
	(aResultStruct)->QX.s[3] = mEm7180_GetData8(0x3);

	//*(aQuaeternionsTab+0) = (mEm7180_GetData8(0x0)) + (mEm7180_GetData8(0x1)<<8) + (mEm7180_GetData8(0x2)<<16) + (mEm7180_GetData8(0x3)<<24);

	//Y
	(aResultStruct)->QY.s[0] = mEm7180_GetData8(0x4);
	(aResultStruct)->QY.s[1] = mEm7180_GetData8(0x5);
	(aResultStruct)->QY.s[2] = mEm7180_GetData8(0x6);
	(aResultStruct)->QY.s[3] = mEm7180_GetData8(0x7);
	//*(aQuaeternionsTab+1) = (mEm7180_GetData8(0x4)) + (mEm7180_GetData8(0x5)<<8) + (mEm7180_GetData8(0x6)<<16) + (mEm7180_GetData8(0x7)<<24);

	//Z
	(aResultStruct)->QZ.s[0] = mEm7180_GetData8(0x8);
	(aResultStruct)->QZ.s[1] = mEm7180_GetData8(0x9);
	(aResultStruct)->QZ.s[2] = mEm7180_GetData8(0xA);
	(aResultStruct)->QZ.s[3] = mEm7180_GetData8(0xB);
	//*(aQuaeternionsTab+2) = (mEm7180_GetData8(0x8)) + (mEm7180_GetData8(0x9)<<8) + (mEm7180_GetData8(0xA)<<16) + (mEm7180_GetData8(0xB)<<24);

	//W
	(aResultStruct)->QW.s[0] = mEm7180_GetData8(0xC);
	(aResultStruct)->QW.s[1] = mEm7180_GetData8(0xD);
	(aResultStruct)->QW.s[2] = mEm7180_GetData8(0xE);
	(aResultStruct)->QW.s[3] = mEm7180_GetData8(0xF);
	//*(aQuaeternionsTab+3) = (mEm7180_GetData8(0xC)) + (mEm7180_GetData8(0xD)<<8) + (mEm7180_GetData8(0xE)<<16) + (mEm7180_GetData8(0xF)<<24);

	//Timestamp
	aResultStruct->QTime = (mEm7180_GetData8(0x10)) + (mEm7180_GetData8(0x10)<<8);

}


//TODO test
void mEm7180_GetEuler(EM7180_DataStruct *aResultStruct)
{
//	float test = 0;
//	float heading = 0;
//	float attitude = 0;
//	float bank = 0;
//
//	//Get timestamp (when has the measure been released, useful for integration,... check datasheet of em7180/sentral to convert in ms if required)
//	*aTimeStamp = (UInt16) ((mEm7180_GetData8(0x10)) + (mEm7180_GetData8(0x10)<<8));
//
//	//TODO caster en UIn16 avant le shift ?
//	//Get quaternions
//	float qx = (float) ((mEm7180_GetData8(0x0)) + (mEm7180_GetData8(0x1)<<8) + (mEm7180_GetData8(0x2)<<16) + (mEm7180_GetData8(0x3)<<24));
//	float qy = (float) ((mEm7180_GetData8(0x4)) + (mEm7180_GetData8(0x5)<<8) + (mEm7180_GetData8(0x6)<<16) + (mEm7180_GetData8(0x7)<<24));
//	float qz = (float) ((mEm7180_GetData8(0x8)) + (mEm7180_GetData8(0x9)<<8) + (mEm7180_GetData8(0xA)<<16) + (mEm7180_GetData8(0xB)<<24));
//	float qw = (float) ((mEm7180_GetData8(0xC)) + (mEm7180_GetData8(0xD)<<8) + (mEm7180_GetData8(0xE)<<16) + (mEm7180_GetData8(0xF)<<24));

	//Convert quaternions to Euler

	//Test if singularities
//	test = qx*qy + qz*qw;
//	if (test > 0.499) { // singularity at north pole
//		heading = 2 * atan2(qx,qw);
//		attitude = PI/2;
//		bank = 0;
//	}
//	else if (test < -0.499) { // singularity at south pole
//		heading = -2 * atan2(qx,qw);
//		attitude = - PI/2;
//		bank = 0;
//	}
//	else
//	{
//		//Compute qx^2,qy^2,qz^2
//		double sqx = qx*qx;
//		double sqy = qy*qy;
//		double sqz = qz*qz;
//		double sqw = qw*qw;
//		double norm2 = sqx + sqy + sqz + sqw;
//		//Convert
//		heading = atan2(2*qy*qw-2*qx*qz , 1 - 2*sqy - 2*sqz);
//		attitude = asin(2*test);
//		bank = atan2(2*qx*qw-2*qy*qz , 1 - 2*sqx - 2*sqz);
////	}
//	//Store
//	*(aEulerTab+0) = heading;
//	*(aEulerTab+1) = attitude;
//	*(aEulerTab+2) = bank;
}
//-----------------------------------------------------------------------------
// Lecture d'un registre 8 bits du capteur EM7180
// aReg:    le registre que l'on veut lire (son adresse)
// aData:   l'adresse du variable dans laquelle on écrit le contenu du registre
// retour : true --> lecture OK, false --> lecture KO
//-----------------------------------------------------------------------------
UInt8 mEm7180_GetData8(EM7180_Reg_Enum aReg)
{
	bool aNoAck=false;

	// Disable transmit ACK
	iI2C_SetAckMode(kI2c0, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(kI2c0, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// Début de la transmission --> mode write et START condition
	iI2C_TxRxSelect(kI2c0, kTxMode);
	iI2C_SetStartState(kI2c0);

	// Transmission de l'adresse en WRITE du slave dans le registre de données
	// --> obligatoire protocolle I2C, le slave doit d'abords répondre à son adresse
	iI2C_SendData(kI2c0, EM7180_ADDR_W);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(kI2c0, kTxMode);
		iI2C_SetAckMode(kI2c0, kNoAck);
		iI2C_SetStopState(kI2c0);
		return 0;
	}

	// Transmission de l'adresse du registre que l'on veut lire
	iI2C_SendData(kI2c0, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(kI2c0, kTxMode);
		iI2C_SetAckMode(kI2c0, kNoAck);
		iI2C_SetStopState(kI2c0);
		return 0;
	}

	// Nouvelle condition START
	iI2C_SetRepeatedStartSate(kI2c0);

	//-----------------------------------------------------------------------------
	// Passage en READ
	//-----------------------------------------------------------------------------

	// Transmission de l'adresse en READ du slave dans le registre de données
	// --> obligatoire protocolle I2C, le slave doit d'abords répondre à son adresse
	iI2C_SendData(kI2c0, EM7180_ADDR_R);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(kI2c0, kTxMode);
		iI2C_SetAckMode(kI2c0, kNoAck);
		iI2C_SetStopState(kI2c0);
		return 0;
	}

	// Passage en mode READ
	// --> En lecture c'est au master d'envoyer le ACK mais comme on
	// lit q'un byte pas besoin de ACK
	//iI2C_EnableTxAck();
	iI2C_TxRxSelect(kI2c0, kRxMode);

	// Lecture qui ne sert à rien --> permet l'émission de l'horloge nécessaire au
	// slave afin de transmettre sa donnée
	iI2C_ReadData(kI2c0);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// FIN de la lecture
	// Génération de la condition STOP
	// Obligatoire de faire le STOP avant la lecture pour
	// ne pas émettre de clock à nouveau!
	iI2C_TxRxSelect(kI2c0, kTxMode);
	iI2C_SetAckMode(kI2c0, kNoAck);
	iI2C_SetStopState(kI2c0);

	// Lecture de la valeur du registre demandé
	return iI2C_ReadData(kI2c0);
}


//-----------------------------------------------------------------------------
// Ecriture d'un registre 8 bits du capteur EM7180
// aReg:    le registre que l'on veut écrire (adresse)
// aData:   le contenu du registre
// retour : true --> lecture OK, false --> lecture KO
//-----------------------------------------------------------------------------
bool mEm7180_SetData8(EM7180_Reg_Enum aReg,UInt8 aVal)
{
	bool aNoAck=false;

	// Disable transmit ACK
	iI2C_SetAckMode(kI2c0, kNoAck);

	// Attend que le bus soit libre
	while(true==iI2C_ReadStatus(kI2c0, kBUSY));

	//-----------------------------------------------------------------------------
	// D'abords en WRITE afin de transmettre le registre
	// que l'on veut lire ainsi que l'adresse du slave
	//-----------------------------------------------------------------------------

	// Début de la transmission --> mode write et START condition
	iI2C_TxRxSelect(kI2c0, kTxMode);
	iI2C_SetStartState(kI2c0);

	// Transmission de l'adresse en WRITE du slave dans le registre de données
	// --> obligatoire protocolle I2C, le slave doit d'abords répondre à son adresse
	iI2C_SendData(kI2c0, EM7180_ADDR_W);


	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(kI2c0, kTxMode);
		iI2C_SetAckMode(kI2c0, kNoAck);
		iI2C_SetStopState(kI2c0);
		return false;
	}


	// Transmission de l'adresse du registre que l'on veut écrire
	iI2C_SendData(kI2c0, aReg);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	if(aNoAck==true)
	{
		// FIN de la lecture
		iI2C_TxRxSelect(kI2c0, kTxMode);
		iI2C_SetAckMode(kI2c0, kNoAck);
		iI2C_SetStopState(kI2c0);
		return false;
	}


	// Transmission de la donnée que l'on veut écrire dans le registre
	iI2C_SendData(kI2c0, aVal);

	// Attend la fin de la transmission
	iI2C_WaitEndOfRxOrTx(kI2c0);

	// Est-ce que le slave est content --> Read Ack
	aNoAck=iI2C_ReadStatus(kI2c0, kRxAK);

	// FIN de la lecture
	iI2C_TxRxSelect(kI2c0, kTxMode);
	iI2C_SetAckMode(kI2c0, kNoAck);
	iI2C_SetStopState(kI2c0);
	if(aNoAck==true)
	{
		return false;
	}
	else
	{
		return true;
	}
}


