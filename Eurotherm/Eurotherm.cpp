// Eurotherm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Eurotherm.h"
#include "ComHandler.h"
#include "FileWriter.h"
#include ".\tempcontroller.h"
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



using namespace std;

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

		console.writeln("DLTS Messsoftware / Temperatursteuerung Version 0.1");
		console.writeln("Copyright 2005 T. Schwaiger");

		console.writeln("");
		console.writeln("Please press 'c' to terminate program while execution!");
		console.writeln("Please do NOT stop execution with key 'CRTL + c'!");
		console.writeln("Please press ENTER to start the program");

		int ch = _getch();
		if (ch != 13){
			console.writeln("Will terminate program");
			return nRetCode;
		}


		TempController tempController;
		int TStart = 25;
		int TEnd = 35;
		int TStep = 10;
		int THold = 20; // sec
		tempController.start(TStart, TEnd, TStep, THold);
		console.writeln("Please press any key to close window");
		_getch();

	}

	return nRetCode;
}



