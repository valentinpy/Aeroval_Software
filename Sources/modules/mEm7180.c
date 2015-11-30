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

#include "mEm7180.h"

//-----------------------------------------------------------------------------------
//Static prototypes
//-----------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Send a byte to Em7180 over I2C
// aReg: register to write into
// aVal: value to write in aReg
// return: true: write successful, false: error when writing
//-------------------------------------------------------------------
static bool mEm7180_SetData8(EM7180_Reg_Enum aReg,UInt8 aVal);

//-------------------------------------------------------------------
// Read a byte from Em7180 over I2C
// aReg: register to read
// return: value of the register aReg
//-------------------------------------------------------------------
static UInt8 mEm7180_GetData8(EM7180_Reg_Enum aReg);



//-----------------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------------

//-------------------------------------------------------------------
// Basic setup of the sensor
//-------------------------------------------------------------------
void mEm7180_Setup()
{
	//Configure I2C bus
	iI2C_Config();
	iI2C_Enable(kI2c0);

	// Hardware reset of EM7180 module
	mEm7180_SetData8(ResetReq, 0x01);

	// Wait for reset
	UInt16 aDelay = mDelay_GetDelay(kPit0, 100);
	while(mDelay_IsDelayDone(kPit0, aDelay)==false);
	mDelay_DelayRelease(kPit0, aDelay);

	// Check EEPROM detected by SENTRAL
	while(FALSE == (0x01 & mEm7180_GetData8(SentralStatus)));

	// Check Configuration file uploaded from EEPROM to SENTRAL
	while(FALSE == (0x01 & (mEm7180_GetData8(SentralStatus) >> 1)));

	// Check if upload has successfull finished (CRC = OK)
	//TODO WTF?
	if(FALSE == (0x01 & (mEm7180_GetData8(SentralStatus) >> 2)))
	{
		//mRs232_SendString("[Sentral / INFO]	Configuration file successfully uploaded!\r\n");
	}
	else
	{
		//mRs232_SendString("[Sentral / ERROR]	Failed to upload configuration file!\r\n");
	}

	// Set MagRate register to 200Hz
	mEm7180_SetData8(MagRate, 0xC8);
	// Set AccelRate register to 200Hz
	mEm7180_SetData8(AccelRate, 0x14);
	// Set GyroRate register to 300Hz
	mEm7180_SetData8(GyroRate, 0x1E);
	// Set QRateDivisor to 1 (Related to GyroRate -> 1300Hz / QRateDivisor)
	mEm7180_SetData8(QRateDivisor, 0x01);
	//Set AlgorithmControl register (enable heading, pitch and roll)
	mEm7180_SetData8(AlgorithmControl, 0x06);
	// Set EnableEvent register (enable interrupt when: reset, error, new quaternion available)
	mEm7180_SetData8(EnableEvents, 0x07);
}

//-------------------------------------------------------------------
// Run sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Open()
{
	// Enable run Sentral sensor algorithm
	mEm7180_SetData8(HostControl, 0x01);
}

//-------------------------------------------------------------------
// Stop sensor algorithm
//-------------------------------------------------------------------
void mEm7180_Close()
{
	// Disable run Sentral sensor algorithm
	mEm7180_SetData8(HostControl, 0x00);
}

