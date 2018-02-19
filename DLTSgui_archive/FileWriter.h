// FileWriter.h: interface for the CFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEWRITER_H__1B542BE1_B24C_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_FILEWRITER_H__1B542BE1_B24C_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileWriter  
{
public:
	void writeln(CString str);
	void write(CString str);
	CFileWriter(CString label);

	virtual ~CFileWriter();

protected:
	CFile m_file;
};

#endif // !defined(AFX_FILEWRITER_H__1B542BE1_B24C_11D9_8F79_00E0290686A0__INCLUDED_)
