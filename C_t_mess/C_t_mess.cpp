// C_t_mess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "DataHandler.h"
#include "Boonton7200.h"
#include "math.h"
#include "wdaq_c.h"
#include "Satz_typ.h"
#include "math.h"
#include "nidaqcns.h"
#include "BufferedFileWriter.h"
#include "Card.h"
#include "IOCard.h"
#include "TimerCard.h"
#include "ComHandler.h"
#include "FileWriter.h"
#include "tempcontroller.h"
#include "conio.h"
#include "hardwareException.h"
#include "C_t_mess.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




/////////////////////////////////////////////////////////////////////////////
// The one and only application object



#define FILL_PULSE_VOLTAGE -1.0f
#define MAX_DRIFT_DIFFERENCE 100  // (*Volt=Driftdifferenz/2048*1 Volt = 48 millivolt *)
#define SAMPLE_INTERVAL 10 	// interval of each new sample: timebase * SAMPLE_INTERVAL z.B. 1µs * 10 = 10µs

//const long speichermax = 131080;
using namespace std;


void C_t_mess::init(int pulsWidth, int delay, int numberOfAveraging, int gain, float reverseVoltage){
	m_pulsWidth = pulsWidth;
	m_delay = delay;
	m_numberOfAveraging = numberOfAveraging;
	m_gain = gain;
	m_reverseVoltage = reverseVoltage;
}

bool C_t_mess::abort(){
	int ch = 0;
	int hit = _kbhit();
	if (hit){
		ch = _getch();
	} 
	if (ch == 67 || ch == 99){
		console.writeln("Key 'c' pressed. Will terminate program");
		_getch();
		return true;
	}
	return false;
}

C_t_mess::C_t_mess(){
	m_pulsWidth = 200;
	m_delay = 10;
	m_numberOfAveraging = 1;
	m_gain = 10;
	m_reverseVoltage = -6.0f;
}



