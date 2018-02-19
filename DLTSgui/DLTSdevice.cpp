// C_t_mess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataHandler.h"
#include "Boonton7200.h"
#include "math.h"
#include "wdaq_c.h"
#include "math.h"
#include "nidaqcns.h"
#include "FileWriter.h"
#include "BufferedFileWriter.h"

#include "DAQDevice.h"
#include "ComHandler.h"
#include "conio.h"
#include "hardwareException.h"
#include "DLTSdevice.h"
#include "TempController.h"
#include "DataArray.h"
#include "DataArrayList.h"
#include "DataElement.h"
#include "DltsGuiDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// The one and only application object


bool CDLTSdevice::m_bRunning = false;
bool CDLTSdevice::m_bAbort = false;


bool CDLTSdevice::doAbort(){
	return m_bAbort;
}

void CDLTSdevice::setAbortFlag(){
	m_bAbort = true;
}


CDLTSdevice::CDLTSdevice(){
	// init with default values!
	m_bAbort = false;
	m_bRunning = false;

	m_pTempController = new TempController();
	m_pBoonton = new CBoonton7200();
	m_pBoonton->initDevice();
	m_pDAQDevice = new DAQDevice();
	m_pDataHandler = new DataHandler();
}


CDLTSdevice::~CDLTSdevice(){
	if (m_pTempController != NULL){
		delete m_pTempController;
	}
	if (m_pBoonton != NULL){
		delete m_pBoonton;
	}
	if (m_pDAQDevice != NULL){
		delete m_pDAQDevice;
	}

	if (m_pDataHandler != NULL){
		delete m_pDataHandler;
	}
}


CBoonton7200* CDLTSdevice::getBoonton(){
	return m_pBoonton;
}

float CDLTSdevice::getCurrentTemp(){
	return m_pTempController->getCurrentTemperature();
}


void CDLTSdevice::testThread(){
	int i = 0;
	m_bRunning = true;
	m_bAbort = false;
	while (!doAbort()){
		Sleep(100);
		i++;
		console.writeln("juhu %d", i);
	}
	m_bRunning = false;
}

bool CDLTSdevice::isRunning(){
	return m_bRunning;
}

void CDLTSdevice::setIsRunning(bool isRunning){
	m_bRunning = isRunning;
}

