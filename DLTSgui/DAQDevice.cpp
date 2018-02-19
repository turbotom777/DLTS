// DAQDevice.cpp: implementation of the DAQDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DAQDevice.h"

#include "DataHandler.h"
#include "HardwareException.h"

#include "wdaq_c.h"
#include "nidaqcns.h"




#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DAQDevice::DAQDevice()
{

}

DAQDevice::~DAQDevice()
{
	DAQ_Clear (DEVICE_AT_MIO_16);
}


int DAQDevice::_DAQ_Clear(void)
{
	short status =  DAQ_Clear (DEVICE_AT_MIO_16);
	if ( status != DAQ_NO_ERROR && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR )
	{
		console.writeln ("DAQ_Clear FEHLER NUMMER %d",status);
	}
	return status;
}


int DAQDevice::_AI_Read(short & reading, int gain)
{
	int status = AI_Read(DEVICE_AT_MIO_16, CHANNEL_0, gain, &reading);
	if (status != 0)
	{
		console.writeln("Fehler Nr.%d bei  IOCard.read !", status );
	}
	return status;
}

int DAQDevice::_AO_VWrite(float value)
{
	int status = AO_VWrite (DEVICE_AT_MIO_16, CHANNEL_0, value); // FÜLLIMPULS*)
	if (status != 0){
		console.writeln("Fehler Nr.%d bei  IOCard.write !", status );
	}
	return status;
}

int DAQDevice::_AI_VScale(int gain, int unscaliert, double &scaliert)
{
	int status = AI_VScale (1, CHANNEL_0, gain, GAIN_ADJUSTMENT, SCALE_OFFSET, unscaliert, &scaliert);
	if (status != 0) {
		console.writeln ("AI_VScale FEHLER NUMMER %d ",status);
	}
	return status;
}

int DAQDevice::_AO_Configure(int updateMode)
{
	int status;
	status= AO_Configure (DEVICE_AT_MIO_16, CHANNEL_0, POLARITY_BIPOLAR, INTERNAL_REFERENCE, REFERENCE_VOLTAGE_MINUS_10_PLUS_10, updateMode);  // Vorbereitung der Ausgangswandler(D/A) nach änderung der Firmeneinstellung*)
	if (status != 0){ 
		console.writeln("Status AO_Configure %d", status);
	}
	return status;
}


int DAQDevice::_DAQ_Start(int amplification, int timebaseIndex, int sampleInterval, DataHandler * dataHandler, int numberOfSamples)
{
	// start data aquisition  and store input in an array.
	int status = DAQ_Start(DEVICE_AT_MIO_16, CHANNEL_0, amplification, (short*) dataHandler->getMemoryHandle(), numberOfSamples, timebaseIndex, sampleInterval);
	if (status != 0){
		console.writeln ("DAQ Start FEHLER NUMMER %d ", status);
	}
	return status;
}

void DAQDevice::checkDAQFinished()
{
    short isFinishedFlag = 0;
    unsigned long number = 0;

	int status = 0;
	bool bFirst = true;
	while (!isFinishedFlag && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		status = DAQ_Check (DEVICE_AT_MIO_16, &isFinishedFlag, &number);
		if (bFirst && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
			//console.writeln("Transfer of data in progress...");
			bFirst = false;
		}
	}
	
	if (!bFirst && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		//console.writeln("Finished transfer of data!");
	}


	if (status != DAQ_NO_ERROR && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		console.writeln ("DAQ_Check FEHLER NUMMER %d", status);
	} 
}

int DAQDevice::getDrift(int nuberOfAverage, int gain)
{
	int count;
	int drift = 0;			
	for (count = 0; count < nuberOfAverage; count++) {
		short input;
		_AI_Read(input, gain);
		drift = drift + input;
	}
	drift = (int) drift/count;
	return drift;
}

int DAQDevice::_CTR_Reset(void)
{
	int status = CTR_Reset (DEVICE_PC_TIO_10, COUNTER_1, LOGIC_HIGH_OUT);                    //Zähler 1 auf HIGH       *)
	if (status != 0)
	{
		console.writeln ("CTR_Reset 1 FEHLER NUMMER %d", status);
		return status;
	}

	status = CTR_Reset (DEVICE_PC_TIO_10, COUNTER_2, LOGIC_HIGH_OUT);                    // Zähler 2 auf HIGH       *)
	if (status != 0) 
	{
		console.writeln ("CTR_Reset  5 FEHLER NUMMER %d", status);
		return status;
	}
	return status;
}

int DAQDevice::_CRT_Pulse(int pulseWidth, int delay)
{

	// minimal value is 3!
	int delayCounter1 = 3;
	// if 
	int status = CTR_Pulse (DEVICE_PC_TIO_10, COUNTER_1, TIMEBASE_INDEX, delayCounter1, pulseWidth);				//Pulsausgabe Zähler1, Zeitbasis 1(1ys)*)
	if (status != 0)										// 10 Zeiteinheiten bis Pulsanfang     *)
	{														// "LOW" Puls,dann Pulsbreite*1ys "HIGH"*)
		console.writeln ("CTR_Pulse 1 FEHLER NUMMER %d", status);	//  Danach wieder LOW Puls mit 1ys      *)   
		return status;								// zum Schluß "HIGH" Zustand   
	}                                                     
                            
	int pulseWidthCounter2 = 10000;
	int delayCounter2 = pulseWidth + delay;
	status = CTR_Pulse (DEVICE_PC_TIO_10, COUNTER_2, TIMEBASE_INDEX, delayCounter2, pulseWidthCounter2);// Pulsausgabe Zähler2, Zeitbasis 1(1ys)*)
	if (status != 0) 
	{										// (VERSATZ+PULSBREITE+9)*Zeiteinheit bis Pulsanfang*)
		console.writeln ("CTR_Pulse 5 FEHLER NUMMER ",status);		// 10 Zeiteinheiten bis Pulsende       *)
		return status;										// Versatz+Pulsbreite darf nicht NEGATIV sein!!*)
	}
	return status;	
}

int DAQDevice::_CTR_Simul_Op(int updateMode)
{

	const int NUMBER_OF_COUNTER = 2;
	short COUNTER_1_2[NUMBER_OF_COUNTER];
	COUNTER_1_2[0] = COUNTER_1;
	COUNTER_1_2[1] = COUNTER_2;


	int status = CTR_Simul_Op (DEVICE_PC_TIO_10, NUMBER_OF_COUNTER, COUNTER_1_2, updateMode);      
															// Gleichzeitiger Start    *)
															// von 2 Zählern definiert *)       
															// in dem Feld ctrList     *)
															// RESERVIEREN =1         *)

	if (status != 0) {
	   console.writeln("Fehler bei CTR Simult Op  1  NUMMER  %d ", status);
	}
	return status;
}


int DAQDevice::_DAQ_Config(int triggerMode)
{
	int status = DAQ_Config (DEVICE_AT_MIO_16, triggerMode, INTERNAL_CLOCK);  // BOARD=1,EXTERNER TRIGGER =1 erlaubt HARDWARE TRIGGERUNG!!,INTERNER ZÄHLER =0*)
	if (status != 0){
		console.writeln ("DAQ_CONFIGURE Fehler Nummer= %d",status);
	}
	return status;
}
