#if !defined(AFX_LISTFRAME_H__F21A0BD5_9C9B_4D6C_86BC_B7090B80B22E__INCLUDED_)
#define AFX_LISTFRAME_H__F21A0BD5_9C9B_4D6C_86BC_B7090B80B22E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListFrame.h : header file
//

class CDataArray;
class CDLTSguiDoc;
/////////////////////////////////////////////////////////////////////////////
// CListFrame window

class CListFrame : public CWnd
{
// Construction
public:
	CListFrame();

// Attributes
public:

// Operations
public:

	CListCtrl* m_ListCtrlCt;
	CDLTSguiDoc * m_activeDocument;
	
	CImageList * m_pImageList;


	
	void AddProjectItem(CDataArray *dataArray);

	void UpdateListContent();
	void UpdateCurrentView();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListFrame();

	// Generated message map functions
protected:
	int m_sortDirection;

	int GetIcon(double temperature);
	

	//{{AFX_MSG(CListFrame)
	afx_msg void OnKeydown(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDoubleClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnColumnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTFRAME_H__F21A0BD5_9C9B_4D6C_86BC_B7090B80B22E__INCLUDED_)