void C_t_mess::start()
{
	try {
		CBufferedFileWriter fileWriter("C_t");
		int status;

		CBoonton7200 boonton;
		IOCard ioCard;
		
		DataHandler dataHandler;
		TempController tempController;

		// init boonton7200
		boonton.initC_U();
		boonton.setRange200pF();

		// init at-mio-16 for C/t messuring
		ioCard.initC_t();
		ioCard._DAQ_Clear();
		
	// init memory for DAQ
		dataHandler.initMemory();

	// init pc-tio-10 for C/t messuring
		
 
		short dataArray[RESULT_FIELD_SIZE];
		short dataArrayAverage[RESULT_FIELD_SIZE];
		double voltageArray[RESULT_FIELD_SIZE];

		while ( !abort() ) {
		// Meßschleife // Temperaturmessung*)
			float temperature = tempController.setTemperature(temperature, false);
			console.writeln(" %f °Celsius ", temperature);
			status = 0;
			
			 // begin Löschen*)
			// prepopulate arrays with 0
			int index;
			for (index = 0; index < RESULT_FIELD_SIZE; index++){ 
				dataArray[index] = 0;
				voltageArray[index] = 0;
				dataArrayAverage[index] = 0;
			}

			int averageCnt = 0;
			for (int averageIdx = 0; averageIdx < m_numberOfAveraging; averageIdx++ ) {
				// begin Pulsausgabe*)
				
				int driftAverageNb = 100;
				int drift1 = ioCard.getDrift(driftAverageNb, m_gain);
				double driftVoltage = 0.0;
				status = ioCard._AI_VScale(m_gain, drift1, driftVoltage);
				console.writeln("%f Drift I Volt:", driftVoltage);


				ioCard.checkDAQFinished();

				// FÜLLIMPULS*)
				// fillpulse will be set with timer1 on low first time.
				// used to be positiv?!
				ioCard._AO_Configure(0);
				Sleep(100);
				ioCard._AO_VWrite(FILL_PULSE_VOLTAGE);
				
				
				//ioCard._AO_Configure(2);
				//Sleep(100);
				status = ioCard._DAQ_Clear();
				//status = timerCard._CTR_Reset();
				//timerCard._CRT_Pulse(m_pulsWidth, m_delay);
                                                   
				
				// start dataHandler aquisition  and store input in an array.
				// data aquisition will start with timer2 on low.
				ioCard._DAQ_Start(m_gain, TIMEBASE_INDEX , SAMPLE_INTERVAL, dataHandler);
				// the duration of the fillpulse is dependent on the duration of the programm here.
				
				const int performOnStart = 2;		// 2: perform simultanous start/restart on counters...
				//timerCard._CTR_Simul_Op(performOnStart);
				
				
				// reverseVoltage will be set with timer1 on low second time!
				// used to be negative
				if (m_reverseVoltage > 0) {
					console.writeln("Warnung: Sperrspannung ist positiv!", averageIdx);
				}
				ioCard._AO_VWrite(m_reverseVoltage);

				// check if data aquisition on card has finished!
				ioCard.checkDAQFinished();

				// stop timers
				const int performOnStop = 3;
				

				status = ioCard._DAQ_Clear();
				int drift2 = ioCard.getDrift(driftAverageNb, m_gain);
				status = ioCard._AI_VScale(m_gain, drift2, driftVoltage);
				console.writeln("%f Drift II Volt:", driftVoltage);

				// ceil: round up to a valid integer/long!
				// TODO: find better solution!
				int nullbalance = ceil((double) ((drift1)+(drift2))/2);

				int driftDifference = abs(drift1- drift2);
				if (  driftDifference < MAX_DRIFT_DIFFERENCE )  //Entsprechend XYZ pF*)
				{ //store)

					dataHandler.copyData(dataArray, nullbalance);
					console.writeln("Mittelung Nr. %d", averageIdx);

					// TODO: this doesnt work!!!!
					for (int i = 0; i < RESULT_FIELD_SIZE; i++){
						if (averageCnt == 0){
							dataArrayAverage[i] = dataArray[i];
						} else {	
							// add new value to average value and divide by 2.
							dataArrayAverage[i] =(int) ceil((double) (dataArrayAverage[i] + dataArray[i]) / 2);
						}
					}
					averageCnt++;
				}
				//end(*Speicherung*)
				else {
					console.writeln("Diese Messung wird nicht gespeichert !   Differenz ist zu groß: " + driftDifference);
					continue;
				}			
			}
			//end;(*Pulsausgabe*)

			if (averageCnt == m_numberOfAveraging){
				console.writeln(" %d Mittelungen ausgefuehrt.", averageIdx);
			} else {
				console.writeln("Messung wird nicht gespeichert!");
				continue;
			}


			status = DAQ_VScale (ioCard.getDevice(), ioCard.getInputChannel(), m_gain, 1, 0, RESULT_FIELD_SIZE, dataArrayAverage, voltageArray);
			if (status != 0){	 
				console.writeln ("DAQ_VScale  FEHLER NUMMER %d", status);
			}

			CString strValue;
			strValue.Format("%3.2f,", temperature);
			fileWriter.appendLine(strValue);
			for (int k = 0; k < RESULT_FIELD_SIZE; k++){	
				double value = voltageArray[k];
				CString strValue;
				strValue.Format("%2.10f,", value);
				fileWriter.appendLine(strValue);
			}
			fileWriter.resetLineIndex();
			console.writeln("Status %d", status);

			ioCard._DAQ_Clear();

			
		// end;(*ENDE Meßschleife*)
		}

	//  TODO:
		//close(MessdataHandler);
		const int cancelReservation = 0;		// 0: cancel reservation for counters in list
		//timerCard._CTR_Simul_Op(cancelReservation);

		ioCard._DAQ_Clear();
		
		const int directUpdate = 1;	// 1: update on call of AO_Update
		status = ioCard._AO_Configure(directUpdate);
    
		//0 Volt werden zu DAC 0 geschrieben*)
		ioCard._AO_VWrite(0.0);
		status = AO_Update (ioCard.getDevice());
		console.writeln("%d", status);

		                   // Zähler 1 auf Tristate    *)
		console.writeln("%d Status CTR_Reset  1 ", status);

		short outState = 0;
		
		
		if (outState != 1){
			console.writeln("Zähler Nummer 1 ist nicht Tristate ! Ausgangsstatus= %d", outState);
		}

	} catch (CHardwareException exception){
		console.writeln("An Hardware Exception occured");
	}

}