void CDLTSdevice::start(CDLTSguiDoc * dltsDoc)
{
	if (m_bRunning){
		console.writeln("ERROR, measurement in progress");
		return;
	}
	m_bAbort = false;
	m_bRunning = true;
	int numberOfCapacitanceValues = dltsDoc->m_NumberOfCapacitanceValues;
	if (numberOfCapacitanceValues > MAX_MEMORY_ELEMENTS){
		console.writeln("ERROR, record time is too long!");
	}
	try {
		//CBufferedFileWriter fileWriter("C_t");
		int status;

		this->initCt(dltsDoc->getReverseVoltage() );

		short dataArray[MAX_MEMORY_ELEMENTS];
		short dataArrayAverage[MAX_MEMORY_ELEMENTS];
		long dataArraySum[MAX_MEMORY_ELEMENTS];
		double voltageArray[MAX_MEMORY_ELEMENTS];


		float Tsetpoint = dltsDoc->getStartTemp();
		bool test = true;
		while ( !doAbort() && !dltsDoc->reachedEndTemperature(Tsetpoint) ) {
		// Meßschleife // Temperaturmessung*)
			float Tcurrent= m_pTempController->setTemperature(Tsetpoint, dltsDoc->getTempDeviance(), !dltsDoc->isSingleTemperature());
			if (Tcurrent == ABORT_VALUE){
				break;
			}
			console.writeln(" %f °Celsius ", Tcurrent);
			Tsetpoint = dltsDoc->getNextTemperature(Tsetpoint);
			status = 0;
			
			 // begin Löschen*)
			// prepopulate arrays with 0
			int index;
			for (index = 0; index < MAX_MEMORY_ELEMENTS; index++){ 
				dataArray[index] = 0;
				voltageArray[index] = 0;
				dataArrayAverage[index] = 0;
				dataArraySum[index] = 0;
			}

			int averageCnt = 0;
			int loopCount = 0;
			while (averageCnt < dltsDoc->getNumberOfAveragings()){
			//for (int averageIdx = 0; averageIdx < dltsDoc->getNumberOfAveragings(); averageIdx++ ) {
				// begin Pulsausgabe*)

				loopCount++;
				if (loopCount > dltsDoc->getNumberOfAveragings() * 2){
					console.writeln("Zu viele Messungen sind ungültig. Abbruch!");
					this->setAbortFlag();
				}

				int driftAverageNb = 100;
				int drift1 = m_pDAQDevice->getDrift(driftAverageNb, dltsDoc->getGain());
				double driftVoltage1 = 0.0;
				status = m_pDAQDevice->_AI_VScale(dltsDoc->getGain(), drift1, driftVoltage1);
				//console.writeln("%f Drift I Volt:", driftVoltage);
				if (doAbort()) {
					break;
				}

				/*
				// timer trigger! 	*/
				m_pDAQDevice->checkDAQFinished();
     
				status = m_pDAQDevice->_DAQ_Clear();
				status = m_pDAQDevice->_CTR_Reset();
				m_pDAQDevice->_CRT_Pulse(dltsDoc->getPulseWidth(), dltsDoc->getDelay());
                                                   
				
				// start dataHandler aquisition  and store input in an array.
				m_pDAQDevice->_DAQ_Config(EXTERNAL_TRIGGER);

				// data aquisition will start with timer2 on low.
				// timer2 pulse is {delay}µs after timer1 first pulse
				m_pDAQDevice->_DAQ_Start(dltsDoc->getGain(), TIMEBASE_INDEX , SAMPLE_INTERVAL, m_pDataHandler, numberOfCapacitanceValues);

				// configure writing pulse voltage on low pulse of timer2
				m_pDAQDevice->_AO_Configure(WRITE_ON_LOW_PULSE_ON_OUT2);
				m_pDAQDevice->_AO_VWrite(dltsDoc->getPulseVoltage());

				// start timer1 & timer2 simultanous
				m_pDAQDevice->_CTR_Simul_Op(PERFORM_SIMULTANOUS_START);

				// configure writing reverse voltage on next (second) trigger pulse of timer1  
				// second pulse is {pulseWith}µs after first pulse!
				m_pDAQDevice->_AO_VWrite(dltsDoc->getReverseVoltage());

				// wait for data acquisition to be finished
				m_pDAQDevice->checkDAQFinished();
				m_pDAQDevice->_CTR_Simul_Op(PERFORM_SIMULTANOUS_STOP);
				

				status = m_pDAQDevice->_DAQ_Clear();
				int drift2 = m_pDAQDevice->getDrift(driftAverageNb, dltsDoc->getGain());

				double driftVoltage2 = 0.0;
				status = m_pDAQDevice->_AI_VScale(dltsDoc->getGain(), drift2, driftVoltage2);
				//console.writeln("%f Drift II Volt:", driftVoltage);

				// ceil: round up to a valid integer/long!
				// TODO: find better solution!
				int nullbalance = ceil((double) ((drift1)+(drift2))/2);

				int driftDifference = abs(drift1- drift2);
				
				// if zero level before and after the pulse is near the max. possible resolution, the measurement is not valid!!
				bool bIsInRange = abs(drift1) < (MAX_SAMPLE_VALUE / 2) && abs(drift2) < (MAX_SAMPLE_VALUE / 2);
				if (  driftDifference < MAX_DRIFT_DIFFERENCE && bIsInRange)  //Entsprechend XYZ pF*)
				{ //store)
					m_pDataHandler->copyData(dataArray, numberOfCapacitanceValues, nullbalance);
					//console.writeln("Mittelung Nr. %d", averageCnt);
					for (int i = 0; i < numberOfCapacitanceValues; i++){
						if (averageCnt == 0){
							dataArraySum[i] = dataArray[i];
						} else {	
							dataArraySum[i] += dataArray[i];
						}
						
					}
					averageCnt++;
					
				}
				//end(*Speicherung*)
				else {
					//console.writeln("Diese Messung wird nicht gespeichert !   Differenz ist zu groß: " + driftDifference);
					console.write("!");
					continue;
				}
				console.write(".");
			}
			//end;(*Pulsausgabe*)
			console.writeln("");

			if (averageCnt == dltsDoc->getNumberOfAveragings()){
				console.writeln(" %d Mittelungen ausgefuehrt.", averageCnt);
			} else {
				console.writeln("Messung wird nicht gespeichert!");
				continue;
			}

			for (int i = 0; i < numberOfCapacitanceValues; i++){
				dataArrayAverage[i] = (short) ceil((double) (dataArraySum[i]) / averageCnt);	
			}

			status = DAQ_VScale (DEVICE_AT_MIO_16, CHANNEL_0, dltsDoc->getGain(), GAIN_ADJUSTMENT, SCALE_OFFSET, numberOfCapacitanceValues, dataArrayAverage, voltageArray);
			if (status != 0){	 
				console.writeln ("DAQ_VScale  FEHLER NUMMER %d; Please adjust Gain!", status);
			}

			
			CDataArray *pDataArray = new CDataArray();
			pDataArray->SetTemperature(Tcurrent);
			pDataArray->SetNumberOfAveraging(averageCnt);
			CTime *time = new CTime(CTime::GetCurrentTime());
			pDataArray->SetTime(time);
			pDataArray->SetBoontonRange(m_pBoonton->getRangeMultiplier());

			dltsDoc->GetDataArrayList()->AddElement(pDataArray);
			// todo!
			int timestamp = 0;
			for (int k = 0; k < numberOfCapacitanceValues; k++){	
				double voltage = voltageArray[k];
				double capacitance = m_pBoonton->getCapacitance(voltage);
				CDataElement *element = new CDataElement(capacitance, timestamp);
				pDataArray->AddElement(element);
				timestamp++;
			}

			dltsDoc->SetModifiedFlag(TRUE);

#ifdef _DEBUG
			// for some reason it does NOT work in release build!?!
			BOOL success = AfxGetApp( )->PostThreadMessage(ID_CT_THREAD_MESSAGE, 0,0);
#endif //_DEBUG

			/*
			CString strValue;
			strValue.Format("%3.2f,", Tcurrent);
			fileWriter.appendLine(strValue);
			for (k = 0; k < RESULT_FIELD_SIZE; k++){	
				double voltage = voltageArray[k];
				double capacitance = m_pBoonton->getCapacitance(voltage);
				CString strValue;
				strValue.Format("%2.10f,", capacitance);
				fileWriter.appendLine(strValue);
			}
			fileWriter.resetLineIndex();
			console.writeln("Status %d", status);
			*/

			m_pDAQDevice->_DAQ_Clear();
			

		// end;(*ENDE Meßschleife*)
		}

	//  TODO:
		//close(MessdataHandler);
		m_pDAQDevice->_CTR_Simul_Op(CANCEL_RESERVE_FOR_SIMULTANOUS_START_STOP);

		m_pDAQDevice->_DAQ_Clear();
		status = m_pDAQDevice->_AO_Configure(WRITE_ON_CALL_AO_UPDATE);
    
		//0 Volt werden zu DAC 0 geschrieben*)
		m_pDAQDevice->_AO_VWrite(0.0);
		status = AO_Update (DEVICE_AT_MIO_16);
		//console.writeln("%d", status);

		status = CTR_Reset (DEVICE_PC_TIO_10, COUNTER_1, 0);                    // Zähler 1 auf Tristate    *)
		//console.writeln("%d Status CTR_Reset  1 ", status);

		short outState = 0;
		status = CTR_State (DEVICE_PC_TIO_10, COUNTER_1, &outState);             
		if (status != 0){
			console.writeln("Fehler bei CTR_State1 NUMMER %d",status);
		}
		
		if (outState != 1){
			console.writeln("Zähler Nummer 1 ist nicht Tristate ! Ausgangsstatus= %d", outState);
		}

	} catch (CHardwareException exception){
		console.writeln("An Hardware Exception occured");
	} catch (...){
		console.writeln("An Unknown Exception occured");
	}
	console.writeln("Messung beendet!");
	m_bRunning = false;
}


