// StringBuffer.h: interface for the StringBuffer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRINGBUFFER_H__49C9DBEB_EBE3_4BBA_B2F3_541424284A04__INCLUDED_)
#define AFX_STRINGBUFFER_H__49C9DBEB_EBE3_4BBA_B2F3_541424284A04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class StringTokenizer  
{
public:
	StringTokenizer(CString content, char delimiter);
	virtual ~StringTokenizer();

	bool hasMoreTokens();
	CString nextToken();
	int countTokens();

private:
	CStringList m_tokenList;
	int tokenCount;

	void parseContent(CString content, char delimiter);

};

#endif // !defined(AFX_STRINGBUFFER_H__49C9DBEB_EBE3_4BBA_B2F3_541424284A04__INCLUDED_)