//-------------------------------------------------------------------
// Read heading, pitch, roll and timestamp
// *aResultStruct: pointer over a structure which in which the values are stored (QX, QY, QZ, QTime)
// TODO add return value to detect problems during flight
//-------------------------------------------------------------------
void mEm7180_GetEuler(EM7180_DataStruct *aResultStruct)
{
	//TODO handle error:
	/*
	  Exemple of code to implement:

	  Check event status register, way to chech data ready by polling rather than interrupt
	  uint8_t eventStatus = readByte(EM7180_ADDRESS, EM7180_EventStatus); // reading clears the register

	   // Check for errors
	  if(eventStatus & 0x02) { // error detected, what is it?

	  uint8_t errorStatus = readByte(EM7180_ADDRESS, EM7180_ErrorRegister);
	  if(!errorStatus) {
	  Serial.print(" EM7180 sensor status = "); Serial.println(errorStatus);
	  if(errorStatus & 0x11) Serial.print("Magnetometer failure!");
	  if(errorStatus & 0x12) Serial.print("Accelerometer failure!");
	  if(errorStatus & 0x14) Serial.print("Gyro failure!");
	  if(errorStatus & 0x21) Serial.print("Magnetometer initialization failure!");
	  if(errorStatus & 0x22) Serial.print("Accelerometer initialization failure!");
	  if(errorStatus & 0x24) Serial.print("Gyro initialization failure!");
	  if(errorStatus & 0x30) Serial.print("Math error!");
	  if(errorStatus & 0x80) Serial.print("Invalid sample rate!");
	 */

	//TODO read only if new data available:
	/*
	 Exemple of code to implement:
	 if no errors, see if new data is ready
  	 if(eventStatus & 0x10) { // new acceleration data available
	 readSENtralAccelData(accelCount);

	// Now we'll calculate the accleration value into actual g's
	ax = (float)accelCount[0]*0.000488;  // get actual g value
	ay = (float)accelCount[1]*0.000488;
	az = (float)accelCount[2]*0.000488;
  }

	 */

	//X
	(aResultStruct)->QX.s[0] = mEm7180_GetData8(0x0);
	(aResultStruct)->QX.s[1] = mEm7180_GetData8(0x1);
	(aResultStruct)->QX.s[2] = mEm7180_GetData8(0x2);
	(aResultStruct)->QX.s[3] = mEm7180_GetData8(0x3);

	//Y
	(aResultStruct)->QY.s[0] = mEm7180_GetData8(0x4);
	(aResultStruct)->QY.s[1] = mEm7180_GetData8(0x5);
	(aResultStruct)->QY.s[2] = mEm7180_GetData8(0x6);
	(aResultStruct)->QY.s[3] = mEm7180_GetData8(0x7);

	//Z
	(aResultStruct)->QZ.s[0] = mEm7180_GetData8(0x8);
	(aResultStruct)->QZ.s[1] = mEm7180_GetData8(0x9);
	(aResultStruct)->QZ.s[2] = mEm7180_GetData8(0xA);
	(aResultStruct)->QZ.s[3] = mEm7180_GetData8(0xB);

	//W
	//TODO remove qw?
	(aResultStruct)->QW.s[0] = mEm7180_GetData8(0xC);
	(aResultStruct)->QW.s[1] = mEm7180_GetData8(0xD);
	(aResultStruct)->QW.s[2] = mEm7180_GetData8(0xE);
	(aResultStruct)->QW.s[3] = mEm7180_GetData8(0xF);

	(aResultStruct)->GX = ((UInt16)mEm7180_GetData8(0x22)) | ((UInt16)mEm7180_GetData8(0x23) <<8);
	(aResultStruct)->GY = ((UInt16)mEm7180_GetData8(0x24)) | ((UInt16)mEm7180_GetData8(0x25) <<8);
	(aResultStruct)->GZ = ((UInt16)mEm7180_GetData8(0x26)) | ((UInt16)mEm7180_GetData8(0x27) <<8);
	//Timestamp
	aResultStruct->QTime = (mEm7180_GetData8(0x10)) + (mEm7180_GetData8(0x10)<<8);

	//Read events
	(aResultStruct)->Event = mEm7180_GetData8(0x35);
}

//-----------------------------------------------------------------------------
// Read one register (8 bits) from sensor (EM7180)
// aReg:    Address of the register we wnat to read
// Return:	Value of the requested register
//-----------------------------------------------------------------------------
static UInt8 mEm7180_GetData8(EM7180_Reg_Enum aReg)
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


//-------------------------------------------------------------------
// Send a byte to Em7180 over I2C
// aReg: register to write into
// aVal: value to write in aReg
// return: true: write successful, false: error when writing
//-------------------------------------------------------------------
static bool mEm7180_SetData8(EM7180_Reg_Enum aReg,UInt8 aVal)
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