void CDLTSdevice::writeVoltage(float voltage){
	m_pDAQDevice->_AO_Configure(WRITE_ON_UPDATE);
	Sleep(100);
	m_pDAQDevice->_AO_VWrite(voltage);
	Sleep(100);
}


void CDLTSdevice::initCt(float reverseVoltage)
{		
	// init boonton7200
	m_pBoonton->initC_U();
	
	
	// Für Externe Trigerung  der Spannungsausgabe*)
	// von DAC 0 durch Low Puls an Out2 =Pin 46   *)

	// set reverse voltage as base level -> adjust capacitance meter to reverse voltage!
	this->writeVoltage(reverseVoltage);
	
	int status= AO_Configure (DEVICE_AT_MIO_16, CHANNEL_0, POLARITY_BIPOLAR, INTERNAL_REFERENCE, REFERENCE_VOLTAGE_MINUS_10_PLUS_10, WRITE_ON_UPDATE);  // Vorbereitung der Ausgangswandler(D/A) nach änderung der Firmeneinstellung*)
	if (status != 0){ 
		console.writeln("Status AO_Configure %d", status);
	}

	// ??? why all channels???
	status = AI_Configure (DEVICE_AT_MIO_16, CHANNEL_0, INPUT_MODE_DIFF , INPUT_RANGE_MINUS_10_PLUS_10, POLARITY_BIPOLAR , NOT_DEFINED);  
	if (status!= 0){
		console.writeln("Status AI_Configure %d", status);
	}

	status = AI_Mux_Config (DEVICE_AT_MIO_16, NO_EXTERNAL_MULTIPLEXER);
	if (status != 0){
		console.writeln("Status AI_MUX_Configure %d", status);
	}
	
									
	status = DAQ_Config (DEVICE_AT_MIO_16, SOFTWARE_TRIGGER, INTERNAL_CLOCK);  // BOARD=1,EXTERNER TRIGGER =1 erlaubt HARDWARE TRIGGERUNG!!,INTERNER ZÄHLER =0*)
	if (status != 0){
		console.writeln ("DAQ_CONFIGURE Fehler Nummer= %d",status);
	}

	status = DAQ_StopTrigger_Config (DEVICE_AT_MIO_16, DISABLE_PRETRIGGER, POINTS_0); //Erlaubt Meßdatenerfassung vor!! dem Trigger "PRETRIGGER".Nicht benutzt!!*)
	if (status != 0){
		console.writeln("DAQ_Stop Trigger Configure Fehler Nummer= %d",status);
	}


	status = DAQ_DB_Config (DEVICE_AT_MIO_16, DISABLE_DOUBLE_BUFFER_MODE);	//Datenspeicherung in zwei Speicher AUSGESCHALTET!!*)
	if (status!= 0){
		console.writeln("DAQ_DB_Configure Fehler Nummer= %d",status);
	}

	const int TIME_OUT_VALUE = 500;			// -1: indefinitely (disabled)
										// 0-2**32-1 ticks: 1 tick is about 55ms!
	status = Timeout_Config (DEVICE_AT_MIO_16, TIME_OUT_VALUE);
	if (status != 0){
		console.writeln("TIMEOUT_Configure Fehler Nummer= %d",status);
	}
	this->ShowHardwareInfo();
	
	m_pDAQDevice->_DAQ_Clear();

	//m_pBoonton->setBaseVoltage(dltsDoc->getReverseVoltage());
	// workaround: first pulse needs longer to initalize!
	//m_pBoonton->setPulse(dltsDoc->getReverseVoltage(), dltsDoc->getPulseVoltage());
	Sleep(1000);
	

	// init memory for DAQ
	m_pDataHandler->initMemory();


	// init pc-tio-10 for C/t messuring
	status = CTR_Stop (DEVICE_PC_TIO_10, COUNTER_1);			// suspend operation of specified counter!
	if (status != 0) {
		console.writeln("Fehler bei CTR_Stop1 NUMMER %d", status);
	}
	status = CTR_Stop (DEVICE_PC_TIO_10, COUNTER_2);			// suspend operation of specified counter!
	if (status != 0){
		console.writeln("Fehler bei CTR_Stop2 NUMMER %d", status);
	}

	status = CTR_Config (DEVICE_PC_TIO_10, COUNTER_1, COUNT_RISING_EDGE, NO_GATING_USED, OUT_TYPE_PULSE, NEGATIVE_LOGIC_OUTPUT);          
																// Festlegen von Zähler 1 *)
																// Trigger durch 0 auf  1 *)
																// Start durch Programm   *)
																// Ausgabe einer Flanke_/---*)
																// Invertiert d.h.-5 volt *)
	if (status != 0){
		console.writeln("Fehler bei CTR_Configure 1 NUMMER %d", status);
	}

	status = CTR_Config (DEVICE_PC_TIO_10, COUNTER_2, COUNT_RISING_EDGE, NO_GATING_USED, OUT_TYPE_PULSE, NEGATIVE_LOGIC_OUTPUT);              // Festlegen von Zähler 2*)
	if (status != 0){
	   console.writeln("Fehler bei CTR_Configure 5 NUMMER %d", status);
	}

	const int NUMBER_OF_COUNTER = 2;
	short COUNTER_1_2[NUMBER_OF_COUNTER];
	COUNTER_1_2[0] = COUNTER_1;
	COUNTER_1_2[1] = COUNTER_2;

	status = CTR_Simul_Op (DEVICE_PC_TIO_10, NUMBER_OF_COUNTER, COUNTER_1_2, RESERVE_FOR_SIMULTANOUS_START_STOP);      
															// Gleichzeitiger Start    *)
															// von 2 Zählern definiert *)       
															// in dem Feld ctrList     *)
															// RESERVIEREN =1         *)

	if (status != 0) {
	   console.writeln("Fehler bei CTR Simult Op  1  NUMMER  %d ", status);
	}

	m_pDAQDevice->_CTR_Reset();
}


