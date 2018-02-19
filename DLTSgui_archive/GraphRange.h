#if !defined(AFX_GRAPHRANGE_H__A49FF552_879B_4970_9376_91F3774F1136__INCLUDED_)
#define AFX_GRAPHRANGE_H__A49FF552_879B_4970_9376_91F3774F1136__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphRange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGraphRange dialog

class CGraphRange : public CDialog
{
// Construction
public:
	CGraphRange(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphRange)
	enum { IDD = IDD_GRAPH_RANGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphRange)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHRANGE_H__A49FF552_879B_4970_9376_91F3774F1136__INCLUDED_)
