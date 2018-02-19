// Log.cpp: implementation of the Log class.
//
//////////////////////////////////////////////////////////////////////



#include "stdafx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


// wrapper class for writing to standard out.
// possible to write all output to file as well.



using namespace std;

CWriter::CWriter()
{
	file = NULL;
}

CWriter::~CWriter()
{
	if (file != NULL){
		file->Close();
	}
}

void CWriter::write(CString out){

	if (file != NULL){
		const char *buf = out.GetBuffer(0);
		file->Write(buf, lstrlen(buf));
	}  else {
		cout<< (LPCSTR) out;
	}
}

void CWriter::writeln(CString out){
	write(out + "\r\n");
}

void CWriter::setPath(CString path){
	file = new CFile(path, CFile::modeCreate | CFile::modeWrite  | CFile::shareDenyNone );
}

void CWriter::setMainWnd(CMainFrame* wnd){
	m_mainWnd = wnd;
}


void CWriter::writeln(CString msg, int value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void CWriter::writeln(CString msg, unsigned long value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void CWriter::writeln(CString msg, float value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

void CWriter::writeln(CString msg, double value){
	CString str;
	str.Format(msg, value);
	writeln(str);
}