void CDLTSdevice::ShowHardwareInfo()
{
	short aufzeichnung;
	short value;
	int status = AI_Check (DEVICE_AT_MIO_16, &aufzeichnung, &value) ;
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


	int infoType = ND_DATA_XFER_MODE_AI ;
	unsigned long infoVal;

	CHardwareException exception;
	


	status = Get_DAQ_Device_Info (DEVICE_AT_MIO_16, infoType, &infoVal) ;
	if (infoVal == 35300 && SHOW_INFO) {
		console.writeln("ND_DATA_XFER_MODE_AI ist ND_UP_TO_2_DMA_CHANNELS");
	} else if (infoVal = 35200 && SHOW_INFO){
		console.writeln("ACHTUNG !!! ND_DATA_XFER_MODE_AI ist ND_UP_TO_1_DMA_CHANNEL");
	} else {
		console.writeln("Keine Datenerfassung möglich !!");
		throw exception;    
	}

	infoType =  ND_DATA_XFER_MODE_AO_GR1 ;
	status = Get_DAQ_Device_Info (DEVICE_AT_MIO_16, infoType, &infoVal) ;
	if (infoVal == 19600 && SHOW_INFO) {
		console.writeln("ND_DATA_XFER_MODE_AO ist ND_INTERRUPTS ");
	} else { 
		console.writeln("Keine getriggerte Pulsausgabe möglich !!");
		throw exception;     
	}


	infoType = ND_INTERRUPT_A_LEVEL;
	status = Get_DAQ_Device_Info (DEVICE_AT_MIO_16, infoType, &infoVal) ;
	console.writeln("ND_INTERRUPT_A_LEVEL =10");
	if (infoVal > 0){
		console.writeln("ND_INTERRUPT_A_LEVEL = %d", infoVal);
	} else {
		console.writeln("Kein Interrupt A !!");
		throw exception;
	}

	infoType = ND_DMA_A_LEVEL ;
	status = Get_DAQ_Device_Info (DEVICE_AT_MIO_16, infoType, &infoVal) ;
	if (infoVal > 0) {
		console.writeln("DMA KANAL 1 ist 6 ");
	} else {
		console.writeln("Kein DMA KANAL !!");
		throw exception;
	}      
	

	infoType = ND_DMA_B_LEVEL ;
	status = Get_DAQ_Device_Info (DEVICE_AT_MIO_16, infoType, &infoVal) ;
	if (infoVal > 0){
		console.writeln("DMA KANAL 2 ist 7 ");
	} else {
		console.writeln("Kein DMA KANAL !!");
		throw exception;
	}

}
