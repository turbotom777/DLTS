#include "stdafx.h"
#include "DataHandler.h"
#include "Card.h"
#include "IOCard.h"
#include "HardwareException.h"

#include "wdaq_c.h"
#include "nidaqcns.h"
#include ".\iocard.h"

const static int DEVICE_AT_MIO_16 = 1;
const static int DEFAULT_OUT_CHANNEL = 0;
const static int DEFAULT_IN_CHANNEL = 0; 


IOCard::IOCard(void)
{
	m_device = DEVICE_AT_MIO_16;
	m_outputChannel = DEFAULT_OUT_CHANNEL;
	m_inputChannel = DEFAULT_IN_CHANNEL;
}

IOCard::~IOCard(void)
{
	_DAQ_Clear();
}

int IOCard::_DAQ_Clear(void)
{
	short status =  DAQ_Clear (m_device);
	if ( status != DAQ_NO_ERROR && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR )
	{
		console.writeln ("DAQ_Clear FEHLER NUMMER %d",status);
	}
	return status;
}


bool IOCard::initC_t(void)
{
	const bool kommentar = true;
	// Für Externe Trigerung  der Spannungsausgabe*)
	// von DAC 0 durch Low Puls an Out2 =Pin 46   *)
	// bei Update Mode = 2 *)


	const int updateMode = 2;	// 0: write on update
								// 1: update on call of AO_Update
								// 2: update on active low pulse on OUT2 (MIO-16)

	_AO_Configure(updateMode);

	// ??? why all???
	const int allChannel = -1;				// -1: apply configuration to all input channels!!!
	const int inputMode = 0;				// 0: differential configuration (DIFF)
											// 1: Referenced Single-Ended (RSE)
											// 2: Nonreferenced Single-Ended (NRSE)
	const int inputRange = 20;				// 5: -2.5 to 2.5 or 0 to 5V
											// 10: -5 to +5 or 0 to 10V
											// 20: -10 to +10V

	const int inputPolarity = 0;					// 0: bipolar (default)
											// unipolar
	int aisense = 0;						// ignored for AT-MIO-16
	int status = AI_Configure (m_device, allChannel, inputMode , inputRange, inputPolarity , aisense);  // Board=1,Kanal=0,Differential=0,Bereich=20Volt,Bipolar=0,Aisense=?*)
	if (status!= 0){
		console.writeln("Status AI_Configure %d", status);
	}

	int numMuxBoards = 0;					// 0: no external multiplexer
											// 1,2,4: number of AMUX-64T boards connected
	status = AI_Mux_Config (m_device, numMuxBoards);
	if (status != 0){
		console.writeln("Status AI_MUX_Configure %d", status);
	}
	

	const int startTrigger = 0;				// 0: generate software trigger
											// 1: wait for external trigger at STARTTRIG (MIO-16)

	const int extConversion = 0;			// 0: use onbaord clocks to controll data acquesition sample interval
											// 1: allow external clock to control sample inverval
											// 2: allow external clock to control scan-interval timing
									
	status = DAQ_Config (m_device, startTrigger, 0);  // BOARD=1,EXTERNER TRIGGER =1 erlaubt HARDWARE TRIGGERUNG!!,INTERNER ZÄHLER =0*)
	if (status != 0){
		console.writeln ("DAQ_CONFIGURE Fehler Nummer= %d",status);
	}

	const int stopTrigger = 0;				// 0: disable pretrigger (default)
											// 1: enable pretrigger
	const int pointsAfterStopTrigger = 0;	// valid only, if stopTrigger = 1!
									
	status = DAQ_StopTrigger_Config (m_device, stopTrigger, pointsAfterStopTrigger); //Erlaubt Meßdatenerfassung vor!! dem Trigger "PRETRIGGER".Nicht benutzt!!*)
	if (status != 0){
		console.writeln("DAQ_Stop Trigger Configure Fehler Nummer= %d",status);
	}

	const int doubleBufferMode = 0;			// 0: disable double buffer mode (default)
											// 1: enable double buffer
	status = DAQ_DB_Config (m_device, doubleBufferMode);	//Datenspeicherung in zwei Speicher AUSGESCHALTET!!*)
	if (status!= 0){
		console.writeln("DAQ_DB_Configure Fehler Nummer= %d",status);
	}

	const int timeout = 500;			// -1: indefinitely (disabled)
										// 0-2**32-1 ticks: 1 tick is about 55ms!
	status = Timeout_Config (m_device, timeout);
	if (status != 0){
		console.writeln("TIMEOUT_Configure Fehler Nummer= %d",status);
	}

	short aufzeichnung;
	short value;
	status = AI_Check (m_device, &aufzeichnung, &value) ;
	if (status != 0){
		console.writeln("AI_Check Fehler Nummer= %d",status);
	}
	
	if (aufzeichnung != 0) {
		console.writeln("Es wurde eine Messung gestartet");
		console.writeln("Anzahl der Aufgezeichneten Werte von AI CHECK: %d", value);
	}

	unsigned long version;
	status = Get_NI_DAQ_Version (&version) ;
	if (status == 0){	
		version = (version & 0xffFF);
		if (version == 0x0452 ) {
			console.writeln("Version Nummer der NIDAQ Software =4.5.2");
		}
		else {
			console.writeln("Version (Fehler?) %d", version);
		}
	}
	else {
		console.writeln("Configure Fehler Nummer= %d", status);
	}


/*
	{ Status:= Get_DA_Brds_Info (1,brdCode, baseAddr, irq1Lvl,irq2Lvl, irqTrigMode, dma1Lvl, dma2Lvl, daqMode ) ;
	if status<>0 then Writeln(status,'_status von Get DA Brds INFO !');
	Writeln(brdCode,' =Wert von brdCode');
	Writeln(baseAddr,' =Wert von baseAddr','OK falls',$220);
	Writeln(irq1Lvl,' =Wert von irq1Lvl');
	Writeln(irq2Lvl,' =Wert von irq2Lvl');
	Writeln(irqTrigMode,' =Wert von irqTrigMode');
	Writeln(dma1Lvl,' =Wert von dma1Lvl');
	Writeln(dma2Lvl,' =Wert von dma2Lvl');
	Writeln(daqMode,' =Wert von daqMode');   }


	{   function Set_DAQ_Device_Info (deviceNumber : Integer; infoType, infoVal
	: Longint) : integer; far; external 'atwdaq'; }

*/
	int infoType = ND_DATA_XFER_MODE_AI ;
	unsigned long infoVal;

	CHardwareException exception;
	


	status = Get_DAQ_Device_Info (m_device, infoType, &infoVal) ;
	if (infoVal == 35300 && kommentar) {
		console.writeln("ND_DATA_XFER_MODE_AI ist ND_UP_TO_2_DMA_CHANNELS");
	} else if (infoVal = 35200 && kommentar){
		console.writeln("ACHTUNG !!! ND_DATA_XFER_MODE_AI ist ND_UP_TO_1_DMA_CHANNEL");
	} else {
		console.writeln("Keine Datenerfassung möglich !!");
		throw exception;    
	}

	infoType =  ND_DATA_XFER_MODE_AO_GR1 ;
	status = Get_DAQ_Device_Info (m_device, infoType, &infoVal) ;
	if (infoVal == 19600 && kommentar) {
		console.writeln("ND_DATA_XFER_MODE_AO ist ND_INTERRUPTS ");
	} else { 
		console.writeln("Keine getriggerte Pulsausgabe möglich !!");
		throw exception;     
	}


	infoType = ND_INTERRUPT_A_LEVEL;
	status = Get_DAQ_Device_Info (m_device, infoType, &infoVal) ;
	console.writeln("ND_INTERRUPT_A_LEVEL =10");
	if (infoVal > 0){
		console.writeln("ND_INTERRUPT_A_LEVEL = %d", infoVal);
	} else {
		console.writeln("Kein Interrupt A !!");
		throw exception;
	}

	infoType = ND_DMA_A_LEVEL ;
	status = Get_DAQ_Device_Info (m_device, infoType, &infoVal) ;
	if (infoVal > 0) {
		console.writeln("DMA KANAL 1 ist 6 ");
	} else {
		console.writeln("Kein DMA KANAL !!");
		throw exception;
	}      
	

	infoType = ND_DMA_B_LEVEL ;
	status = Get_DAQ_Device_Info (m_device, infoType, &infoVal) ;
	if (infoVal > 0){
		console.writeln("DMA KANAL 2 ist 7 ");
	} else {
		console.writeln("Kein DMA KANAL !!");
		throw exception;
	}
	return true;
}

