// Log.cpp: implementation of the Log class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Log.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Log::Log()
{

}

Log::~Log()
{

}

static void Log::writeln(CString msg){
	console.writeln(msg);
}


void Log::writeln(CString msg, int value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void Log::writeln(CString msg, unsigned long value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void Log::writeln(CString msg, float value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void Log::writeln(CString msg, double value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}
