// BufferedFileWriter.h: interface for the CBufferedFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUFFEREDFILEWRITER_H__3BFF1E61_2126_11DA_AB29_00E0290686A0__INCLUDED_)
#define AFX_BUFFEREDFILEWRITER_H__3BFF1E61_2126_11DA_AB29_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FileWriter.h"

class CBufferedFileWriter : public CFileWriter  
{
public:
	void appendLine(CString & append);
	CBufferedFileWriter(CString label);
	virtual ~CBufferedFileWriter();
	void resetLineIndex();

protected:
	CList <CString, CString&> m_lineList;
	POSITION m_pos;
};

#endif // !defined(AFX_BUFFEREDFILEWRITER_H__3BFF1E61_2126_11DA_AB29_00E0290686A0__INCLUDED_)
