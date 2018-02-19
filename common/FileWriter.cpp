// FileWriter.cpp: implementation of the CFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define PATH "c:/dlts/data/"

CFileWriter::CFileWriter(CString label)
{
	// open write/create mode

	
	CFile dir;
	CTime time;
	time = time.GetCurrentTime();
	

	int year = time.GetYear();
	int month = time.GetMonth();
	int day = time.GetDay();

	// for some reason, it doesnt work to create a directory with date!
	// -> set date as prefix on fileName.
	CString strDir;
	CString root = PATH;
	int hour = time.GetHour();
	int min = time.GetMinute();
	strDir.Format("%s/%0.4d%0.2d%0.2d_%0.2d%0.2d", root, year, month, day, hour, min);
	//CreateDirectory(strDir, NULL);


	CString strFile;
	strFile.Format("%s_%s.dat", strDir, label);
	
	int exits = m_file.Open(strFile, CFile::modeWrite | CFile::modeCreate);
}

CFileWriter::~CFileWriter()
{
	CFileStatus status;
	if (!m_file.GetStatus(status)){
		return;
	}
	m_file.Close();
}




void CFileWriter::writeln(CString str)
{
	str = str + "\r\n";
	write(str);
}

void CFileWriter::write(CString str)
{
	CFileStatus status;
	if (!m_file.GetStatus(status)){
		return;
	}
	m_file.Write(str.GetBuffer(str.GetLength()), str.GetLength());
}
