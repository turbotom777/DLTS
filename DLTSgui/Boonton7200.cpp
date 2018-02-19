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

// for some reason the communication over IEEE-488 does not work!
#define BOONTON_IS_DAMAGED false

//////////////////////////////////////////////////////////////////////


CBoonton7200::CBoonton7200()
{
	// -1 device not set!
	m_device = -1;
	// range not set!
	m_rangeMultiplier = 1;
}

CBoonton7200::~CBoonton7200()
{
	AfxGetApp()->WriteProfileInt("DLTS Settings", "boonton range", m_rangeMultiplier);
	ibonl (m_device,0);	
}

void CBoonton7200::initDevice()
{
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	try {
	// find gpib 
		CString gpib_index;
		gpib_index.Format("gpib%d", GPIB0);
		int board = ibfind(gpib_index);
		if (board < 0) {
			gpiberr("Ibfind Error");
		}


		// Create a unit descriptor handle 
		m_device = ibdev (GPIB0,	// Board Index (GPIB0 = 0, GPIB1 = 1, ...) 
						  PRIMARY_ADDRESS_18,	// Device primary address 
						  NO_SAD,			// Device secondary address
						  T10s,				// Timeout setting (T10s = 10 seconds)  
						  1,				// Assert EOI line at end of write
						  0);				// EOS termination mode 

		ibclr(m_device);
		if (ibsta & ERR) gpiberr("ibclr Error");

		_ibwrt("PG(9)");	// programm 9 :Testspannung 15 mV EOI Character 
		//_ibwrt("RE");		// recall front panel setup from program location
		_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
		
		// TODO: check if necessar!?
		_ibwrt("SP(12)");	// special function 12
		_ibwrt("CP");		// clear errors and disable bias sweep

		m_rangeMultiplier = AfxGetApp()->GetProfileInt("DLTS Settings", "boonton range", 100);
		SetRange();
	} catch (...){
		console.writeln("Error while initDevice");
		
	}
}


void CBoonton7200::setRangeMultiplier(int multiplier){
	m_rangeMultiplier = multiplier;
	if (BOONTON_IS_DAMAGED) {
		return;
	}	
	try {
		SetRange();
	} catch (...){
		console.writeln("Error while initDevice");
	}
}

int CBoonton7200::getRangeMultiplier(){
	return m_rangeMultiplier;
}


void CBoonton7200::initC_U()
{
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	if (m_device < 0){
		initDevice();
	}

	_ibwrt("SP(15)");	// Special function 15
	_ibwrt("CP");		// clear errors and disable bias sweep
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	this->SetRange();
}



void CBoonton7200::checkStatus()
{
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	const int MAX_BUF = 256;
	char buf[MAX_BUF];
	for (int i = 0; i < MAX_BUF; i++){
		buf[i] = 0x0;
	}
	int count = _ibrd(buf, MAX_BUF);
	
	CString status = CString(buf);
	status.TrimRight();
	if (status == "0"){
		console.writeln("Status of BOONTON is OK!");
	} else {
		console.writeln("BOONTON error Nb " +  status + "; Please check the BOONTON manual! Will exit.");
		CHardwareException exception;
		throw exception;
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
	m_rangeMultiplier = 1;
	console.writeln("Set range to 2pF");
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	_ibwrt("SP(12)");	// Special function 12 
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange20pF()
{
	m_rangeMultiplier = 10;
	console.writeln("Set range to 20pF");
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	_ibwrt("SP(13)");	// Special function 13
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange200pF()
{
	m_rangeMultiplier = 100;
	console.writeln("Set range to 200pF");
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	_ibwrt("SP(14)");	// Special function 14
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}

void CBoonton7200::setRange2000pF()
{	
	m_rangeMultiplier = 1000;
	console.writeln("Set range to 2000pF");
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	_ibwrt("SP(15)");	// Special function 15
	_ibwrt("CP");		// capacitance parallel
	_ibwrt("TS");		// set talk mode to talk status byte; TS frägt Status von Boonton ab.
	checkStatus();
}


double CBoonton7200::getCapacitance(double U)
{
	//double U_abs = fabs(U); // because of negativ capacitance
	return m_rangeMultiplier * U; //m_rangeMultiplier * U_abs;
}


void CBoonton7200::setPulse(float baseVoltage, float pulseVoltage){
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	
	CString cmd;
	/* appr. 28ms pulse
	cmd.Format("BI %f VO %f VO %f VO",baseVoltage, pulseVoltage, baseVoltage);
	_ibwrt(cmd.GetBuffer(cmd.GetLength()));
	*/

	// appr. 15 ms
	cmd.Format("BI %f VO BO",baseVoltage);
	_ibwrt(cmd.GetBuffer(cmd.GetLength()));
	cmd.Format("WT BI %f VO",pulseVoltage);
	_ibwrt(cmd.GetBuffer(cmd.GetLength()));
	cmd.Format("TR %f VO IM",baseVoltage);
	_ibwrt(cmd.GetBuffer(cmd.GetLength()));
}

void CBoonton7200::setBaseVoltage(float baseVoltage){
	CString cmd;
	cmd.Format("BI %f VO BO", baseVoltage);
	_ibwrt(cmd.GetBuffer(cmd.GetLength()));
}

void CBoonton7200::SetZero()
{	
	if (BOONTON_IS_DAMAGED) {
		return;
	}
	_ibwrt("ZR");
}

void CBoonton7200::SetRange()
{
	if (m_rangeMultiplier == 1){
		setRange2pF();
	} else if (m_rangeMultiplier == 10){
		setRange20pF();
	} else if (m_rangeMultiplier == 100){
		setRange200pF();
	} else if (m_rangeMultiplier == 1000){
		setRange2000pF();
	} 
}

bool CBoonton7200::IsInRange(float capacitance)
{
	return (fabs(capacitance) <= m_rangeMultiplier * 2);
}
