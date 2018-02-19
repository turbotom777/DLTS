// DLTSgui.h : main header file for the DLTSGUI application
//

#if !defined(AFX_DLTSGUI_H__5CE3155B_848B_49E5_9502_D8D0E1152BFA__INCLUDED_)
#define AFX_DLTSGUI_H__5CE3155B_848B_49E5_9502_D8D0E1152BFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDLTSguiApp:
// See DLTSgui.cpp for the implementation of this class
//

class CDLTSguiApp : public CWinApp
{
public:
	CDLTSguiApp();
	CDLTSdevice *m_pDltsDevice;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLTSguiApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDLTSguiApp)
	afx_msg void OnAppAbout();
	afx_msg void UpdateDocumentView();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLTSGUI_H__5CE3155B_848B_49E5_9502_D8D0E1152BFA__INCLUDED_)
