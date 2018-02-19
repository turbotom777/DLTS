#include "stdafx.h"
#include "ComHandler.h"
#include "FileWriter.h"
#include "tempcontroller.h"
#include "math.h"
#include "conio.h"
#include "DLTSdevice.h"

#define COM_2 1

static const char STX=0x2;		//start of text
static const char ETX=0x3;		// End of text
static const char EOT=0x4;		// End of Transmission
static const char ENQ=0x5;		// Enquiry
static const char ACK=0x6;		// Positive Acknowledge
static const char NAK=0x15;	// Negative Acknowledge

static const CString ADDRESS = "0000";		//' X,Y Address of unit to be interrogated ??


static const float ROOM_TEMP = 25.0f;


TempController::TempController(void)
//:m_fileWriter("T_t")
{
	m_comHandler.ComInit();
	// initialize com port (2)
	int comOpen = m_comHandler.ComOpen(COM_2, 9600, P_EVEN, S_1BIT, D_7BIT);

	CString header = "zeit, istwert, sollwert, ausgang, sollwert1";
	//m_fileWriter.writeln(header);


	CTime time;
	time = time.GetCurrentTime();
	
	int hour = time.GetHour();
	int min = time.GetMinute();
	int sec = time.GetSecond();

	m_startTimeSec = 0;
	m_startTimeSec = getCurrentTimeSec();
}

int TempController::getCurrentTimeSec(){
	CTime time;
	time = time.GetCurrentTime();
	
	int hour = time.GetHour();
	int min = time.GetMinute();
	int sec = time.GetSecond();
	return (hour * 3600) + (min * 60) + sec - m_startTimeSec;
}


TempController::~TempController(void)
{
	m_comHandler.ComExit();
	m_comHandler.ComClose(COM_2);
}


float TempController::setTemperature(float Tsetpoint, float maxDeviance, bool bWaitForTemp){
	
	float Tcurrent;
	// Sollwert an Gerät übertragen
	CString cmd = "SL";		// Sollwert 1
	CString strTsetpoint;
	strTsetpoint.Format("%3.1f", Tsetpoint);

	// Sendepaket zusammenstellen
	CString packet = STX + cmd + strTsetpoint + ETX;

	// Datenblockkontrollzeichen erzeugen
	char bcc = createBCC(packet);
	CString dataLine = EOT + ADDRESS + packet + bcc;

	// Paket senden
	this->writeData(COM_2, dataLine);

	Sleep(10);
	// Daten vom Gerät empfangen
	CString data = this->readData(COM_2);

	while (true){	
		

		
		// query 'Istwert'
		Tcurrent = this->doQuery("PV");
		CString msg = "";
		msg.Format("Istwert: %3.1f", Tcurrent);
		//console.writeln(msg);

		// query 'Sollwert'
		float sp = this->doQuery("SP");
		msg.Format("Sollwert: %3.1f", sp);
		//console.writeln(msg);

		// query 'Ausgangsleistung'
		float op = this->doQuery("OP");
		msg.Format("Ausgangsleistung: %3.1f", op);
		//console.writeln(msg);

		// query 'Sollwert1'
		float sl = this->doQuery("SL");
		msg.Format("Sollwert1: %3.1f", sl);
		//console.writeln(msg);

		int currTimeSec = getCurrentTimeSec();

		/*
		CString strLine;
		strLine.Format("%d, %3.1f, %3.1f, %3.1f, %3.1f", currTimeSec, Tcurrent, sp, op, sl);
		m_fileWriter.writeln(strLine);
		*/

		msg.Format("T: %3.1fK (%3.1f°C) >> %3.1fK (%3.1f°C) >> %3.1f%s",(273-sl), sl, (273-Tcurrent), Tcurrent, op, "%");
		console.writeln(msg);

		if (!bWaitForTemp){
			return Tcurrent;
		}


		// wait for n seconds
		// check every 100ms if Tcurrent has reached setpoint!
		for (int i = 0; i < CHECK_INTERVAL * 10; i++){
			Sleep(100);
			if (doAbort()){
				return ABORT_VALUE;
			}
			Tcurrent = this->doQuery("PV");
			float diff = Tcurrent - Tsetpoint;
			float deviance = fabs(diff);
			if ( deviance <= maxDeviance ) {
				msg.Format("Tcurr: %3.1fK (%3.1f°C)",(273-Tcurrent), Tcurrent);
				return Tcurrent;
			} 
		}
	}
	return Tcurrent;
}


