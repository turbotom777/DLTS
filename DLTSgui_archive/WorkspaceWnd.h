#if !defined(__PROJECT_VIEW_H__)
#define __PROJECT_VIEW_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DockingBar.h : header file
//


class CDataArray;
class CDLTSguiDoc;
class CListFrame;

#include "sizecbar.h"
/////////////////////////////////////////////////////////////////////////////
// CDockingBar window

#ifndef baseCDockingBar
#define baseCDockingBar CSizingControlBar
#endif

class CWorkspaceWnd : public baseCDockingBar
{
// Construction
public:
    CWorkspaceWnd();

// Attributes
public:
    CTabCtrl* m_pTabCtrl;
	CListFrame* m_pListFrame;



// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Operations
public:
    void ToggleStatus();
    void UpdateCurrentView();
	

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CWorkspaceWnd)
	public:
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDocument(CDLTSguiDoc * doc);
    virtual ~CWorkspaceWnd();

	void UpdateListContent();


protected:
    CFont   m_font;

    BOOL    m_bIsBarActive;
	void ShowCurrentList();

    // Generated message map functions
protected:
    //{{AFX_MSG(CWorkspaceWnd)
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnDestroy( );
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__MYBAR_H__)
