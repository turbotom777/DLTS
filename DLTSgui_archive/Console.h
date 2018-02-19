// Console.h: interface for the CConsole class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONSOLE_H__DFEB68C9_3DF2_4E69_9EB4_B946A287C580__INCLUDED_)
#define AFX_CONSOLE_H__DFEB68C9_3DF2_4E69_9EB4_B946A287C580__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "sizecbar.h"

class CConsole : public CSizingControlBar  
{
public:
	void AddText(CString text, bool bScroll);
	CConsole();
	virtual ~CConsole();

protected:
	CRichEditCtrl* m_edit;

	//{{AFX_MSG(CConsole)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

#endif // !defined(AFX_CONSOLE_H__DFEB68C9_3DF2_4E69_9EB4_B946A287C580__INCLUDED_)