float TempController::getCurrentTemperature(){
	// query 'Istwert'
	return this->doQuery("PV");
}



// TODO: improve!
bool TempController::hasTemperature(float & Tcurrent, float Tsetpoint){
	float deviance = fabs(Tcurrent - Tsetpoint);
	if ( deviance <= TEMPERATURE_DEVIANCE_MAX) {			
		// do check again. There may be an overshooting (überschwingen)
		Tcurrent = this->doQuery("PV");
		deviance = fabs(Tcurrent - Tsetpoint);
		if ( deviance <= TEMPERATURE_DEVIANCE_MAX ) {
			return true;
		} 
	}
	return false;
}


bool TempController::doAbort(){
	return CDLTSdevice::m_bAbort;
}


void TempController::start(int TStart, int TEnd, int TStep, int holdTime){
	
	int Tsetpoint = TStart;
	float Tcurrent = ERROR_VALUE;
	int startTime = getCurrentTimeSec();
	while ( Tsetpoint <= TEnd){
		Tcurrent = this->setTemperature(Tsetpoint, TEMPERATURE_DEVIANCE_MAX);
		if (Tcurrent == ABORT_VALUE){
			return;
		}
		int currHoldTime = getCurrentTimeSec() - startTime;
		if (currHoldTime >= holdTime){
			Tsetpoint += TStep;
			startTime = getCurrentTimeSec();
		}
	}
	this->setTemperature(ROOM_TEMP, false);
	return;
}


float TempController::doQuery(CString cmd){
	CString writeData = EOT + ADDRESS + cmd + ENQ;
	this->writeData(COM_2, writeData);
	Sleep(10);
	CString readData = this->readData(COM_2);
	float value = getValue(readData);
	return value;
}
			


float TempController::getValue(CString data){
	if (data.GetLength() < 9){
		return ERROR_VALUE;
	}
	CString value = data.Left(9);
	value = value.Right(6);
	CString cleaned = "";
	for (int i = 0; i < value.GetLength(); i++){
		char ch = value.GetAt(i);
		if ( (ch >= 48 && ch <=57 ) || ch == 45 || ch == 46){
			cleaned += ch;
		}
	}
	float fValue = atof(cleaned.GetBuffer(cleaned.GetLength()));
	return fValue;
}



char TempController::createBCC(CString packet)
{
	char bcc = 0x0;
	for (int i = 1; i < packet.GetLength(); i++) {
		char ch = packet.GetAt(i);
		bcc = bcc^ch;
	}
	return bcc;
}	

CString TempController::readData(int port)
{	
	bool bCheckBcc = false;
	bool bTimeout = false;
	bool bRxEnd = false;
	int retry = 0;
	CString Rx = "";
	
	char in = 0;
	while ( !bRxEnd && !bTimeout ){
		while (in != EOF){
			in = m_comHandler.ComRead(port);
			if (in != EOF){
				Rx += in;
			} 
			if (in == ETX){
				bCheckBcc = true;
			}
			if (in == ETX || in == ACK || in == NAK){
				bRxEnd = true;
			}
		}
		retry++;
		Sleep(100);
		if (retry >= 10){
			bTimeout = true;
		}
		in = 0;
	}

//                                         Rückgabekontrolle
// ---------------------------------------------------------------------------------------------------------------------------------
	bool bBccError;
	if (bCheckBcc && Rx.GetLength() > 1){
		char bcc = Rx.GetAt(Rx.GetLength() - 1);
		char bccCalc = createBCC(Rx.GetBuffer(Rx.GetLength() - 2));
		if ( bcc != bccCalc){
			bBccError = true;
		}
		// remove BCC, it may be NULL.
		Rx = Rx.Left(Rx.GetLength() - 1);
	}

	//CString msg = "Read data from com: '" + Rx + "'";
	//console.writeln(msg);
	return Rx;
}

void TempController::writeData(int port, CString data)
{
	//CString msg = "write data to com: '" + data + "'";
	//console.writeln(msg);
	if (data.GetLength() > 0){
		m_comHandler.ComWrite(COM_2, data.GetBuffer(data.GetLength() -1), data.GetLength());
	}
}

bool TempController::wait(int seconds)
{
	// wait for n seconds
	// Sleep is called in a loop, otherwise userinput is not possible in that time!
	for (int i = 0; i < seconds; i++){
		Sleep(100);

		if (doAbort()){
			return false;
		}
	}
	return true;
}