int IOCard::_AI_Read(short & reading, int gain)
{
	int status = AI_Read(m_device, m_inputChannel, gain, &reading);
	if (status != 0)
	{
		console.writeln("Fehler Nr.%d bei  IOCard.read !", status );
	}
	return status;
}

int IOCard::_AO_VWrite(float value)
{
	int status = AO_VWrite (m_device, m_outputChannel, value); // FÜLLIMPULS*)
	if (status != 0){
		console.writeln("Fehler Nr.%d bei  IOCard.write !", status );
	}
	return status;
}

int IOCard::_AI_VScale(int gain, int unscaliert, double &scaliert)
{
	int const gainAdjust = 1;
	int const offset = 0;
	int status = AI_VScale (1, m_inputChannel, gain, gainAdjust, offset, unscaliert, &scaliert);
	if (status != 0) {
		console.writeln ("AI_VScale FEHLER NUMMER %d ",status);
	}
	return status;
}

int IOCard::_AO_Configure(int updateMode)
{
	// updateMode
	// 0: write on update
	// 1: update on call of AO_Update
	// 2: update on active low pulse on OUT2 (MIO-16)

	const int chan = 0;					// analog output channel
	const int outputPolarity = 0;		// 0: bipolar (-refVolate to +refVoltage);  
										// 1: unipolar (0 to +refVoltage)
	const int intOrExtRef = 0;			// 0: internal reference; 
										// 1: external reference
	const int refVoltage = 10;			// analog output channel voltage reference value; range -10 to +10 


	int status;
	status= AO_Configure (m_device, m_outputChannel, outputPolarity, intOrExtRef, refVoltage, updateMode);  // Vorbereitung der Ausgangswandler(D/A) nach änderung der Firmeneinstellung*)
	if (status != 0){ 
		console.writeln("Status AO_Configure %d", status);
	}
	return status;
}

