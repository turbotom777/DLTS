// C_U_mess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "C_U_mess.h"


#include "Boonton7200.h"
#include "FileWriter.h"
#include "math.h"
#include "wdaq_c.h"
#include "conio.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// The one and only application object
CWinApp theApp;
CWriter console;


void writeln(CString msg){
	console.writeln(msg);
}
void write(CString msg){
	console.write(msg);
}


void start(CString name);

using namespace std;

// windows main methode. 
// This is the startpoint of the application
int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// TODO: code your application's behavior here.
		writeln("DLTS Messsoftware Version 0.1");
		writeln("Copyright 2005 T. Schwaiger");

		console.writeln("");
		console.writeln("Please press 'c' to terminate program while execution!");
		console.writeln("Please do NOT stop execution with key 'CRTL + c'!");
		console.writeln("Please insert a name for the specimen and press ENTER to start the program");

		CString probe;
		cin >> probe.GetBuffer(128);
		probe.ReleaseBuffer();

		if (probe.IsEmpty()){
			console.writeln("No valid name. Will terminate program");
			return nRetCode;
		}

/*
		int ch = _getch();
		if (ch != 13){
			console.writeln("Will terminate program");
			return nRetCode;
		}
*/

		start(probe);
	}

	return nRetCode;
}


bool _abort(){
	int ch = 0;
	int hit = _kbhit();
	if (hit){
		ch = _getch();
	} 
	if (ch == 67 || ch == 99){
		console.writeln("Key 'c' pressed. Will terminate program");
		return true;
	}
	return false;
}



void start(CString name)
{
	CBoonton7200 boonton;	
	CString label = name + "_C_U";
	CFileWriter fileWriter(label);
	fileWriter.writeln("Messpunkt, U, C, 1/(C**2)");
	const int MESSURING_POINT_DISTANCE = 1;


	// TODO: insert by user interaction
	double U_reverse_max = 6;
	double U_REVERSE_STEP = 0.05;

	// init boonton7200
	boonton.initC_U();

	int status = 0;
	double U_reverse = 0;
	int	index = 0;
	while ( U_reverse < U_reverse_max && status == 0 ) 
	{ 
    
		//begin output of voltage
		status = AO_VWrite(1,0,U_reverse); // Reverse_voltage (Sperrspannung)
		int count = 0;
		if (status != 0)
		{
			return;
		}

		Sleep(100);
		
		
		double U_C_average = 0;
		const int MAX_NUMBER = 1000;

		// average value for capacitance 
		for (int n = 0; n < MAX_NUMBER; n++)
		{
			// messurement of capacitance
			double U_C;		
			// read capacitance from io card provided by boonton (as voltage).
			status = AI_VRead(1,0,1,&U_C);
			if (status != 0)
			{
				// TODO: Error handling
				return;
			}

			U_C_average += U_C;
			// End messurement of capacitance
		}
		U_C_average = U_C_average/MAX_NUMBER;

		
		double capacitance =  boonton.getCapacitance(U_C_average); 
		if (capacitance < 0){
			writeln("Falscher Messbereich eingestellt. Wert ist ungueltig!");
			continue;
		}

		
		// begin calculation
		double C_sqrt = sqrt(capacitance);
		if ( C_sqrt < 1e-10) 
		{
			C_sqrt = 1e-10; // Do not divide by 0
		}

		double oneByC_sqrt = 1/C_sqrt; // set C_sqrt to 1e-10 if it is 0 !! *)


		// store each n (=MESSURING_POINT_DISTANCE) times
		if (index % MESSURING_POINT_DISTANCE == 0)
		{
			CString msg;
			msg.Format("U_r %f V, U_c %f V, C %f pF, Messpunkt=%d, 1/C= %f",U_reverse, fabs(U_C_average), capacitance, index, oneByC_sqrt);
			writeln(msg);

			CString rowSet;
			rowSet.Format("%d, %f, %f, %f", index, U_reverse, capacitance, oneByC_sqrt);
			fileWriter.writeln(rowSet);

			
			// TODO: write to file!
			//writeln(C_U_DAT,Spannung:6:2,U_Boonton:8:4,' ',Kapazitaet:8:4,' ',c_quadrat:8:1,'  ',Einsdurch:10:8,Bereich:6);

			/*
			cu.spannung = spannung;
			cu.einsdurch = Einsdurch;

			write(cu_dat,cu);
			*/
		}

		U_reverse = U_reverse + U_REVERSE_STEP;
		index++;

		_abort();

	} 

	// check for errors
	CString msg;
	msg.Format("Der Wert der Variablen Status=%d ", status);
	writeln(msg);
	status = AO_VWrite(1,0,0);

	if (status != 0 )
	{
		CString msg;
		msg.Format("Der Wert der Variablen Status=%d ", status);
		writeln(msg);
	}

}



