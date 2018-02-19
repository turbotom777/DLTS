#if !defined(AFX_BOONTONRANGE_H__2ED0D3C1_D6A0_11DA_AB29_0000C05C25D3__INCLUDED_)
#define AFX_BOONTONRANGE_H__2ED0D3C1_D6A0_11DA_AB29_0000C05C25D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BoontonRange.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBoontonRange dialog

class CBoontonRange : public CDialog
{
// Construction
public:
	CBoontonRange(CWnd* pParent = NULL);   // standard constructor


	void setRange(int range);
	int getRange();
// Dialog Data
	//{{AFX_DATA(CBoontonRange)
	enum { IDD = IDD_DIALOG_BOONTON_RANGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBoontonRange)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	int m_range;

	// Generated message map functions
	//{{AFX_MSG(CBoontonRange)
	afx_msg void OnRadioRange2pF();
	afx_msg void OnRadioRange20pF();
	afx_msg void OnRadioRange200pF();
	afx_msg void OnRadioRange2000pF();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BOONTONRANGE_H__2ED0D3C1_D6A0_11DA_AB29_0000C05C25D3__INCLUDED_)
