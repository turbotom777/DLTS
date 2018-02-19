// BufferedFileWriter.cpp: implementation of the CBufferedFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileWriter.h"
#include "BufferedFileWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBufferedFileWriter::CBufferedFileWriter(CString label)
	:CFileWriter(label)
{
	m_pos = NULL;
}

CBufferedFileWriter::~CBufferedFileWriter(){
	POSITION pos = m_lineList.GetHeadPosition();
	CString line;
	while (pos != NULL){
		line = m_lineList.GetNext(pos);
		writeln(line);
	}
}

void CBufferedFileWriter::appendLine(CString & append)
{
	if (m_pos != NULL){	
		CString line = m_lineList.GetAt(m_pos);
		line += append;
		m_lineList.SetAt(m_pos, line);	
		m_lineList.GetNext(m_pos);
		return;
	}
	CString newLine;
	newLine += append;
	m_pos = m_lineList.AddTail(newLine);
	m_lineList.GetNext(m_pos);
}

void CBufferedFileWriter::resetLineIndex(){
	m_pos = m_lineList.GetHeadPosition();
}