int IOCard::getInputChannel(void)
{
	return m_inputChannel;
}

int IOCard::_DAQ_Start(int amplification, int timebaseIndex, int sampleInterval, DataHandler & dataHandler)
{
	// start data aquisition  and store input in an array.
	int status = DAQ_Start(m_device, m_inputChannel, amplification, (short*) dataHandler.getMemoryHandle(), MAX_MEMORY_ELEMENTS, timebaseIndex, sampleInterval);
	if (status != 0){
		console.writeln ("DAQ Start FEHLER NUMMER %d ", status);
	}
	return status;
}

void IOCard::checkDAQFinished()
{
    short isFinishedFlag = 0;
    unsigned long number = 0;

	int status = 0;
	bool bFirst = true;
	while (!isFinishedFlag && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		status = DAQ_Check (m_device, &isFinishedFlag, &number);
		if (bFirst && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
			console.writeln("Transfer of data in progress...");
			bFirst = false;
		}
	}
	
	if (!bFirst && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		console.writeln("Finished transfer of data!");
	}


	if (status != DAQ_NO_ERROR && status != DAQ_NO_TRANSFER_IN_PROGRESS_ERROR){
		console.writeln ("DAQ_Check FEHLER NUMMER %d", status);
	} 
}

int IOCard::getDrift(int nuberOfAverage, int gain)
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
