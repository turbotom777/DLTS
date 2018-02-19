// Log.h: interface for the Log class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__20AEEF0E_3222_4502_B2B3_CC09E1C9A2E4__INCLUDED_)
#define AFX_LOG_H__20AEEF0E_3222_4502_B2B3_CC09E1C9A2E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame;

class CWriter  
{
public:
	CWriter();
	virtual ~CWriter();
	void write(CString out);
	void setPath(CString path);
	void setMainWnd(CMainFrame* wnd);
	

	void writeln(CString msg);
	void writeln(CString msg, int value);
	void writeln(CString msg, unsigned long value);
	void writeln(CString msg, float value);
	void writeln(CString msg, double value);


protected:
	CFile *file;
	CMainFrame* m_mainWnd;
};

#endif // !defined(AFX_LOG_H__20AEEF0E_3222_4502_B2B3_CC09E1C9A2E4__INCLUDED_)
