// Start.cpp: implementation of the CStart class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "C_t_mess.h"
#include "Start.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CWinApp theApp;

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

		C_t_mess ctMess;
		ctMess.start();
		//start();
	}

	return nRetCode;
}
