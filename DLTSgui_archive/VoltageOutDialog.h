#if !defined(AFX_VOLTAGEOUTDIALOG_H__0B4C6002_D5E6_11DA_AB29_AB9238BAC77A__INCLUDED_)
#define AFX_VOLTAGEOUTDIALOG_H__0B4C6002_D5E6_11DA_AB29_AB9238BAC77A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VoltageOutDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVoltageOutDialog dialog

class CVoltageOutDialog : public CDialog
{
// Construction
public:
	CVoltageOutDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVoltageOutDialog)
	enum { IDD = IDD_DIALOG_OUT_VOLTAGE };
	float	m_voltageOut;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVoltageOutDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVoltageOutDialog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VOLTAGEOUTDIALOG_H__0B4C6002_D5E6_11DA_AB29_AB9238BAC77A__INCLUDED_)
