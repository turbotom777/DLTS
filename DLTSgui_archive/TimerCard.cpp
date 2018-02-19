#include "stdafx.h"
#include "Card.h"
#include "TimerCard.h"
#include "wdaq_c.h"
#include "nidaqcns.h"
#include ".\timercard.h"

const static int DEVICE_PC_TIO_10 = 2;
const static int NUMBER_OF_COUNTER = 2;


TimerCard::TimerCard(void)
{
	m_counter1 = 1;
	m_counter2 = 2;
	m_counterList[0] = m_counter1;
	m_counterList[1] = m_counter2;
	m_device = DEVICE_PC_TIO_10;
}

TimerCard::~TimerCard(void)
{
}


void TimerCard::initC_t(void)
{
	const int edgeModeRise = 0;		// 0: count rising edge
									// 1: count falling edge

	const int gateModeNone = 0;		// 0: no gating used

	const int outTypeToggle = 0;	// 0: TC toggled output
	const int outTypePulse = 1;		// 1: TC pulse output

	const int outPolarityNegative = 1;		// 0: positive logic output
									// 1: negative logic output (inverted)

	
	int status = CTR_Stop (m_device, m_counter1);			// suspend operation of specified counter!
	if (status != 0) {
		console.writeln("Fehler bei CTR_Stop1 NUMMER %d", status);
	}
	status = CTR_Stop (m_device, m_counter2);			// suspend operation of specified counter!
	if (status != 0){
		console.writeln("Fehler bei CTR_Stop2 NUMMER %d", status);
	}

	status = CTR_Config (m_device, m_counter1, edgeModeRise, gateModeNone, outTypePulse, outPolarityNegative);          
																// Festlegen von Z‰hler 1 *)
																// Trigger durch 0 auf  1 *)
																// Start durch Programm   *)
																// Ausgabe einer Flanke_/---*)
																// Invertiert d.h.-5 volt *)
	if (status != 0){
		console.writeln("Fehler bei CTR_Configure 1 NUMMER %d", status);
	}

	status = CTR_Config (m_device, m_counter2, edgeModeRise, gateModeNone, outTypePulse, outPolarityNegative);              // Festlegen von Z‰hler 2*)
	if (status != 0){
	   console.writeln("Fehler bei CTR_Configure 5 NUMMER %d", status);
	}
	

	const int modeReserve = 1;		// 0: cancel reservation for counters in list
									// 1: reserve counters in list for simulanous start, restart, stop, ....
									// 2: perform simultanous start/restart on counters...
									// 3: perform simultanous stop

	status = CTR_Simul_Op (m_device, NUMBER_OF_COUNTER, m_counterList, modeReserve);      
															// Gleichzeitiger Start    *)
															// von 2 Z‰hlern definiert *)       
															// in dem Feld ctrList     *)
															// RESERVIEREN =1         *)

	if (status != 0) {
	   console.writeln("Fehler bei CTR Simult Op  1  NUMMER  %d ", status);
	}

	_CTR_Reset();

}

int TimerCard::_CTR_Reset(void)
{
	const int output = 2;			// 0: high impedance
									// 1: low logic out
									// 2: high logic out

	int status = CTR_Reset (m_device, m_counter1, output);                    //Z‰hler 1 auf HIGH       *)
	if (status != 0)
	{
		console.writeln ("CTR_Reset 1 FEHLER NUMMER %d", status);
		return status;
	}

	status = CTR_Reset (m_device, m_counter2, output);                    // Z‰hler 2 auf HIGH       *)
	if (status != 0) 
	{
		console.writeln ("CTR_Reset  5 FEHLER NUMMER %d", status);
		return status;
	}
	return status;
}

int TimerCard::_CRT_Pulse(int pulseWidth, int delay)
{

	int delayCounter1 = 10;
	int status = CTR_Pulse (m_device, m_counter1, TIMEBASE_INDEX, delayCounter1, pulseWidth);				//Pulsausgabe Z‰hler1, Zeitbasis 1(1ys)*)
	if (status != 0)										// 10 Zeiteinheiten bis Pulsanfang     *)
	{														// "LOW" Puls,dann Pulsbreite*1ys "HIGH"*)
		console.writeln ("CTR_Pulse 1 FEHLER NUMMER %d", status);	//  Danach wieder LOW Puls mit 1ys      *)   
		return status;								// zum Schluﬂ "HIGH" Zustand   
	}                                                     
                            
	int pulseWidthCounter2 = 10;
	int delayCounter2 = delay + pulseWidth + 9;
	status = CTR_Pulse (m_device, m_counter2, TIMEBASE_INDEX, delayCounter2, pulseWidthCounter2);// Pulsausgabe Z‰hler2, Zeitbasis 1(1ys)*)
	if (status != 0) 
	{										// (VERSATZ+PULSBREITE+9)*Zeiteinheit bis Pulsanfang*)
		console.writeln ("CTR_Pulse 5 FEHLER NUMMER ",status);		// 10 Zeiteinheiten bis Pulsende       *)
		return status;										// Versatz+Pulsbreite darf nicht NEGATIV sein!!*)
	}
	return status;	
}

int TimerCard::_CTR_Simul_Op(int updateMode)
{
	int status = CTR_Simul_Op (m_device, NUMBER_OF_COUNTER, m_counterList, updateMode);      
															// Gleichzeitiger Start    *)
															// von 2 Z‰hlern definiert *)       
															// in dem Feld ctrList     *)
															// RESERVIEREN =1         *)

	if (status != 0) {
	   console.writeln("Fehler bei CTR Simult Op  1  NUMMER  %d ", status);
	}
	return status;
}

int TimerCard::getCounter1()
{
	return m_counter1;
}
