#if !defined(AFX_GRAPHPROPERTIES_H__DD12F6CD_70D0_44CC_9784_24B189CE5B1F__INCLUDED_)
#define AFX_GRAPHPROPERTIES_H__DD12F6CD_70D0_44CC_9784_24B189CE5B1F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GraphProperties.h : header file
//

class CDLTSguiView;
/////////////////////////////////////////////////////////////////////////////
// CGraphProperties dialog

class CGraphProperties : public CDialog
{
// Construction
public:
	CGraphProperties(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CGraphProperties)
	enum { IDD = IDD_GRAPH_RANGE };
	double	m_maxX;
	double	m_maxY;
	double	m_minX;
	double	m_minY;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphProperties)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGraphProperties)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHPROPERTIES_H__DD12F6CD_70D0_44CC_9784_24B189CE5B1F__INCLUDED_)
