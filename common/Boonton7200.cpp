// Booton7200.cpp: implementation of the Booton7200 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Boonton7200.h"
#include "Decl-32.h"
#include "math.h"
#include "HardwareException.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// hardware constants
// change if hardware has changed!

// boonton is connected to gpib0!
const static int GPIB_BOARD_INDEX = 0;
// primary address of boonton is 18
const static int PRIMARY_ADDRESS = 18;


CBoonton7200::CBoonton7200()
{
	// -1 device not set!
	m_device = -1;
	// range not set!
	m_rangeMultiplier = -1;
}

CBoonton7200::~CBoonton7200()
{
	ibonl (m_device,0);	
}

void CBoonton7200::initDevice()
{
	// find gpib 
	CString gpib_index;
	gpib_index.Format("gpib%d", GPIB_BOARD_INDEX);
	int board = ibfind(gpib_index);
	if (board < 0) {
		gpiberr("Ibfind Error");
	}


	// Create a unit descriptor handle 
	m_device = ibdev (GPIB_BOARD_INDEX,	// Board Index (GPIB0 = 0, GPIB1 = 1, ...) 
					  PRIMARY_ADDRESS,	// Device primary address 
					  NO_SAD,			// Device secondary address
					  T10s,				// Timeout setting (T10s = 10 seconds)  
					  1,				// Assert EOI line at end of write
					  0);				// EOS termination mode 

	ibclr(m_device);
	if (ibsta & ERR) gpiberr("ibclr Error");

//	_ibwrt("PG(9)");	// programm 9 :Testspannung 15 mV EOI Character 
	_ibwrt("RE");		// recall front panel setup from program location
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	
	// TODO: check if necessar!?
	_ibwrt("SP(12)");	// special function 12
	_ibwrt("CP");		// clear errors and disable bias sweep
}


void CBoonton7200::initC_U()
{
	if (m_device < 0){
		initDevice();
	}

	_ibwrt("SP(15)");	// Special function 15
	_ibwrt("CP");		// clear errors and disable bias sweep
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	setRange2000pF();
}



void CBoonton7200::checkStatus()
{
	const int MAX_BUF = 256;
	char buf[MAX_BUF];
	for (int i = 0; i < MAX_BUF; i++){
		buf[i] = 0x0;
	}
	_ibrd(buf, MAX_BUF);
	
	CString status = CString(buf);
	status.TrimRight();

	if (status == "0"){
		console.writeln("Status of BOONTON is OK!");
	} else {
		console.writeln("BOONTON error Nb " +  status + "; Please check the BOONTON manual! Will exit.");
		return;
	}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////
// helper
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CBoonton7200::_ibwrt( char cmd[]) 
{
	int result = ibwrt (m_device, cmd, strlen(cmd));              /*write data to a device from a user buffer*/	
    if (ibsta & ERR){
		 gpiberr("Ibwrt Error");
	}
	return result;
}


int CBoonton7200::_ibrd( char cmd[], int maxLen) 
{
	return ibrd (m_device, cmd, maxLen);              /*read data from a device to a user buffer*/	
}



void CBoonton7200::gpiberr(CString msg){

    console.writeln(msg);
	CString error; 
	error.Format("ibsta = %d", ibsta );

	console.writeln(error);
 
    if ((ibsta & ERR) != 0) console.writeln("ERR");
    if ((ibsta & TIMO) != 0) console.writeln("TIMO");
    if ((ibsta & END) != 0) console.writeln("END");
    if ((ibsta & SRQI) != 0) console.writeln("SRQI");
    if ((ibsta & RQS) != 0) console.writeln("RQS");
    if ((ibsta & CMPL) != 0) console.writeln("CMPL");
    if ((ibsta & LOK) != 0) console.writeln("LOK");
    if ((ibsta & REM) != 0) console.writeln("REM");
    if ((ibsta & CIC) != 0) console.writeln("CIC");
	if ((ibsta & ATN) != 0) console.writeln("ATN");
	if ((ibsta & TACS) != 0) console.writeln("TACS");
	if ((ibsta & LACS) != 0) console.writeln("LACS");
	if ((ibsta & DTAS) != 0) console.writeln("DTAS");
	if ((ibsta & DCAS) != 0) console.writeln("DCAS");

	CString err;
	err.Format("iberr=%d", iberr);
    ::console.writeln(err);
	if ((iberr & EDVR) != 0) console.writeln("EDVR <DOS Error>");
	if ((iberr & ECIC) != 0) console.writeln("ECIC <Not CIC>");
	if ((iberr & ENOL) != 0) console.writeln("ENOL <No Listener>");
	if ((iberr & EADR) != 0) console.writeln("EADR <Address error>");
	if ((iberr & EARG) != 0) console.writeln("EARG <Invalid argument>");
	if ((iberr & ESAC) != 0) console.writeln("ESAC <Not Sys Ctrlr>");
	if ((iberr & EABO) != 0) console.writeln("EABO <Op. aborted>");
	if ((iberr & ENEB) != 0) console.writeln("ENEB <No GPIB board>");
	if ((iberr & EOIP) != 0) console.writeln("EOIP <Async I/O in prg>");
	if ((iberr & ECAP) != 0) console.writeln("ECAP <No capability>");
	if ((iberr & EFSO) != 0) console.writeln("EFSO <File sys. error>");
	if ((iberr & EBUS) != 0) console.writeln("EBUS <Command error>");
	if ((iberr & ESTB) != 0) console.writeln("ESTB <Status byte lost>");
	if ((iberr & ESRQ) != 0) console.writeln("ESRQ <SRQ stuck on>");
	if ((iberr & ETAB) != 0) console.writeln("ETAB <Table Overflow>");
	
	CString cntl;
	cntl.Format("ibcntl=%d", ibcntl);
    console.writeln(cntl);

	CHardwareException exception;
	throw exception;	
}


void CBoonton7200::setRange2pF()
{
	if (m_rangeMultiplier == 1){
		return;
	}
	m_rangeMultiplier = 1;
	console.writeln("Set range to 2pF");
	_ibwrt("SP(12)");	// Special function 12 
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange20pF()
{
	if (m_rangeMultiplier == 10) {
		return;
	}

	m_rangeMultiplier = 10;
	console.writeln("Set range to 20pF");
	_ibwrt("SP(13)");	// Special function 13
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange200pF()
{
	if (m_rangeMultiplier == 100) {
		return;
	}

	m_rangeMultiplier = 100;
	console.writeln("Set range to 200pF");
	_ibwrt("SP(14)");	// Special function 14
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange2000pF()
{	
	if (m_rangeMultiplier == 1000) {
		return;
	}
	m_rangeMultiplier = 1000;
	console.writeln("Set range to 2000pF");
	_ibwrt("SP(15)");	// Special function 15
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}


double CBoonton7200::getCapacitance(double U)
{
	double U_abs = fabs(U); // because of negativ capacitance


	// if U_abs > 2 V, the messurement is dirty!
	if (U_abs > 2.0){
		setRange2000pF();
		Sleep(1000);
		return -1;
	}

	double capacitance = m_rangeMultiplier * U_abs; //m_rangeMultiplier * U_abs;



	return capacitance;	
}
