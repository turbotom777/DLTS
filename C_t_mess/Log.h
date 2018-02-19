// Log.h: interface for the Log class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__D5330AE1_E4A1_11D9_8F79_00E0290686A0__INCLUDED_)
#define AFX_LOG_H__D5330AE1_E4A1_11D9_8F79_00E0290686A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Log  
{
public:
	Log();
	virtual ~Log();


	void writeln(CString msg);
	void writeln(CString msg, int value);
	void writeln(CString msg, unsigned long value);
	void writeln(CString msg, float value);
	void writeln(CString msg, double value);


};

#endif // !defined(AFX_LOG_H__D5330AE1_E4A1_11D9_8F79_00E0290686A0__INCLUDED_)
