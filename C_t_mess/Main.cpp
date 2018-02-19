#include "stdafx.h"
#include "DataHandler.h"
#include "Card.h"
#include "IOCard.h"
#include "C_t_mess.h"
#include "conio.h"




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
		// TODO: code your application's behavior here.
		console.writeln("DLTS Messsoftware Version 0.1");
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

		C_t_mess ctMess;
		int pulsWidth = 200;
		int delay = 20;
		int numberOfAveraging = 1;
		int gain = 1; // possible: 1, 10, 100, 500
		float reverseVoltage = -6.0f;
		ctMess.init(pulsWidth, delay, numberOfAveraging, gain, reverseVoltage);
		ctMess.start();
	}

	return nRetCode;
}